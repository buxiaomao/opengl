#include "Material.h"


Material::Material(Shader * _shader, unsigned int  _diffuse, glm::vec3 _ambient, unsigned int  _specular, float _shinness):
	shader(_shader),
	diffuse(_diffuse),
	specular(_specular),
	ambient(_ambient),
	shinness(_shinness)
{
}

Material::~Material()
{
}
