#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "DisplayClass.h" 
#include "ShaderClass.h"
#include "MeshClass.h"
#include "TextureClass.h"
#include "Transform.h"
#include "CameraClass.h"

enum class GameState { PLAY, EXIT };

class MainGameClass
{
public:
	MainGameClass();
	~MainGameClass();

	void run();

private:

	void initialiseSystems();
	void processInput();
	void gameLoop();
	void drawGame();

	DisplayClass gameDisplay;
	GameState gameState;
	MeshClass mesh1;
	MeshClass mesh2;
	CameraClass camera1;

	float counter;

};
