#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	enum class DIR
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	Camera(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), float yaw = -90.f, float pitch = 0, float speed = 5.f);
	~Camera();

	void move(DIR dir, float deltaTime);

	void setMouseSensivity(float sensivity);
	float getMouseSensivity();

	void mouseOffset(glm::fvec2 mouseOffset, bool constrainPitch = true);
	void scrollOffset(float scrollOffset);

	inline glm::mat4 GetViewMatrix();


private:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 front;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float speed;
	float mouseSensitivity;

	void updateVectors();
};
