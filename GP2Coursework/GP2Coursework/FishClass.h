#pragma once
#include "Transform.h"
#include "ShaderClass.h"
#include "TextureClass.h"

class FishClass
{
public:
	FishClass();
	~FishClass();
	void MoveFish(ShaderClass* shader, TextureClass* texture, CameraClass camera);
	void SetStartPos(float x, float y, float z);
	bool isSelected = false;
	bool movingLeft = false;
	bool movingRight = false;
	bool movingUp = false;
	bool movingDown = false;

private:
	float count = 0;
	float zCoord = 0;
	float xMax = 0;
	float xMin = 0;
	float yMax = 0;
	float yMin = 0;
	float zMax = 0;
	float zMin = 0;
//	SDL_Rect boundingBox;
	Transform fishTransform;
};

