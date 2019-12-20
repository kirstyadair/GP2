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

private:
	float count = 0;
	Transform fishTransform;
};

