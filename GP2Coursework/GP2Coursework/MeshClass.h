#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "ObjectLoaderClass.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& position, const glm::vec2& textureCoordinates)
	{
		this->position = position;
		this->textureCoordinates = textureCoordinates;
		this->normal = normal;
	}

	glm::vec3* GetPosition() { return &position; }
	glm::vec2* GetTextureCoordinates() { return &textureCoordinates; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 position;
	glm::vec2 textureCoordinates;
	glm::vec3 normal;
};

class MeshClass
{
public:
	MeshClass();
	~MeshClass();

	void draw();
	void initialise(Vertex* vertices, unsigned int numberOfVertices, unsigned int* indices, unsigned int numberOfIndices);
	void loadModel(const std::string& modelFilename);
	void initialiseModel(const IndexedModelClass& theModel);

private:



	enum
	{
		POSITION_VB,
		TEXTURE_COORDINATES_VB,
		NORMAL_VB,
		INDEX_VB,
		NUMBER_OF_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUMBER_OF_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};
