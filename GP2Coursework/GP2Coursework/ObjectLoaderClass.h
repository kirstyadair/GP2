#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

struct ObjectIndex
{
	unsigned int vertexIndex;
	unsigned int uvIndex;
	unsigned int normalIndex;

	bool operator<(const ObjectIndex& r) const { return vertexIndex < r.vertexIndex; }
};

class IndexedModelClass
{
public:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textureCoordinates;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	void CalculateNormals();
};

class ObjectModel
{
public:
	std::vector<ObjectIndex> ObjectIndices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool hasUVs;
	bool hasNormals;

	ObjectModel(const std::string& objectFilename);

	IndexedModelClass ToIndexedModel();
private:
	unsigned int FindLastVertexIndex(const std::vector<ObjectIndex*>& indexLookup, const ObjectIndex* theCurrentIndex, const IndexedModelClass& theResult);
	void CreateObjectFace(const std::string& line);

	glm::vec2 ParseObjectVector2(const std::string& line);
	glm::vec3 ParseObjectVector3(const std::string& line);
	ObjectIndex ParseObjectIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};

