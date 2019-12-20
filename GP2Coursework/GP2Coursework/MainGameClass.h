#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "DisplayClass.h" 
#include "ShaderClass.h"
#include "MeshClass.h"
#include "TextureClass.h"
#include "Transform.h"
#include "CameraClass.h"
#include "FishClass.h"

class MainGameClass
{
public:
	MainGameClass();
	~MainGameClass();
	void loadModelsFromFile();
	bool gamePlaying = true;
	void run();
	CameraClass camera1;

private:

	void gameLoop();
	void drawGame();

	DisplayClass gameDisplay;
	MeshClass mesh1;
	MeshClass mesh2;

	FishClass fish1;
	FishClass fish2;
	FishClass fish3;

	float counter;
	ShaderClass *fish1shader;
	ShaderClass *fish2shader;
	TextureClass *fish1texture;
	TextureClass *fish2texture;

};
