#include "TextureClass.h"
#include "STBImageClass.h"
#include <cassert>
#include <iostream>

TextureClass::TextureClass(const std::string& fileName)
{
	// Declare width, height and number of components of the image
	int width, height, numComponents;
	// Load the image and store the data
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	// If there is no image data, return an error
	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}

	// Generate textures using the number of texture and the address of the texture
	glGenTextures(1, &theTextureHandler);
	// Bind the texture and define the type
	glBindTexture(GL_TEXTURE_2D, theTextureHandler);

	// Wrap the texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	// Wrap the texture outside height
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	// Filtering for if the texture is smaller than the area
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Filtering for if the texture is larger than the area
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Pass in the required data 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	// Free the loaded image
	stbi_image_free(imageData);
}

TextureClass::~TextureClass()
{
	// Delete the textures using the number of and address of the textures
	glDeleteTextures(1, &theTextureHandler);
}

void TextureClass::Bind(unsigned int unit)
{
	// Ensure working with one of 32 textures
	assert(unit >= 0 && unit <= 31);

	// Set the active temperature unit
	glActiveTexture(GL_TEXTURE0 + unit);
	// Bind the texture using the type of texture and the texture to bind
	glBindTexture(GL_TEXTURE_2D, theTextureHandler);
}
