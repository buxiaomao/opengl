#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Shader.h"  
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Camera.h"

#pragma region model data

GLfloat vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
glm::vec3(0.0f,  0.0f,  0.0f),
glm::vec3(2.0f,  5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f,  3.0f, -7.5f),
glm::vec3(1.3f, -2.0f, -2.5f),
glm::vec3(1.5f,  2.0f, -2.5f),
glm::vec3(1.5f,  0.2f, -1.5f),
glm::vec3(-1.3f,  1.0f, -1.5f)
};

#pragma endregion

// camera declare
Camera camera(glm::vec3(0, 0, 3), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1, 0));

#pragma region input declare
float lastx;
float lasty;
bool firstmouse = true;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
	// 关闭应用程序
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		camera.speedz = -0.01f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		camera.speedz = 0.01f;
	}
	else
	{
		camera.speedz = 0.0f;
	}

}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstmouse == true)
	{
		lastx = xpos;
		lasty = ypos;
		firstmouse = false;
	}
	float deltax, deltay;
	deltax = xpos - lastx;
	deltay = ypos - lasty;

	lastx = xpos;
	lasty = ypos;
	camera.ProcessMouseMovement(deltax, deltay);
	cout << deltax << endl;
}
#pragma endregion

// load image to GPU
unsigned int LoadImagetoGPU(const char * filename, GLint internalformat,GLenum format)
{
	unsigned int texturebuff;
	glGenTextures(1, &texturebuff);
	glBindTexture(GL_TEXTURE_2D, texturebuff);
	// 加载图片
	int width, height, nrchannel;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* image = stbi_load(filename, &width, &height, &nrchannel, 0);
	if (image)
	{
		// 生成2d 纹理和 texture 没有关系 但是自动会关联 ourTexture
		glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load image error";
	}
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texturebuff;
}

int main()
{
#pragma region openwindow
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// opengl glfw window 开窗
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);


	// init glew 初始化glew
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("init glew failed.");
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
#pragma endregion
	// init shader program
	Shader * myshader = new Shader("shader.vs", "shader.frag");

#pragma region init adn load models to vao vbo
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// 顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//// 颜色属性
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	// 颜色属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑vbo
	glBindVertexArray(0); // 解绑 vao
#pragma endregion

#pragma region init and load textures
	GLuint textureA;
	// LoadImagetoGPU(const char * filename, GLint internalformat,GLenum format, unsigned int &texturebuff)
	textureA = LoadImagetoGPU("container.jpg", GL_RGB, GL_RGB);
	GLuint textureB;
	textureB = LoadImagetoGPU("awesomeface.png", GL_RGBA, GL_RGBA);
#pragma endregion

#pragma region MVP martices

	// 模型矩阵 M
	glm::mat4 modelMat = glm::mat4(1.0f);

	// 视图矩阵 V
	glm::mat4 viewmat = glm::mat4(1.0f);

	// 投影矩阵 P
	glm::mat4 projMat;
	projMat = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
#pragma endregion

	


	// 窗口消息接收
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		// 设置视图矩阵
		viewmat = camera.GetViewMartix();
	
		for (GLuint i = 0; i < 10; i++)
		{
			// 设置模型矩阵
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			
			// 设置视图和投影矩阵 如果你想

			// 设置材质的贴图
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureA);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textureB);

			// 设置材质shader
			myshader->Use();
			// 设置材质uniform
			glUniform1i(glGetUniformLocation(myshader->Program, "ourTexture2"), 1);
			glUniform1i(glGetUniformLocation(myshader->Program, "ourTexture1"), 0);
			glUniformMatrix4fv(glGetUniformLocation(myshader->Program, "viewmat"), 1, GL_FALSE, glm::value_ptr(viewmat));
			glUniformMatrix4fv(glGetUniformLocation(myshader->Program, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			glUniformMatrix4fv(glGetUniformLocation(myshader->Program, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));

			// 设置要画的模型
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}
		
		glfwSwapBuffers(window);
		camera.updatecamerapos();
	}
	glfwTerminate();
	return 0;

	return 0;

}