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
			// Move left
			xcount += 0.01f * speed;
		}
		else
		{
			// Move right
			xcount -= 0.01f * speed;
			
		}

		if (hasHitTopWall)
		{
			ycount -= 0.005f * speed;
		}
		else
		{
			ycount += 0.005f * speed;
		}

		if (maxX <= -64)
		{
			hasHitRightWall = true;
			hasHitLeftWall = false;
		}

		if (minX >= 64)
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
			hasHitBottomWall = true;
			hasHitTopWall = false;
		}
	}
	else
	{
		if (movingRight && !hasHitRightWall)
		{
			xcount -= 0.05f * speed;
		}

		if (movingLeft && !hasHitLeftWall)
		{
			xcount += 0.05f * speed;
		}

		if (movingDown && !hasHitBottomWall)
		{
			ycount -= 0.05f * speed;
		}

		if (movingUp && !hasHitTopWall)
		{
			ycount += 0.05f * speed;
		}

		if (maxX <= -64)
		{
			hasHitRightWall = true;
		}
		else
		{
			hasHitRightWall = false;
		}

		if (minX >= 64)
		{
			hasHitLeftWall = true;
		}
		else
		{
			hasHitLeftWall = false;
		}

		if (maxY >= 84)
		{
			hasHitTopWall = true;
		}
		else
		{
			hasHitTopWall = false;
		}

		if (minY <= -84)
		{
			hasHitBottomWall = true;
		}
		else
		{
			hasHitBottomWall = false;
		}
	}

	fishTransform.SetPos(glm::vec3(xcount, ycount / 2, zCoord));
	maxX = xcount - (xLength / 2);
	minX = maxX + xLength;
	maxY = ycount + (yLength / 2);
	minY = maxY - yLength;
	maxZ = zCoord + (zLength / 2);
	minZ = maxZ - zLength;

	fishTransform.SetRot(glm::vec3(rot, rot, rot));
	shader->Bind();
	shader->Update(fishTransform, camera);
	texture->Bind(0);
}