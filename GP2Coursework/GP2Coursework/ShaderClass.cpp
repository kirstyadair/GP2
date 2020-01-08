#include "ShaderClass.h"
#include <iostream>
#include <fstream>

ShaderClass::ShaderClass(const std::string& filename)
{
	// Create shader program (saved by a reference number)
	program = glCreateProgram();
	// Create the vertex shader
	shaders[0] = CreateShader(LoadShader("..\\res\\Shader\\shader.vert"), GL_VERTEX_SHADER);
	// Create the fragment shader
	shaders[1] = CreateShader(LoadShader("..\\res\\Shader\\shader.frag"), GL_FRAGMENT_SHADER);

	// Add all shaders to the shader program
	for (unsigned int i = 0; i < NUMBER_OF_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]);
	}

	// Associate attribute variable with the shader program attribute
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	
	// Create executable that runs on GPU shaders
	glLinkProgram(program);
	// Check for errors
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed");

	// Check the program is valid
	glValidateProgram(program);
	// Otherwise give an error
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	// Join with the location of uniform variable within the program
	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}


ShaderClass::~ShaderClass()
{
	// Iterate through all shaders
	for (unsigned int i = 0; i < NUMBER_OF_SHADERS; i++)
	{
		// Detach shader from program
		glDetachShader(program, shaders[i]);
		// Delete the shader
		glDeleteShader(shaders[i]); 
	}
	// Delete the program
	glDeleteProgram(program);
}

void ShaderClass::Bind()
{
	// Installs program object
	glUseProgram(program);
}

void ShaderClass::Update(const Transform& transform, const CameraClass& camera)
{
	// Get the model view projection matrix
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}

GLuint ShaderClass::CreateShader(const std::string& text, unsigned int type)
{
	// Create a shader based on the type
	GLuint shader = glCreateShader(type);

	// If there is no shader created, show an error
	if (shader == 0) std::cerr << "Error type creation failed " << type << std::endl;

	// Convert strings into c-string lists
	const GLchar* stringSource[1];
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	// Send source code to openGL
	glShaderSource(shader, 1, stringSource, lengths);
	// Use openGL to compile the shader
	glCompileShader(shader);
	// Check for errors
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

std::string ShaderClass::LoadShader(const std::string& fileName)
{
	// Open the file using the filename provided
	std::ifstream file;
	file.open((fileName).c_str());

	// Declare strings
	std::string output;
	std::string line;

	// Check the file is open
	if (file.is_open())
	{
		while (file.good())
		{
			// Append each line of the file
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		// Return an error
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void ShaderClass::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	// Declare a GL int and GL char
	GLint success = 0;
	GLchar error[1024] = { 0 };

	// If is program
	if (isProgram)
		// Get the program iv 
		glGetProgramiv(shader, flag, &success);
	else
		// Get the shader iv
		glGetShaderiv(shader, flag, &success);

	// If not successful
	if (success == GL_FALSE)
	{
		// If a program
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		// Output an error message
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

