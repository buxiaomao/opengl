#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
using namespace std;
class Shader
{
public:
	GLuint Program;
	// Constructor generates the shader on the fly
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	enum Slot
	{
		DIFFUSE,
		SPECULAR
	};

	// Uses the current shader
	void Use();
	void SetUniform3f(const char * paramNamestring ,glm::vec3 param);
	void SetUniform1f(const char * paramNamestring, float param);
	void SetUniform1i(const char * paramNamestring, int sloat);
	
};
