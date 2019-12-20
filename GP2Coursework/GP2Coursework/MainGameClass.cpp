#include "MainGameClass.h"
#include <iostream>
#include <string>
#include "CameraClass.h"
#include <glm/glm.hpp>


MainGameClass::MainGameClass()
{
	gamePlaying = true;
	DisplayClass* gameDisplay = new DisplayClass(); //new display
	counter = 0.0f;
	
	camera1.GetViewProjection();
	camera1.initialiseCamera(glm::vec3(0, 0, -100), 70.0f, gameDisplay->getScreenWidth() / gameDisplay->getScreenHeight(), 0.01f, 1000.0f);

	fish1.SetStartPos(0, 0, 0);
	fish2.SetStartPos(15, 3, 0);
}

MainGameClass::~MainGameClass()
{

}

void MainGameClass::run()
{
	gameDisplay.Init();
	loadModelsFromFile();
	gameLoop();
}

void MainGameClass::loadModelsFromFile()
{
	// Loads the models before gameplay loop starts
	mesh1.loadModel("C:\\Users\\kirst\\Downloads\\Fish1.obj");
	mesh2.loadModel("C:\\Users\\kirst\\Downloads\\Fish1.obj");
	fish1shader = new ShaderClass("..\\res\\shader"); //new shader
	fish2shader = new ShaderClass("..\\res\\shader"); //new shader
	fish1texture = new TextureClass("..\\res\\fish flipped.png");
	fish2texture = new TextureClass("..\\res\\fish flipped.png");
}

void MainGameClass::gameLoop()
{
	while (gamePlaying)
	{
		// Handle input here
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			// If the event type quits the game
			if (event.type == SDL_QUIT)
			{
				// End the gameplay loop
				gamePlaying = false;
			}
		}
						
		// Draw everything to the screen
		drawGame();
	}
}


void MainGameClass::drawGame()
{
	gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	fish1.MoveFish(fish1shader, fish1texture, camera1);
	fish2.MoveFish(fish2shader, fish2texture, camera1);
	
	
	mesh1.draw();
	mesh2.draw();

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	gameDisplay.bufferSwap();
}
