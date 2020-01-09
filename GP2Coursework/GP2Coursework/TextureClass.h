#pragma once
#include <string>
#include <GL\glew.h>

class TextureClass
{
public:
	// Constructor and deconstructor
	TextureClass(const std::string& filename);
	~TextureClass();

	// Bind method declaration
	void Bind(unsigned int unit);

private:
	// Private variable
	GLuint theTextureHandler;
};

