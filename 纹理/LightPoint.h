#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

class LightPoint
{
public:
	glm::vec3 positon;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1);
	glm::vec3 color;

	LightPoint(glm::vec3 _position, glm::vec3 _angle, glm::vec3 _color = glm::vec3(1, 1, 1));
	~LightPoint();

	float constant;
	float liner;
	float quadratic;
};

