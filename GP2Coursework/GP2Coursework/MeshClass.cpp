#include "MeshClass.h"
#include <vector>

MeshClass::MeshClass()
{
	
}


MeshClass::~MeshClass()
{
	glDeleteVertexArrays(1, &vertexArrayObject); // delete arrays
}

void MeshClass::draw()
{
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glBindVertexArray(0);
}

void MeshClass::loadModel(const std::string& filename)
{
	ObjectModel obj = ObjectModel(filename);
	IndexedModelClass model = obj.ToIndexedModel();
	initialiseModel(model);
}

// This isn't called by anything, delete this later if it's never used
/*void MeshClass::initialise(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModelClass model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPosition());
		model.textureCoordinates.push_back(*vertices[i].GetTextureCoordinates());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	initialiseModel(model);

}*/

void MeshClass::initialiseModel(const IndexedModelClass& model)
{
	drawCount = model.indices.size();

	glGenVertexArrays(1, &vertexArrayObject); 
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUMBER_OF_BUFFERS, vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]); 
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXTURE_COORDINATES_VB]); 
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.textureCoordinates[0]), &model.textureCoordinates[0], GL_STATIC_DRAW); 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0); 

}

