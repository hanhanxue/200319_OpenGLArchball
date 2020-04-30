

#include "cameraEuler.h"




cameraEuler::cameraEuler()
	: position(glm::vec3(5.0f, 5.0f, 5.0f)), pivot(glm::vec3(0.0f, 0.0f, 0.0f))
{
	updateCamera();

}









void cameraEuler::tumbleCamera(float delta_xpos, float delta_ypos)
{	
	delta_xpos *= TUMBLE_SPEED;
	delta_ypos *= -TUMBLE_SPEED;

	if (pitch + glm::degrees(delta_ypos) > PITCH_CONSTRAINT_UPPER)
	{
		delta_ypos = glm::radians(PITCH_CONSTRAINT_UPPER - pitch);
	}
	else if (pitch + glm::degrees(delta_ypos) < PITCH_CONSTRAINT_LOWER)
	{
		delta_ypos = glm::radians(PITCH_CONSTRAINT_LOWER - pitch);
	}


	glm::mat4 m_tumble = glm::mat4(1.0f);
	m_tumble = glm::rotate(m_tumble, -delta_xpos, worldUp);    // rotate on world Y
	m_tumble = glm::rotate(m_tumble, -delta_ypos, right);    // rotate on target X


	glm::mat4 m_pivot = glm::mat4(1.0f);
	m_pivot = glm::translate(m_pivot, pivot);

	position = m_pivot * m_tumble * glm::inverse(m_pivot) * glm::vec4(position, 1.0f);

	updateCamera();

}

void cameraEuler::trackCamera(float delta_xpos, float delta_ypos)
{
	delta_xpos *= -TRACK_SPEED;
	delta_ypos *= -TRACK_SPEED;

	glm::mat4 m_track = glm::mat4(1.0f);
	m_track = glm::translate(m_track, right * delta_xpos);
	m_track = glm::translate(m_track, up * delta_ypos);

	pivot = m_track * glm::vec4(pivot, 1.0f);
	position = m_track * glm::vec4(position, 1.0f);

	updateCamera();
	printf("pivot: %f %f %f    position: %f %f %f\n", pivot.x, pivot.y, pivot.z, position.x, position.y, position.z);
}


























void cameraEuler::updateCamera()
{
	front = glm::normalize(pivot - position);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));


	view = glm::lookAt(position, position + front, up);


	pitch = glm::degrees(acos(glm::dot(front, worldUp)));

}




glm::mat4 cameraEuler::getViewMatrix() const
{
	return view;
}


glm::mat4 cameraEuler::getPivotMatrix() const
{
	glm::mat4 m_pivot = glm::mat4(1.0f);
	m_pivot = glm::translate(m_pivot, pivot);
	return m_pivot;
}

cameraEuler::~cameraEuler()
{

}