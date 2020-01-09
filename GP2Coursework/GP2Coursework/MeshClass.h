#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "ObjectLoaderClass.h"

// Vertex struct
struct Vertex
{
public:
	// Constructor for Vertex
	Vertex(const glm::vec3& position, const glm::vec2& textureCoordinates)
	{
		// Assign variables
		this->position = position;
		this->textureCoordinates = textureCoordinates;
		this->normal = normal;
	}

	// Getters
	glm::vec3* GetPosition() { return &position; }
	glm::vec2* GetTextureCoordinates() { return &textureCoordinates; }
	glm::vec3* GetNormal() { return &normal; }


private:
	// Private variables
	glm::vec3 position;
	glm::vec2 textureCoordinates;
	glm::vec3 normal;
};

// MeshClass class
class MeshClass
{
public:
	// Constructor and deconstructor
	MeshClass();
	~MeshClass();

	// Methods
	void draw();
	void loadModel(const std::string& modelFilename);
	void initialiseModel(const IndexedModelClass& theModel);

private:
	// Enum declaration
	enum
	{
		POSITION_VB,
		TEXTURE_COORDINATES_VB,
		NORMAL_VB,
		INDEX_VB,
		NUMBER_OF_BUFFERS
	};

	// Variable declarations
	GLuint vertexArrayObject;
	// Array of buffers
	GLuint vertexArrayBuffers[NUMBER_OF_BUFFERS];
	unsigned int drawCount;
};
