#pragma once
#include <string>
#include <GL\glew.h>

class TextureClass
{
public:
	TextureClass(const std::string& filename);
	~TextureClass();

	void bind(unsigned int unit);

private:
	GLuint theTextureHandler;
};

