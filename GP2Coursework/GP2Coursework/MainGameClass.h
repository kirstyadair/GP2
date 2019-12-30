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
	static int selectedFish;

private:

	void gameLoop();
	void drawGame();
	void CheckForCollisions();

	DisplayClass gameDisplay;
	MeshClass mesh1;
	MeshClass mesh2;
	MeshClass mesh3;
	MeshClass backgroundMesh;
	Transform backgroundTransform;

	FishClass fish1;
	FishClass fish2;
	FishClass fish3;

	float counter;
	char keyboardInput;
	

	ShaderClass *fish1shader;
	ShaderClass *fish2shader;
	ShaderClass *fish3shader;
	ShaderClass *backgroundShader;
	TextureClass *fish1texture;
	TextureClass *fish2texture;
	TextureClass *fish3texture;
	TextureClass *backgroundTexture;

};
