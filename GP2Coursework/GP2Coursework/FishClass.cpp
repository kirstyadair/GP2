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
	xcount = x;
	ycount = y;
	zCoord = z;
	fishTransform.SetPos(glm::vec3(x, y, z));
}


void FishClass::SetBoundingBox(float x, float y, float z)
{
	xLength = x;
	yLength = y;
	zLength = z;
}


void FishClass::MoveFish(ShaderClass* shader, TextureClass* texture, CameraClass camera)
{
	if (!isSelected)
	{
		if (hasHitRightWall)
		{
			xcount -= 0.01f;
		}
		else
		{
			xcount += 0.01f;
		}

		if (hasHitTopWall)
		{
			ycount -= 0.005f;
		}
		else
		{
			ycount += 0.005f;
		}
		
		fishTransform.SetPos(glm::vec3(-xcount, ycount / 2, zCoord));
		maxX = xcount + (xLength / 2);
		minX = maxX - xLength;
		maxY = ycount + (yLength/2);
		minY = maxY - yLength;
		maxZ = zCoord + (zLength/2);
		minZ = maxZ - zLength;

		cout << minY << endl;

		
	}
	else
	{
		if (movingRight && !hasHitRightWall)
		{
			xcount -= 0.1;
			maxX = xcount + (xLength / 2);
			minX = maxX - xLength;
			fishTransform.SetPos(glm::vec3(xcount, ycount, zCoord));
		}

		if (movingLeft && !hasHitLeftWall)
		{
			xcount += 0.1;
			maxX = xcount + (xLength / 2);
			minX = maxX - xLength;
			fishTransform.SetPos(glm::vec3(xcount, ycount, zCoord));
		}

		if (movingUp && !hasHitTopWall)
		{
			ycount += 0.05;
			maxY = ycount + (yLength / 2);
			minY = maxY - yLength;
			fishTransform.SetPos(glm::vec3(xcount, ycount, zCoord));
		}

		if (movingDown && !hasHitBottomWall)
		{
			ycount -= 0.05;
			maxY = ycount + (yLength / 2);
			minY = maxY - yLength;
			fishTransform.SetPos(glm::vec3(xcount, ycount, zCoord));
		}
	}

	if (maxX >= 62)
	{
		hasHitRightWall = true;
		hasHitLeftWall = false;
	}
	if (minX <= -62)
	{
		hasHitLeftWall = true;
		hasHitRightWall = false;
	}
	if (maxY >= 84)
	{
		hasHitTopWall = true;
		hasHitBottomWall = false;
	}
	if (minY <= -84)
	{
		hasHitTopWall = false;
		hasHitBottomWall = true;
	}

	fishTransform.SetRot(glm::vec3(0, 0.0, 0.0));
	shader->Bind();
	shader->Update(fishTransform, camera);
	texture->Bind(0);
}