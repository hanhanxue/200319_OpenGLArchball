#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


class cameraEuler
{

public:
	cameraEuler();



	void tumbleCamera(float delta_xpos, float delta_ypos);
	void trackCamera(float delta_xpos, float delta_ypos);
	//void dollyCamera();


	glm::mat4 getViewMatrix() const;
	glm::mat4 getPivotMatrix() const;

	~cameraEuler();


private:
	const float TUMBLE_SPEED = 0.005f;
	const float TRACK_SPEED = 0.005f;
	const float DOLLY_SPEED = 1.0f;


	const float PITCH_CONSTRAINT_UPPER = 179.9f;
	const float PITCH_CONSTRAINT_LOWER = 0.1f;

	glm::mat4 view;
	const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float pitch = 0.0f;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;


	glm::vec3 pivot;
	glm::vec3 position;




	void updateCamera();
};

