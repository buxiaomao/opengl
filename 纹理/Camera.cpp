#include "Camera.h"



Camera::Camera(glm::vec3 _position, glm::vec3 _tartet, glm::vec3 worldup)
{
	//∑ΩœÚº∆À„
	Positon = _position;
	Forward = glm::normalize(_tartet - _position);
	right = glm::normalize(glm::cross(Forward, worldup));
	up = glm::normalize(glm::cross(Forward, right));


}
glm::mat4 Camera::GetViewMartix()
{
	glm::mat4 view;
	view = glm::lookAt(Positon, Positon + Forward, worldup);
	return view;
}

Camera::~Camera()
{
}
