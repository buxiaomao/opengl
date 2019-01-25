#include "Camera.h"



Camera::Camera(glm::vec3 _position, glm::vec3 _tartet, glm::vec3 worldup)
{
	//∑ΩœÚº∆À„
	Positon = _position;
	Worldup = worldup;
	Forward = glm::normalize(_tartet - _position);
	right = glm::normalize(glm::cross(Forward, worldup));
	up = glm::normalize(glm::cross(Forward, right));


}
Camera::Camera(glm::vec3 _position, float pitch, float yaw, glm::vec3 worldup)
{

	Positon = _position;
	Worldup = worldup;
	Forward.x = glm::cos(pitch)*glm::sin(yaw);
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch)* glm::cos(yaw);
	right = glm::normalize(glm::cross(Forward, worldup));
	up = glm::normalize(glm::cross(Forward, right));

}
glm::mat4 Camera::GetViewMartix()
{
	glm::mat4 view;
	view = glm::lookAt(Positon, Positon + Forward, Worldup);
	return view;
}

Camera::~Camera()
{
}
