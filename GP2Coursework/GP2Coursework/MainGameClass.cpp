#include "MainGameClass.h"
#include <iostream>
#include <string>
#include "CameraClass.h"
#include <glm/glm.hpp>

unsigned int indices[] = { 0, 1, 2 };
Transform transform;


MainGameClass::MainGameClass()
{
	gameState = GameState::PLAY;
	DisplayClass* gameDisplay = new DisplayClass(); //new display
	counter = 0.0f;

	MeshClass Mesh1();
	camera1.GetViewProjection();
	camera1.initialiseCamera(glm::vec3(0, 0, -5), 70.0f, gameDisplay->getScreenWidth() / gameDisplay->getScreenHeight(), 0.01f, 1000.0f);

}

void MainGameClass::run()
{
	initialiseSystems();
	gameLoop();
}

void MainGameClass::initialiseSystems()
{
	gameDisplay.initialiseDisplay();
	mesh1.loadModel("C:\\Users\\kirst\\Downloads\\monkey3.obj");
}

void MainGameClass::gameLoop()
{
	while (gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}

void MainGameClass::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		}
	}

}


void MainGameClass::drawGame()
{
	gameDisplay.clearDisplay(0.0f, 1.0f, 1.0f, 1.0f);

	ShaderClass shader("..\\res\\shader"); //new shader
	TextureClass texture("..\\res\\bricks.jpg"); //load texture
	TextureClass texture1("..\\res\\water.jpg"); //load texture

	transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));
	
	shader.Bind();
	shader.Update(transform, camera1);
	texture.Bind(0);
	mesh1.draw();
	counter = counter + 0.01f;

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	gameDisplay.bufferSwap();
}
