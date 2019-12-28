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
	if (!isSelected)
	{
		fishTransform.SetPos(glm::vec3(-count, count / 2, zCoord));
		count += 0.01f;
	}
	else
	{
		if (movingRight)
		{
			count -= 1;
			fishTransform.SetPos(glm::vec3(count, 0, zCoord));
		}

		if (movingLeft)
		{
			count += 1;
			fishTransform.SetPos(glm::vec3(count, 0, zCoord));
		}
	}

	fishTransform.SetRot(glm::vec3(180, 0.0, 0.0));
	shader->Bind();
	shader->Update(fishTransform, camera);
	texture->Bind(0);
}