#include "Material.h"


Material::Material(Shader * _shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shinness):
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
