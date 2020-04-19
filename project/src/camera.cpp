#include "camera.h"


Camera::Camera()
	: Position(glm::vec3(0.0f, 0.0f, 15.0f)), 
	  Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
	  Up(glm::vec3(0.0f, 1.0f, 0.0f))
{

}


glm::mat4 Camera::GetViewMatrix()
{

	return glm::lookAt(Position, Position + Front, Up);

}

void Camera::UpdatePosition(camera_dir direction, float deltaTime)
{
	float magnitude = MovementSpeed * deltaTime;
	if (direction == FORWARD)
	{
		Position += Front * magnitude;
	}
	if (direction == BACKWARD)
	{
		Position -= Front * magnitude;
	}
	if (direction == LEFT)
	{
		Position += glm::normalize(glm::cross(Up, Front)) * magnitude;
	}
	if (direction == RIGHT)
	{
		Position += glm::normalize(glm::cross(Front, Up)) * magnitude;
	}
}

void Camera::UpdateFront(float xoffset, float yoffset, bool constrainPitch)
{

	const float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	Pitch += yoffset;
	Yaw += xoffset;

	if (Pitch > 89.0f) Pitch = 89.0f;
	if (Pitch < -89.0f) Pitch = -89.0f;

	glm::vec3 front;

	front.x = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw));
	front.y = glm::sin(glm::radians(Pitch));
	front.z = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw));


	Front = glm::normalize(front);

}