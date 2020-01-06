#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct CameraClass
{
public:
	void initialiseCamera(const glm::vec3& position, float fieldOfView, float aspectRatio, float nearClip, float farClip)
	{
		this->pos = position;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fieldOfView, aspectRatio, nearClip, farClip);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	
protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};

