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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
	// 关闭应用程序
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}



int main()
{

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

	Shader * myshader = new Shader("shader.vs", "shader.frag");


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


	GLuint textureA;
	glGenTextures(1, &textureA);
	glBindTexture(GL_TEXTURE_2D, textureA);
	// 加载图片
	int width, height,nrchannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load("container.jpg", &width, &height, &nrchannel,0);
	if (image)
	{
		// 生成2d 纹理和 texture 没有关系 但是自动会关联 ourTexture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load image error";
	}
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint textureB;
	glGenTextures(1, &textureB);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureB);
	unsigned char* image2 = stbi_load("awesomeface.png", &width, &height, &nrchannel, 0);
	if (image2)
	{
		// 生成2d 纹理和 texture 没有关系 但是自动会关联 ourTexture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load image error";
	}
	stbi_image_free(image2);
	glBindTexture(GL_TEXTURE_2D, 0);

	

	// 矩阵产生
	glm::mat4 trans = glm::mat4(1.0f);
	////平移
	//trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0));
	//// 旋转
	//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0, 0, 1.0f));
	//// 缩放
	////trans = glm::scale(trans, glm::vec3(2, 2, 0));
	Camera camera(glm::vec3(0,0,3),glm::vec3(0,0,0),glm::vec3(0,1,0));

	// 模型矩阵
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(90.0f), glm::vec3(0, 0, 1));
	
	// 视图矩阵
	glm::mat4 viewmat = glm::mat4(1.0f);
	//viewmat = glm::translate(viewmat, glm::vec3(0, 0, -3.0f));
	viewmat = camera.GetViewMartix();

	// 投影矩阵
	glm::mat4 projMat;
	projMat = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

	glfwSetKeyCallback(window, key_callback);
	// 窗口消息接收
	while (!glfwWindowShouldClose(window))
	{
	
	
		glfwPollEvents();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


		// 渲染时绑定位置
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureB);
		myshader->Use();
		
		glUniform1i(glGetUniformLocation(myshader->Program, "ourTexture2"), 1);
		glUniform1i(glGetUniformLocation(myshader->Program, "ourTexture1"), 0);
		glUniformMatrix4fv(glGetUniformLocation(myshader->Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		
		glUniformMatrix4fv(glGetUniformLocation(myshader->Program, "viewmat"), 1, GL_FALSE, glm::value_ptr(viewmat));
		glUniformMatrix4fv(glGetUniformLocation(myshader->Program, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		glBindVertexArray(VAO);

		for (GLuint i = 0; i < 10; i++)
		{
			glm::mat4 model2 = glm::mat4(1.0f);
			model2 = glm::translate(model2, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			model2 = glm::rotate(model2, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(myshader->Program, "modelMat"), 1, GL_FALSE, glm::value_ptr(model2));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// 画顶点
//		glDrawArrays(GL_POINTS, 0, 6);
		// 画三角形
		glDrawArrays(GL_TRIANGLES, 0, 36);
// 		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;

	return 0;

}