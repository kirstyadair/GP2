#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

// ObjectIndex struct
struct ObjectIndex
{
	// Variables
	unsigned int vertexIndex;
	unsigned int uvIndex;
	unsigned int normalIndex;

	// Method
	bool operator<(const ObjectIndex& r) const { return vertexIndex < r.vertexIndex; }
};

// IndexedModelClass class
class IndexedModelClass
{
public:
	// Vector declarations
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textureCoordinates;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	// Method
	void CalculateNormals();
};

// ObjectModel class
class ObjectModel
{
public:
	// Vector declarations
	std::vector<ObjectIndex> ObjectIndices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	// Booleans
	bool hasUVs;
	bool hasNormals;

	// Methods
	ObjectModel(const std::string& objectFilename);
	IndexedModelClass ToIndexedModel();

private:

	// Private methods
	unsigned int FindLastVertexIndex(const std::vector<ObjectIndex*>& indexLookup, const ObjectIndex* theCurrentIndex, const IndexedModelClass& theResult);
	void CreateObjectFace(const std::string& line);
	glm::vec2 ParseObjectVector2(const std::string& line);
	glm::vec3 ParseObjectVector3(const std::string& line);
	ObjectIndex ParseObjectIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};

