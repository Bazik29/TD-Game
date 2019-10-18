#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(glm::vec3 position, float yaw, float pitch, float speed)
{
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->speed = speed;

	mouseSensitivity = 0.3f;
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	updateVectors();
}

Camera::~Camera()
{}

void Camera::move(DIR dir, float deltaTime)
{
	float velocity = speed * deltaTime;

	switch (dir)
	{
	case Camera::DIR::FORWARD:
		position += front * velocity;
		break;
	case Camera::DIR::BACKWARD:
		position -= front * velocity;
		break;
	case Camera::DIR::LEFT:
		position -= right * velocity;
		break;
	case Camera::DIR::RIGHT:
		position += right * velocity;
		break;
	default:
		break;
	}
}

inline glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::setMouseSensivity(float sensivity)
{
	mouseSensitivity = sensivity;
}

float Camera::getMouseSensivity()
{
	return mouseSensitivity;
}

void Camera::mouseOffset(glm::fvec2 mouseOffset, bool constrainPitch)
{
	float xoffset = mouseOffset.x * mouseSensitivity;
	float yoffset = mouseOffset.y * mouseSensitivity;

	yaw -= xoffset;
	pitch += yoffset;

	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	updateVectors();
}

void Camera::scrollOffset(float scrollOffset)
{
	//TODO
}

void Camera::updateVectors()
{
	glm::vec3 frontTmp;
	frontTmp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontTmp.y = sin(glm::radians(pitch));
	frontTmp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(frontTmp);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}
