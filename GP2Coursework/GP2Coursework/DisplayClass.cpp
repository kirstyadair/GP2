#include "DisplayClass.h"


DisplayClass::DisplayClass()
{
	// Create null access violation for debugging purposes
	sdlWindow = nullptr;
	// Set the width and height for the screen
	widthOfScreen = 1024;
	heightOfScreen = 768;
}

DisplayClass::~DisplayClass()
{
	// Delete the context
	SDL_GL_DeleteContext(glContext);
	// Delete the window
	SDL_DestroyWindow(sdlWindow);
	// Quit the game
	SDL_Quit();
}

void DisplayClass::showError(std::string errorString)
{
	// Display error message
	std::cout << errorString << std::endl;
	std::cout << "Press any key to quit.";
	// Take user input
	int in;
	std::cin >> in;
	// Quit the game
	SDL_Quit();
}

void DisplayClass::bufferSwap()
{
	// Swap the buffers
	SDL_GL_SwapWindow(sdlWindow);
}

void DisplayClass::clearDisplay(float red, float green, float blue, float alpha)
{
	// Clear the display using the values provided
	glClearColor(red, green, blue, alpha);
	// Clear the colour and depth buffer, set the colour to glClearColor
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DisplayClass::Init()
{
	// Initialise everything 
	SDL_Init(SDL_INIT_EVERYTHING);

	// Set the minimum number of bits to display colour
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	// Initialise the double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);   

	// Create the window
	sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)widthOfScreen, (int)heightOfScreen, SDL_WINDOW_OPENGL);
	// Enable z buffering 
	glEnable(GL_DEPTH_TEST);
	// Cull faces that aren't facing the camera
	glEnable(GL_CULL_FACE);

	// If the window does not create correctly
	if (sdlWindow == nullptr)
	{
		// Show an error message
		showError("Window did not create");
	}

	// Create the window context
	glContext = SDL_GL_CreateContext(sdlWindow);

	// If the context fails to create
	if (glContext == nullptr)
	{
		// Show an error message
		showError("SDL_GL context did not create");
	}

	// Initialise GLEW
	GLenum error = glewInit();
	// If not successful
	if (error != GLEW_OK)
	{
		// Show an error message
		showError("GLEW did not initialise");
	}

	// Set the clear colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

