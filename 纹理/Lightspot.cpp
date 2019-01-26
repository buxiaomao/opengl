#include "Lightspot.h"



Lightspot::Lightspot(glm::vec3 _position, glm::vec3 _angle, glm::vec3 _color ):
positon(_position),
angles(_angle),
color(_color)
{
	updatadirection();
}


Lightspot::~Lightspot()
{
}
