#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class DisplayClass
{
public:
	DisplayClass();
	~DisplayClass();
	
	void Init();
	void bufferSwap();
	void clearDisplay(float red, float green, float blue, float alpha);

	float getScreenWidth()
	{
		return widthOfScreen;
	}
	float getScreenHeight()
	{
		return heightOfScreen;
	}

private:

	void showError(std::string errorString);
	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to out window
	float widthOfScreen;
	float heightOfScreen;
};
