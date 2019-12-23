#include "FishClass.h"
#include "MainGameClass.h"



FishClass::FishClass()
{
}


FishClass::~FishClass()
{
}


void FishClass::SetStartPos(float x, float y, float z)
{
	count = x;
	zCoord = z;
	fishTransform.SetPos(glm::vec3(x, y, z));
}


void FishClass::MoveFish(ShaderClass* shader, TextureClass* texture, CameraClass camera)
{
	fishTransform.SetPos(glm::vec3(-count, count / 2, zCoord));
	fishTransform.SetRot(glm::vec3(180, 0.0, 0.0));
	shader->Bind();
	shader->Update(fishTransform, camera);
	texture->Bind(0);
	count += 0.01;
}