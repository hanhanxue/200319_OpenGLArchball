#pragma once

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

enum camera_dir
{
	FORWARD, 
	BACKWARD, 
	LEFT, 
	RIGHT,
};


class Camera
{
private:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;

	float Yaw = -90.0f;
	float Pitch = 0.0f;

	float MovementSpeed = 2.5f;


public:
	Camera();

	glm::mat4 GetViewMatrix();

	void UpdatePosition(camera_dir direction, float deltaTime);

	void UpdateFront(float xoffset, float yoffset, bool constrainPitch = true);
};

