#include "MainGameClass.h"
#include <iostream>
#include <string>
#include "CameraClass.h"
#include <glm/glm.hpp>

int MainGameClass::selectedFish = 0;

MainGameClass::MainGameClass()
{
	gamePlaying = true;
	DisplayClass* gameDisplay = new DisplayClass(); //new display
	counter = 0.0f;
	
	camera1.GetViewProjection();
	camera1.initialiseCamera(glm::vec3(0, 0, -100), 70.0f, gameDisplay->getScreenWidth() / gameDisplay->getScreenHeight(), 0.01f, 1000.0f);

	fish1.SetStartPos(0, 0, 10);
	fish2.SetStartPos(0, 0, 0);
	fish3.SetStartPos(0, 0, -10);

	MainGameClass::selectedFish = 1;
	fish1.isSelected = true;

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
	mesh2.loadModel("C:\\Users\\kirst\\Downloads\\tropicalFish2.obj");
	mesh3.loadModel("C:\\Users\\kirst\\Downloads\\fish3.obj");
	backgroundMesh.loadModel("C:\\Users\\kirst\\Downloads\\fish3.obj");
	fish1shader = new ShaderClass("..\\res\\shader"); 
	fish2shader = new ShaderClass("..\\res\\shader"); 
	fish3shader = new ShaderClass("..\\res\\shader"); 
	backgroundShader = new ShaderClass("..\\res\\shader"); 
	fish1texture = new TextureClass("..\\res\\fish flipped.png");
	fish2texture = new TextureClass("..\\res\\TropicalFish02.jpg");
	fish3texture = new TextureClass("..\\res\\TropicalFish05.jpg");
	backgroundTexture = new TextureClass("..\\res\\texture.jpg");
}

void MainGameClass::gameLoop()
{
	
	
	while (gamePlaying)
	{
		// Handle input here
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_1)
				{
					MainGameClass::selectedFish = 1;
					fish1.isSelected = true;
					fish2.isSelected = false;
					fish3.isSelected = false;
				}
				if (event.key.keysym.sym == SDLK_2)
				{
					MainGameClass::selectedFish = 2;
					fish1.isSelected = false;
					fish2.isSelected = true;
					fish3.isSelected = false;
				}
				if (event.key.keysym.sym == SDLK_3)
				{
					MainGameClass::selectedFish = 3;
					fish1.isSelected = false;
					fish2.isSelected = false;
					fish3.isSelected = true;
				}

				if (event.key.keysym.sym == SDLK_LEFT)
				{
					switch (selectedFish)
					{
					case 1:
						fish1.movingLeft = true;
						break;
					case 2:
						fish2.movingLeft = true;
						break;
					case 3:
						fish3.movingLeft = true;
						break;
					}
					
				}
				if (event.key.keysym.sym == SDLK_RIGHT)
				{
					switch (selectedFish)
					{
					case 1:
						fish1.movingRight = true;
						break;
					case 2:
						fish2.movingRight = true;
						break;
					case 3:
						fish3.movingRight = true;
						break;
					}
				}
			}

			if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					switch (selectedFish)
					{
					case 1:
						fish1.movingLeft = false;
						break;
					case 2:
						fish2.movingLeft = false;
						break;
					case 3:
						fish3.movingLeft = false;
						break;
					}

				}
				if (event.key.keysym.sym == SDLK_RIGHT)
				{
					switch (selectedFish)
					{
					case 1:
						fish1.movingRight = false;
						break;
					case 2:
						fish2.movingRight = false;
						break;
					case 3:
						fish3.movingRight = false;
						break;
					}
				}
			}
			
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

	backgroundTransform.SetPos(glm::vec3(0, 0, 0));
	backgroundTransform.SetRot(glm::vec3(7.94, 1.55, 0));
	backgroundTransform.SetScale(glm::vec3(2, 2, 2));

	backgroundShader->Bind();
	backgroundShader->Update(backgroundTransform, camera1);
	backgroundTexture->Bind(0);
	backgroundMesh.draw();

	MainGameClass::fish1.MoveFish(fish1shader, fish1texture, camera1);
	mesh1.draw();
	fish2.MoveFish(fish2shader, fish2texture, camera1);
	mesh2.draw();
	fish3.MoveFish(fish3shader, fish3texture, camera1);
	mesh3.draw();

	

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	gameDisplay.bufferSwap();
}
