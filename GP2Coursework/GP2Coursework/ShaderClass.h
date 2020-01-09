#pragma once
#include <string>
#include <GL\glew.h>
#include "Transform.h"


class ShaderClass
{
public:
	// Constructor and deconstructor
	ShaderClass(const std::string& filename);
	~ShaderClass();
	// Methods
	void Bind();
	void Update(const Transform& transform, const CameraClass& camera);
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

private:
	// Number of shaders
	static const unsigned int NUMBER_OF_SHADERS = 2;

	// Enum Declaration
	enum
	{
		TRANSFORM_U,
		NUMBER_OF_UNIFORMS
	};

	// Private variables
	GLuint program;
	GLuint shaders[NUMBER_OF_SHADERS];
	GLuint uniforms[NUMBER_OF_UNIFORMS];
};
