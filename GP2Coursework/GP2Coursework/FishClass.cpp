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
	// Assign coordinate variables
	xCoord = x;
	yCoord = y;
	zCoord = z;
	// Set the fish position using these values
	fishTransform.SetPos(glm::vec3(x, y, z));
}


void FishClass::SetBoundingBox(float x, float y, float z)
{
	// Set the box dimensions using the lengths provided
	xLength = x;
	yLength = y;
	zLength = z;
}


void FishClass::MoveFish(ShaderClass* shader, TextureClass* texture, CameraClass camera)
{
	// If the fish is not currently selected, move without user input
	if (!isSelected)
	{
		if (hasHitRightWall)
		{
			// Move left
			xCoord += 0.01f * speed;
		}
		else
		{
			// Move right
			xCoord -= 0.01f * speed;
			
		}

		if (hasHitTopWall)
		{
			// Move down
			yCoord -= 0.005f * speed;
		}
		else
		{
			// Move up
			yCoord += 0.005f * speed;
		}

		// Check if the fish has hit the right boundary
		if (maxX <= -64)
		{
			hasHitRightWall = true;
			hasHitLeftWall = false;
		}
		// Check if the fish has hit the left boundary
		if (minX >= 64)
		{
			hasHitLeftWall = true;
			hasHitRightWall = false;
		}
		// Check if the fish has hit the top boundary
		if (maxY >= 84)
		{
			hasHitTopWall = true;
			hasHitBottomWall = false;
		}
		// Check if the fish has hit the bottom boundary
		if (minY <= -84)
		{
			hasHitBottomWall = true;
			hasHitTopWall = false;
		}
	}
	else
	{
		// movingRight, movingLeft, movingUp and movingDown are set by user input
		if (movingRight && !hasHitRightWall)
		{
			// Move right
			xCoord -= 0.05f * speed;
		}

		if (movingLeft && !hasHitLeftWall)
		{
			// Move left
			xCoord += 0.05f * speed;
		}

		if (movingDown && !hasHitBottomWall)
		{
			// Move down
			yCoord -= 0.05f * speed;
		}

		if (movingUp && !hasHitTopWall)
		{
			// Move up
			yCoord += 0.05f * speed;
		}

		// Check for collisions with boundaries
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

	// Set the position of the fish after updating the x and y coordinates
	fishTransform.SetPos(glm::vec3(xCoord, yCoord / 2, zCoord));
	// Re-assign the min and max coordinates for the bounding box
	maxX = xCoord - (xLength / 2);
	minX = maxX + xLength;
	maxY = yCoord + (yLength / 2);
	minY = maxY - yLength;
	maxZ = zCoord + (zLength / 2);
	minZ = maxZ - zLength;

	// Set the rotation, which is changed when collisions occur
	fishTransform.SetRot(glm::vec3(rot, rot, rot));
	// Bind and update the shader
	shader->Bind();
	shader->Update(fishTransform, camera);
	// Bind the texture
	texture->Bind(0);
}