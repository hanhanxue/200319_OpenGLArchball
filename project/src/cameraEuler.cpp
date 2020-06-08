

#include "cameraEuler.h"


cameraEuler::cameraEuler(float width, float height)
	: position(glm::vec3(5.0f, 5.0f, 5.0f)), pivot(glm::vec3(0.0f, 0.0f, 0.0f)), aspectRatio(width / height)
{
	updateCamera();
}


void cameraEuler::home()
{
	position = glm::vec3(5.0f, 5.0f, 5.0f);
	pivot = glm::vec3(0.0f, 0.0f, 0.0f);

	fov = 45.0f;

	updateCamera();
}

void cameraEuler::tumble(float delta_xpos, float delta_ypos)
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
	m_tumble = glm::rotate(m_tumble, -delta_xpos, WORLDUP);    // rotate on world Y
	m_tumble = glm::rotate(m_tumble, -delta_ypos, right);    // rotate on target X


	glm::mat4 m_pivot = glm::mat4(1.0f);
	m_pivot = glm::translate(m_pivot, pivot);

	position = m_pivot * m_tumble * glm::inverse(m_pivot) * glm::vec4(position, 1.0f);

	updateCamera();

}

void cameraEuler::track(float delta_xpos, float delta_ypos)
{
	delta_xpos *= -TRACK_SPEED;
	delta_ypos *= -TRACK_SPEED;

	glm::mat4 m_track = glm::mat4(1.0f);
	m_track = glm::translate(m_track, right * delta_xpos);
	m_track = glm::translate(m_track, up * delta_ypos);

	pivot = m_track * glm::vec4(pivot, 1.0f);
	position = m_track * glm::vec4(position, 1.0f);

	updateCamera();
	//printf("pivot: %f %f %f    position: %f %f %f\n", pivot.x, pivot.y, pivot.z, position.x, position.y, position.z);
}

void cameraEuler::dolly(float delta_xpos, float delta_ypos)
{
	delta_xpos *= -DOLLY_SPEED;
	delta_ypos *= -DOLLY_SPEED;

	glm::mat4 m_dolly = glm::mat4(1.0f);
	m_dolly = glm::translate(m_dolly, front * (delta_ypos - delta_xpos));

	position = m_dolly * glm::vec4(position, 1.0f);

	frontSwitch = glm::dot(glm::normalize(pivot - position), front);

	updateCamera();
}

void cameraEuler::zoom(float delta_xpos, float delta_ypos)
{
	delta_xpos *= ZOOM_SPEED;
	delta_ypos *= ZOOM_SPEED;

	fov += delta_ypos - delta_xpos;
	fov = glm::clamp(fov, MIN_FOV, MAX_FOV);

	//printf("%f\n", fov);

	updateCamera();
}







void cameraEuler::setAspectRatio(float width, float height)
{
	aspectRatio = width / height;
	updateCamera();
}

glm::mat4 cameraEuler::getPivotMatrix() const
{
	glm::mat4 m_pivot = glm::mat4(1.0f);
	m_pivot = glm::translate(m_pivot, pivot);
	return m_pivot;
}

glm::mat4 cameraEuler::getViewMatrix() const
{
	return view;
}


glm::mat4 cameraEuler::getProjectionMatrix() const
{
	return projection;
}

glm::vec3 cameraEuler::getPositionVec() const
{
	return position;
}

glm::vec3 cameraEuler::getFrontVec() const
{
	return front;
}




void cameraEuler::updateCamera()
{

	front = glm::normalize((pivot - position) * frontSwitch);

	right = glm::normalize(glm::cross(front, WORLDUP));
	up = glm::normalize(glm::cross(right, front));


	pitch = glm::degrees(acos(glm::dot(front, WORLDUP)));

	view = glm::lookAt(position, position + front, up);
	projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}



cameraEuler::~cameraEuler()
{

}