#include "LightDirectional.h"



LightDirectional::LightDirectional(glm::vec3 _position , glm::vec3 _angle, glm::vec3 _color):
	positon(_position),
	angles(_angle),
	color(_color)
{
	updatadirection();
}


LightDirectional::~LightDirectional()
{
}
