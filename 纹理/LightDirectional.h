#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
class LightDirectional
{
public:
	LightDirectional();
	~LightDirectional();

	glm::vec3 positon;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0,0,1);	
	glm::vec3 color;

	void updatadirection()
	{
		direction = glm::vec3(0, 0, 1);
		direction = glm::rotateZ(direction, angles.z);
		direction = glm::rotateX(direction, angles.x);
		direction = glm::rotateY(direction, angles.y);
		direction = -1.0f * direction;

	}


};

