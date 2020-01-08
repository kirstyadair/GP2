#include "MeshClass.h"
#include <vector>

MeshClass::MeshClass()
{
	
}


MeshClass::~MeshClass()
{
	// Delete the arrays
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void MeshClass::draw()
{
	// Bind the vertex array
	glBindVertexArray(vertexArrayObject);
	// Draw the model
	glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glBindVertexArray(0);
}

void MeshClass::loadModel(const std::string& filename)
{
	// Create an instance of ObjectModel 
	ObjectModel obj = ObjectModel(filename);
	// Convert it to an indexed model
	IndexedModelClass model = obj.ToIndexedModel();
	// Initialise the model
	initialiseModel(model);
}

void MeshClass::initialiseModel(const IndexedModelClass& model)
{
	// Set the draw count
	drawCount = model.indices.size();

	// Create a vertex array and store it in the array object
	glGenVertexArrays(1, &vertexArrayObject); 
	// Bind the object
	glBindVertexArray(vertexArrayObject);
	// Generate the buffers
	glGenBuffers(NUMBER_OF_BUFFERS, vertexArrayBuffers);

	// Declare the data type of the buffer and pass through the data
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]); 
	// Send data to GPU
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Declare the data type of the buffer and pass through the data
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXTURE_COORDINATES_VB]); 
	// Send data to the GPU
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.textureCoordinates[0]), &model.textureCoordinates[0], GL_STATIC_DRAW); 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Declare the data type of the buffer and pass through the data
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	// Send data to the GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Declare the data type of the buffer and pass through the data 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	// Send data to the GPU
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	// Unbind the vertex array object
	glBindVertexArray(0); 

}

