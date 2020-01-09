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
#include "AudioClass.h"

class MainGameClass
{
public:
	// Constructor and deconstructor
	MainGameClass();
	~MainGameClass();
	// Public methods
	void loadModelsFromFile();
	void run();

	// Variables
	CameraClass camera1;
	bool gamePlaying = true;
	static int selectedFish;

private:

	// Private methods
	void gameLoop();
	void drawGame();
	void CheckForCollisions();

	// Instances
	DisplayClass gameDisplay;
	MeshClass mesh1;
	MeshClass mesh2;
	MeshClass mesh3;
	MeshClass backgroundMesh;
	Transform backgroundTransform;
	FishClass fish1;
	FishClass fish2;
	FishClass fish3;

	// Variables
	float timer1;
	float timer2;
	float timer3;
	char keyboardInput;
	
	// Pointers
	ShaderClass *fish1shader;
	ShaderClass *fish2shader;
	ShaderClass *fish3shader;
	ShaderClass *backgroundShader;
	TextureClass *fish1texture;
	TextureClass *fish2texture;
	TextureClass *fish3texture;
	TextureClass *backgroundTexture;
	
	// Audio files
	unsigned int backgroundFile;
	unsigned int popFile;
	unsigned int thudFile;

};
