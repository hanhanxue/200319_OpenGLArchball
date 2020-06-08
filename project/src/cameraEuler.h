#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


class cameraEuler
{

public:
	cameraEuler(float width = 1280.0f, float height = 720.0f);


	void home();

	void tumble(float delta_xpos, float delta_ypos);
	void track(float delta_xpos, float delta_ypos);
	void dolly(float delta_xpos, float delta_ypos);
	void zoom(float delta_xpos, float delta_ypos);


	void setAspectRatio(float width, float height);

	glm::vec3 getPositionVec() const;
	glm::vec3 getFrontVec() const;

	glm::mat4 getPivotMatrix() const;
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;

	~cameraEuler();


private:

	const float TUMBLE_SPEED = 0.005f;
	const float TRACK_SPEED = 0.005f;
	const float DOLLY_SPEED = 0.005f;
	const float ZOOM_SPEED = 0.05f;

	const float PITCH_CONSTRAINT_UPPER = 179.9f;
	const float PITCH_CONSTRAINT_LOWER = 0.1f;
	const glm::vec3 WORLDUP = glm::vec3(0.0f, 1.0f, 0.0f);

	const float MIN_FOV = 18.0f;
	const float MAX_FOV = 120.0f;

	float frontSwitch = 1.0f;


	// Camera params
	float pitch;
	float aspectRatio;
	float fov = 45.0f;

	glm::vec3 pivot;
	glm::vec3 position;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	glm::mat4 view;
	glm::mat4 projection;

	void updateCamera();
};

