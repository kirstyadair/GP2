#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct CameraClass
{
public:
	// Declare initialiseCamera method
	void initialiseCamera(const glm::vec3& position, float fieldOfView, float aspectRatio, float nearClip, float farClip)
	{
		// Assign variable values
		this->pos = position;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fieldOfView, aspectRatio, nearClip, farClip);
	}

	// Declare GetViewProjection method
	inline glm::mat4 GetViewProjection() const
	{
		// Return view projection
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	
protected:
private:
	// Private variables
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};

