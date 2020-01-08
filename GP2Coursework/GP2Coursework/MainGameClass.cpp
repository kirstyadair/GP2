#include "MainGameClass.h"
#include <iostream>
#include <string>
#include "CameraClass.h"
#include <glm/glm.hpp>

int MainGameClass::selectedFish = 0;
AudioClass *audioManager = new AudioClass();

MainGameClass::MainGameClass()
{
	// Set the gameplay loop variable to true
	gamePlaying = true;
	// Create a new display
	DisplayClass* gameDisplay = new DisplayClass();

	// Get the view projection matrix and initialise the camera
	camera1.GetViewProjection();
	camera1.initialiseCamera(glm::vec3(0, 0, -100), 70.0f, gameDisplay->getScreenWidth() / gameDisplay->getScreenHeight(), 0.01f, 1000.0f);

	// For each fish, set the starting position and bounding boxes for collisions
	fish1.SetStartPos(0, 0, -2);
	fish1.SetBoundingBox(28.75, 19, 7);
	fish2.SetStartPos(30, 50, 0);
	fish2.SetBoundingBox(49.3, 23.5, 15.5);
	fish3.SetStartPos(0, 0, 2);
	fish3.SetBoundingBox(16.6, 14, 5);

	// Set each fish's speed
	fish1.speed = 3;
	fish2.speed = 1;
	fish3.speed = 5;

	// Set the current selected fish for user input to fish 1
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
	mesh1.loadModel("..\\res\\Models\\Fish1.obj");
	mesh2.loadModel("..\\res\\Models\\tropicalFish2.obj");
	mesh3.loadModel("..\\res\\Models\\fish3.obj");
	backgroundMesh.loadModel("..\\res\\Models\\seafloor.obj");
	// Create shaders
	fish1shader = new ShaderClass("..\\res\\Shader\\shader"); 
	fish2shader = new ShaderClass("..\\res\\Shader\\shader"); 
	fish3shader = new ShaderClass("..\\res\\Shader\\shader"); 
	backgroundShader = new ShaderClass("..\\res\\Shader\\shader"); 
	// Load textures
	fish1texture = new TextureClass("..\\res\\Textures\\Fish1Texture.png");
	fish2texture = new TextureClass("..\\res\\Textures\\Fish2Texture.jpg");
	fish3texture = new TextureClass("..\\res\\Textures\\Fish3Texture.jpg");
	backgroundTexture = new TextureClass("..\\res\\Textures\\SeafloorTexture.jpg");
	// Load sounds
	backgroundFile = audioManager->loadSound("..\\res\\Sounds\\underwater.wav");
	popFile = audioManager->loadSound("..\\res\\Sounds\\PopSound.wav");
	thudFile = audioManager->loadSound("..\\res\\Sounds\\thud.wav");
	// Start playing the background music
	audioManager->playSound(backgroundFile);
	// Set the audio listener position
	glm::vec3 cameraPos = glm::vec3(0, 0, -100);
	audioManager->setlistener(cameraPos, cameraPos);
}

void MainGameClass::gameLoop()
{
	// The game will keep playing while this is true
	while (gamePlaying)
	{
		// Create the event for handling input
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			// When a key is pressed down
			if (event.type == SDL_KEYDOWN)
			{
				// If the key is 1, set Fish 1 to be the selected fish
				if (event.key.keysym.sym == SDLK_1)
				{
					MainGameClass::selectedFish = 1;
					fish1.isSelected = true;
					fish2.isSelected = false;
					fish3.isSelected = false;
				}
				// If the key is 2, set Fish 2 to be the selected fish
				if (event.key.keysym.sym == SDLK_2)
				{
					MainGameClass::selectedFish = 2;
					fish1.isSelected = false;
					fish2.isSelected = true;
					fish3.isSelected = false;
				}
				// If the key is 3, set Fish 3 to be the selected fish
				if (event.key.keysym.sym == SDLK_3)
				{
					MainGameClass::selectedFish = 3;
					fish1.isSelected = false;
					fish2.isSelected = false;
					fish3.isSelected = true;
				}

				// If the left arrow key is pressed, move the selected fish left
				if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
				{
					// Play the pop sound for the key press
					audioManager->playSound(popFile);
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
				// If the right arrow key is pressed, move the selected fish right
				if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
				{
					audioManager->playSound(popFile);
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
				// If the up arrow key is pressed, move the selected fish up
				if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
				{
					audioManager->playSound(popFile);
					switch (selectedFish)
					{
					case 1:
						fish1.movingUp = true;
						break;
					case 2:
						fish2.movingUp = true;
						break;
					case 3:
						fish3.movingUp = true;
						break;
					}

				}
				// If the down arrow key is pressed, move the selected fish down
				if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
				{
					audioManager->playSound(popFile);
					switch (selectedFish)
					{
					case 1:
						fish1.movingDown = true;
						break;
					case 2:
						fish2.movingDown = true;
						break;
					case 3:
						fish3.movingDown = true;
						break;
					}
				}
				// If the esc key is pressed, quit the game
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					gamePlaying = false;
				}
			}

			// When the key press ends
			if (event.type == SDL_KEYUP)
			{
				// If left key no longer pressed, stop going left
				if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
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
				// If right key no longer pressed, stop going right
				if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
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
				// If up key no longer pressed, stop going up
				if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
				{
					switch (selectedFish)
					{
					case 1:
						fish1.movingUp = false;
						break;
					case 2:
						fish2.movingUp = false;
						break;
					case 3:
						fish3.movingUp = false;
						break;
					}

				}
				// If down key no longer pressed, stop going down
				if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
				{
					switch (selectedFish)
					{
					case 1:
						fish1.movingDown = false;
						break;
					case 2:
						fish2.movingDown = false;
						break;
					case 3:
						fish3.movingDown = false;
						break;
					}
				}
			}

			// If the game is quit
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
	// Clear the display
	gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	// Set the background position, rotation and scale
	backgroundTransform.SetPos(glm::vec3(0, 0, 0));
	backgroundTransform.SetRot(glm::vec3(7.94, 1.55, 0));
	backgroundTransform.SetScale(glm::vec3(2, 2, 2));

	// Bind and update the background shader and texture
	backgroundShader->Bind();
	backgroundShader->Update(backgroundTransform, camera1);
	backgroundTexture->Bind(0);
	// Draw the background mesh
	backgroundMesh.draw();

	// Move each fish
	fish1.MoveFish(fish1shader, fish1texture, camera1);
	mesh1.draw();
	fish2.MoveFish(fish2shader, fish2texture, camera1);
	mesh2.draw();
	fish3.MoveFish(fish3shader, fish3texture, camera1);
	mesh3.draw();

	// Check for collisions
	CheckForCollisions();
	
	// Swap buffers
	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();
	gameDisplay.bufferSwap();
}

void MainGameClass::CheckForCollisions()
{
	// Check for any collisions on the X axis for all 3 fish
	bool collisionXF1F2 = (fish2.maxX >= fish1.maxX) && (fish2.maxX <= fish1.minX) || (fish1.maxX >= fish2.maxX) && (fish1.maxX <= fish2.minX);
	bool collisionXF2F3 = (fish2.maxX >= fish3.maxX) && (fish2.maxX <= fish3.minX) || (fish3.maxX >= fish2.maxX) && (fish3.maxX <= fish2.minX);
	bool collisionXF1F3 = (fish1.maxX >= fish3.maxX) && (fish1.maxX <= fish3.minX) || (fish3.maxX >= fish1.maxX) && (fish3.maxX <= fish1.minX);

	// Check for any collisions on the Y axis
	bool collisionYF1F2 = (fish2.maxY <= fish1.maxY) && (fish2.maxY >= fish1.minY) || (fish1.maxY <= fish2.maxY) && (fish1.maxY >= fish2.minY);
	bool collisionYF2F3 = (fish2.maxY <= fish3.maxY) && (fish2.maxY >= fish3.minY) || (fish3.maxY <= fish2.maxY) && (fish3.maxY >= fish2.minY);
	bool collisionYF1F3 = (fish1.maxY <= fish3.maxY) && (fish1.maxY >= fish3.minY) || (fish3.maxY <= fish1.maxY) && (fish3.maxY >= fish1.minY);

	// Check for any collisions on the Z axis
	bool collisionZF1F2 = (fish2.maxZ <= fish1.maxZ) && (fish2.maxZ >= fish1.minZ) || (fish1.maxZ <= fish2.maxZ) && (fish1.maxZ >= fish2.minZ);
	bool collisionZF2F3 = (fish2.maxZ <= fish3.maxZ) && (fish2.maxZ >= fish3.minZ) || (fish3.maxZ <= fish2.maxZ) && (fish3.maxZ >= fish2.minZ);
	bool collisionZF1F3 = (fish1.maxZ <= fish3.maxZ) && (fish1.maxZ >= fish3.minZ) || (fish3.maxZ <= fish1.maxZ) && (fish3.maxZ >= fish1.minZ);

	if (collisionXF1F2 && collisionYF1F2 && collisionZF1F2)
	{
		fish1.rot += 0.01;
		fish2.rot += 0.01;
		timer1 += 0.005f;

		if (timer1 >= 1.0f)
		{
			timer1 = 0;
			audioManager->playSound(thudFile);
		}
		
	}

	if (collisionXF2F3 && collisionYF2F3 && collisionZF2F3)
	{
		fish3.rot += 0.01;
		fish2.rot += 0.01;
		timer2 += 0.005f;

		if (timer2 >= 1.0f)
		{
			timer2 = 0;
			audioManager->playSound(thudFile);
		}
	}

	if (collisionXF1F3 && collisionYF1F3 && collisionZF1F3)
	{
		fish1.rot += 0.01;
		fish3.rot += 0.01;
		timer3 += 0.005f;

		if (timer3 >= 1.0f)
		{
			timer3 = 0;
			audioManager->playSound(thudFile);
		}
	}
}
