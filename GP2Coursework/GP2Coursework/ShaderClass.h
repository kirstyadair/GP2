#pragma once
#include <string>
#include <GL\glew.h>
#include "Transform.h"


class ShaderClass
{
public:
	ShaderClass(const std::string& filename);

	void Bind(); //Set gpu to use our shaders
	void Update(const Transform& transform, const CameraClass& camera);

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	~ShaderClass();

protected:
private:
	static const unsigned int NUMBER_OF_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUMBER_OF_UNIFORMS
	};

	GLuint program; // Track the shader program
	GLuint shaders[NUMBER_OF_SHADERS]; //array of shaders
	GLuint uniforms[NUMBER_OF_UNIFORMS]; //no of uniform variables
};
