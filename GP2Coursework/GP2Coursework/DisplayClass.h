#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class DisplayClass
{
public:
	// Constructor and deconstructor
	DisplayClass();
	~DisplayClass();
	
	// Public methods
	void Init();
	void bufferSwap();
	void clearDisplay(float red, float green, float blue, float alpha);

	// Getters for screen width and height
	float getScreenWidth()
	{
		return widthOfScreen;
	}
	float getScreenHeight()
	{
		return heightOfScreen;
	}

private:
	// Private variables
	void showError(std::string errorString);
	// Global variable holding context
	SDL_GLContext glContext;
	// Pointer to window
	SDL_Window* sdlWindow; 
	float widthOfScreen;
	float heightOfScreen;
};
