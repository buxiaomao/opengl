#pragma once
#include "Shader.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
class Material
{
public:
	Shader * shader;
	glm::vec3 ambient;
	unsigned int diffuse;
	unsigned int specular;
	float shinness;



	Material(Shader * _shader, unsigned int  _diffuse, glm::vec3 _ambient, unsigned int  _specular, float _shinness);
	~Material();
};

