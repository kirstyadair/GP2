#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "DisplayClass.h" 
#include "ShaderClass.h"
#include "MeshClass.h"
#include "TextureClass.h"
#include "Transform.h"
#include "CameraClass.h"

class MainGameClass
{
public:
	MainGameClass();
	~MainGameClass();
	void loadModelsFromFile();
	bool gamePlaying = true;
	void run();

private:

	void checkGameStatus();
	void gameLoop();
	void drawGame();

	DisplayClass gameDisplay;
	MeshClass mesh1;
	MeshClass mesh2;
	CameraClass camera1;
	Transform transform;

	float counter;

};
