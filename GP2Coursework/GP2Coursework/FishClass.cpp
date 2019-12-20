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
	fishTransform.SetPos(glm::vec3(x, y, z));
	count = x;
	cout << count << endl;
}


void FishClass::MoveFish(ShaderClass* shader, TextureClass* texture, CameraClass camera)
{
	fishTransform.SetPos(glm::vec3(-count, count / 2, 0.0));
	fishTransform.SetRot(glm::vec3(180, 0.0, 0.0));
	shader->Bind();
	shader->Update(fishTransform, camera);
	texture->Bind(0);
	count += 0.01;

	cout << count << endl;
}