#include "ObjectLoaderClass.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

// Static variables 
static bool CompareObjectIndexPointer(const ObjectIndex* a, const ObjectIndex* b);
static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token);
static inline unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end);
static inline float ParseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end);
static inline std::vector<std::string> SplitString(const std::string &s, char delim);

ObjectModel::ObjectModel(const std::string& fileName)
{
	// Set booleans to false
	hasUVs = false;
	hasNormals = false;
	// Declare and open the file
	std::ifstream file;
	file.open(fileName.c_str());
	std::string line;

	// Check the file is open
	if (file.is_open())
	{
		while (file.good())
		{
			// Get each line
			getline(file, line);
			// Find the length of each line
			unsigned int lineLength = line.length();
			// If the line length is less than 2, ignore it
			if (lineLength < 2)
				continue;

			// Make a c-string for the line
			const char* lineCStr = line.c_str();

			// Switch statement for each character in the line c-string
			switch (lineCStr[0])
			{
				// Parse object vectors based on the character
			case 'v':
				if (lineCStr[1] == 't')
					this->uvs.push_back(ParseObjectVector2(line));
				else if (lineCStr[1] == 'n')
					this->normals.push_back(ParseObjectVector3(line));
				else if (lineCStr[1] == ' ' || lineCStr[1] == '\t')
					this->vertices.push_back(ParseObjectVector3(line));
				break;
			case 'f':
				// Create an object face
				CreateObjectFace(line);
				break;
			default: break;
			};
		}
	}
	else
	{
		// Output an error
		std::cerr << "Unable to load mesh: " << fileName << std::endl;
	}
}

void IndexedModelClass::CalculateNormals()
{
	// Iterate through the vector of indices
	for (unsigned int i = 0; i < indices.size(); i += 3)
	{
		// Declare 3 integers holding the indices
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		// Declare 2 vec3s and find their directions
		glm::vec3 v1 = positions[i1] - positions[i0];
		glm::vec3 v2 = positions[i2] - positions[i0];

		// Find the normal of the two vector3s
		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		// Add the normal to the normals list in three positions
		normals[i0] += normal;
		normals[i1] += normal;
		normals[i2] += normal;
	}

	// Normalize each normal 
	for (unsigned int i = 0; i < positions.size(); i++)
		normals[i] = glm::normalize(normals[i]);
}

IndexedModelClass ObjectModel::ToIndexedModel()
{
	// Create two IndexedModelClass instances
	IndexedModelClass result;
	IndexedModelClass normalModel;

	// Store the number of object indices
	unsigned int numberOfIndices = ObjectIndices.size();
	// Create a vector of ObjectIndex instances
	std::vector<ObjectIndex*> indexLookup;

	// Iterate through each index and push it back
	for (unsigned int i = 0; i < numberOfIndices; i++)
		indexLookup.push_back(&ObjectIndices[i]);

	// Sort the indexLookup
	std::sort(indexLookup.begin(), indexLookup.end(), CompareObjectIndexPointer);

	// Declare two index maps
	std::map<ObjectIndex, unsigned int> normalModelIndexMap;
	std::map<unsigned int, unsigned int> indexMap;

	// Iterate through each index
	for (unsigned int i = 0; i < numberOfIndices; i++)
	{
		// Declare and store the current index
		ObjectIndex* currentIndex = &ObjectIndices[i];

		// Declare the current position, texture coordinate and normal
		glm::vec3 currentPosition = vertices[currentIndex->vertexIndex];
		glm::vec2 currentTexCoord;
		glm::vec3 currentNormal;

		// If hasUVs is true, the texture coordinate is set to the current UV index
		if (hasUVs)
			currentTexCoord = uvs[currentIndex->uvIndex];
		else
			// Otherwise the texture coordinate is set to (0,0)
			currentTexCoord = glm::vec2(0, 0);

		// If hasNormals is true, the current normal is set to the current normal index
		if (hasNormals)
			currentNormal = normals[currentIndex->normalIndex];
		else
			// Otherwise it is set to (0,0,0)
			currentNormal = glm::vec3(0, 0, 0);

		// Declare two integers holding normal and result model indices
		unsigned int normalModelIndex;
		unsigned int resultModelIndex;

		//Create model to generate normals on
		std::map<ObjectIndex, unsigned int>::iterator it = normalModelIndexMap.find(*currentIndex);
		if (it == normalModelIndexMap.end())
		{
			normalModelIndex = normalModel.positions.size();

			normalModelIndexMap.insert(std::pair<ObjectIndex, unsigned int>(*currentIndex, normalModelIndex));
			normalModel.positions.push_back(currentPosition);
			normalModel.textureCoordinates.push_back(currentTexCoord);
			normalModel.normals.push_back(currentNormal);
		}
		else
			normalModelIndex = it->second;

		// Set the result model index to the size of the result positions vector
		resultModelIndex = result.positions.size();
		// Push back the current position, texture coordinate and normal
		result.positions.push_back(currentPosition);
		result.textureCoordinates.push_back(currentTexCoord);
		result.normals.push_back(currentNormal);

		// Push back the normal model index and result model index
		normalModel.indices.push_back(normalModelIndex);
		result.indices.push_back(resultModelIndex);
		// Insert the indices
		indexMap.insert(std::pair<unsigned int, unsigned int>(resultModelIndex, normalModelIndex));
	}

	// If hasNormals is false
	if (!hasNormals)
	{
		// Calculate the normals
		normalModel.CalculateNormals();

		// Iterate through each result normal and assign a normal
		for (unsigned int i = 0; i < result.positions.size(); i++)
			result.normals[i] = normalModel.normals[indexMap[i]];
	}

	// Return the indexed model
	return result;
};

unsigned int ObjectModel::FindLastVertexIndex(const std::vector<ObjectIndex*>& indexLookup, const ObjectIndex* currentIndex, const IndexedModelClass& result)
{
	// Declare and assign integer variables
	unsigned int start = 0;
	unsigned int end = indexLookup.size();
	unsigned int current = (end - start) / 2 + start;
	unsigned int previous = start;
	
	// Iterate while current and previous are not the same value
	while (current != previous)
	{
		// Store the current index of indexLookup
		ObjectIndex* testIndex = indexLookup[current];

		// If test index vertex index and current index vertex index are the same 
		if (testIndex->vertexIndex == currentIndex->vertexIndex)
		{
			unsigned int countStart = current;

			for (unsigned int i = 0; i < current; i++)
			{
				// Store possible index
				ObjectIndex* possibleIndex = indexLookup[current - i];

				// If possible index is the current index, continue to the next iteration
				if (possibleIndex == currentIndex)
					continue;

				// if the vertexIndex of possibleIndex and currentIndex aren't the same, break the loop
				if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
					break;

				countStart--;
			}

			for (unsigned int i = countStart; i < indexLookup.size() - countStart; i++)
			{
				// Store the indexLookup index of current + 1 in possibleIndex
				ObjectIndex* possibleIndex = indexLookup[current + i];

				// If the same, continue
				if (possibleIndex == currentIndex)
					continue;

				// If the vertexIndex values are different, break the loop
				if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
					break;
				// Otherwise check the hasUVs boolean, or that the uvIndex values are the same
				else if ((!hasUVs || possibleIndex->uvIndex == currentIndex->uvIndex)
					// And that either the hasNormals boolean is false or the normalIndex values are the same
					&& (!hasNormals || possibleIndex->normalIndex == currentIndex->normalIndex))
				{
					glm::vec3 currentPosition = vertices[currentIndex->vertexIndex];
					glm::vec2 currentTexCoord;
					glm::vec3 currentNormal;

					// If hasUvs, assign the texture coordinates
					if (hasUVs)
						currentTexCoord = uvs[currentIndex->uvIndex];
					else
						currentTexCoord = glm::vec2(0, 0);

					// If hasNormals, assign normals
					if (hasNormals)
						currentNormal = normals[currentIndex->normalIndex];
					else
						currentNormal = glm::vec3(0, 0, 0);

					// Iterate through positions size
					for (unsigned int j = 0; j < result.positions.size(); j++)
					{
						if (currentPosition == result.positions[j]
							&& ((!hasUVs || currentTexCoord == result.textureCoordinates[j])
								&& (!hasNormals || currentNormal == result.normals[j])))
						{
							return j;
						}
					}
				}
			}

			return -1;
		}
		else
		{
			// Check vertexIndex values against each other
			if (testIndex->vertexIndex < currentIndex->vertexIndex)
				start = current;
			else
				end = current;
		}

		previous = current;
		current = (end - start) / 2 + start;
	}

	// Return failure
	return -1;
}

void ObjectModel::CreateObjectFace(const std::string& line)
{
	// Create a vector of strings
	std::vector<std::string> tokens = SplitString(line, ' ');

	// Use this vector to push back indices
	this->ObjectIndices.push_back(ParseObjectIndex(tokens[1], &this->hasUVs, &this->hasNormals));
	this->ObjectIndices.push_back(ParseObjectIndex(tokens[2], &this->hasUVs, &this->hasNormals));
	this->ObjectIndices.push_back(ParseObjectIndex(tokens[3], &this->hasUVs, &this->hasNormals));

	// If the tokens is more than 4
	if ((int)tokens.size() > 4)
	{
		// Push back indices
		this->ObjectIndices.push_back(ParseObjectIndex(tokens[1], &this->hasUVs, &this->hasNormals));
		this->ObjectIndices.push_back(ParseObjectIndex(tokens[3], &this->hasUVs, &this->hasNormals));
		this->ObjectIndices.push_back(ParseObjectIndex(tokens[4], &this->hasUVs, &this->hasNormals));
	}
}

// Method for parsing object index
ObjectIndex ObjectModel::ParseObjectIndex(const std::string& token, bool* hasUVs, bool* hasNormals)
{
	unsigned int tokenLength = token.length();
	const char* tokenString = token.c_str();

	unsigned int vertIndexStart = 0;
	unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

	ObjectIndex result;
	result.vertexIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
	result.uvIndex = 0;
	result.normalIndex = 0;

	if (vertIndexEnd >= tokenLength)
		return result;

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

	result.uvIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
	*hasUVs = true;

	if (vertIndexEnd >= tokenLength)
		return result;

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

	result.normalIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
	*hasNormals = true;

	return result;
}

// Method for parsing Vector 3s
glm::vec3 ObjectModel::ParseObjectVector3(const std::string& line)
{
	unsigned int tokenLength = line.length();
	const char* tokenString = line.c_str();

	unsigned int vertIndexStart = 2;

	while (vertIndexStart < tokenLength)
	{
		if (tokenString[vertIndexStart] != ' ')
			break;
		vertIndexStart++;
	}

	unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float z = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	return glm::vec3(x, y, z);
}

// Method for parsing Vector 2s
glm::vec2 ObjectModel::ParseObjectVector2(const std::string& line)
{
	unsigned int tokenLength = line.length();
	const char* tokenString = line.c_str();

	unsigned int vertIndexStart = 3;

	while (vertIndexStart < tokenLength)
	{
		if (tokenString[vertIndexStart] != ' ')
			break;
		vertIndexStart++;
	}

	unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	return glm::vec2(x, y);
}

// Method for comparing index pointers
static bool CompareObjectIndexPointer(const ObjectIndex* a, const ObjectIndex* b)
{
	return a->vertexIndex < b->vertexIndex;
}

// Method for finding next character
static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token)
{
	unsigned int result = start;
	while (result < length)
	{
		result++;
		if (str[result] == token)
			break;
	}

	return result;
}

// Method for parsing index values
static inline unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end)
{
	return atoi(token.substr(start, end - start).c_str()) - 1;
}

// Method for parsing float values
static inline float ParseOBJFloatValue(const std::string& token, unsigned int start, unsigned int end)
{
	return atof(token.substr(start, end - start).c_str());
}

// Method for splitting strings
static inline std::vector<std::string> SplitString(const std::string &s, char delim)
{
	std::vector<std::string> elems;

	const char* cstr = s.c_str();
	unsigned int strLength = s.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end < strLength)
	{
		while (end <= strLength)
		{
			if (cstr[end] == delim)
				break;
			end++;
		}

		elems.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}
