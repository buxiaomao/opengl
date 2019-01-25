#pragma once

#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
class Camera
{
public:
	Camera(glm::vec3 _position, glm::vec3 _tartet, glm::vec3 worldup);
	Camera(glm::vec3 _position, float pitch, float yaw, glm::vec3 worldup);
	~Camera();
	glm::vec3 Positon;
	glm::vec3 Forward;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 Worldup;

	GLfloat Yaw;
	GLfloat Pitch;

	float sensex = 0.01f;
	float sensey = 0.01f;
	float speedz = 0.0f;


	glm::mat4 GetViewMartix();

	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);

	void updatecamerapos();

private:
	void updateCameraVectors();

};

