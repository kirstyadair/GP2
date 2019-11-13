#include "DisplayClass.h"


DisplayClass::DisplayClass()
{
	sdlWindow = nullptr; //initialise to generate null access violation for debugging. 
	widthOfScreen = 1024;
	heightOfScreen = 768;
}

DisplayClass::~DisplayClass()
{
	SDL_GL_DeleteContext(glContext); // delete context
	SDL_DestroyWindow(sdlWindow); // detete window (make sure to delete the context and the window in the opposite order of creation in initDisplay())
	SDL_Quit();
}

void DisplayClass::showError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Press any key to quit.";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void DisplayClass::bufferSwap()
{
	SDL_GL_SwapWindow(sdlWindow); //swap buffers
}

void DisplayClass::clearDisplay(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void DisplayClass::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)widthOfScreen, (int)heightOfScreen, SDL_WINDOW_OPENGL); // create window
	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera


	if (sdlWindow == nullptr)
	{
		showError("Window did not create");
	}

	glContext = SDL_GL_CreateContext(sdlWindow);

	if (glContext == nullptr)
	{
		showError("SDL_GL context did not create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		showError("GLEW did not initialise");
	}

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	
}

