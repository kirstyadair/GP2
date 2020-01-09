#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "CameraClass.h"

struct Transform
{
public:
	// Transform constructor 
	Transform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		// Assign variables
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

	// GetModel const method
	inline glm::mat4 GetModel() const
	{
		// Assign variables
		glm::mat4 posMat = glm::translate(position);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		// Return model mat4
		return posMat * rotMat * scaleMat;
	}

	// Getters
	inline glm::vec3* GetPos() { return &position; }
	inline glm::vec3* GetRot() { return &rotation; }
	inline glm::vec3* GetScale() { return &scale; }

	// Setters
	inline void SetPos(glm::vec3 position) { this->position = position; }
	inline void SetRot(glm::vec3 rotation) { this->rotation = rotation; }
	inline void SetScale(glm::vec3 scale) { this->scale = scale; }

private:
	// Private variable
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};


