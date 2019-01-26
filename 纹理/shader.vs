#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec3 Fragpos;
out vec3 Normal;
out vec2 TexCoord; 

uniform mat4 modelMat;
uniform mat4 viewmat;
uniform mat4 projMat;

void main()
{
    gl_Position =  projMat *viewmat*modelMat*vec4(position, 1.0f);
	Fragpos = (modelMat *vec4(position, 1.0)).xyz;
	Normal = mat3(transpose(inverse(modelMat))) *aNormal;
	TexCoord = aTexCoord;

}