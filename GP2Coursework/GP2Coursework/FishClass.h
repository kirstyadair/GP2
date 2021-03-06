#pragma once
#include "Transform.h"
#include "ShaderClass.h"
#include "TextureClass.h"

class FishClass
{
public:
	// Constructor and deconstructor
	FishClass();
	~FishClass();
	// Public methods
	void MoveFish(ShaderClass* shader, TextureClass* texture, CameraClass camera);
	void SetStartPos(float x, float y, float z);
	void SetBoundingBox(float x, float y, float z);
	// Boolean variables
	bool isSelected = false;
	bool movingLeft = false;
	bool movingRight = false;
	bool movingUp = false;
	bool movingDown = false;
	bool hasHitRightWall = false;
	bool hasHitLeftWall = false;
	bool hasHitTopWall = false;
	bool hasHitBottomWall = false;

	// Float variables
	float maxX = 0;
	float maxY = 0;
	float maxZ = 0;
	float minX = 0;
	float minY = 0;
	float minZ = 0;
	float speed = 1;
	float rot = 1;
	

private:
	//Private variables
	float xCoord = 0;
	float yCoord = 0;
	float zCoord = 0;
	float xLength = 0;
	float yLength = 0;
	float zLength = 0;

	// Transform instance
	Transform fishTransform;
};

