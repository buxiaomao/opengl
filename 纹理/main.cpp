#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Shader.h"  
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ���û�����ESC��,��������window���ڵ�WindowShouldClose����Ϊtrue
	// �ر�Ӧ�ó���
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}



int main()
{
	//glm::vec4 vec(1, 0, 0, 1);
	//glm::mat4 trans= glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(2.0f,1, 0)); 
	//vec = trans * vec;
	//cout << vec.x << endl << vec.y << endl << vec.z << endl;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// opengl glfw window ����
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// init glew ��ʼ��glew
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("init glew failed.");
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);


	Shader * myshader = new Shader("shader.vs", "shader.frag");


	GLfloat vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	};
	GLuint indices[] = { // ��ʼ��0!
		0, 1, 2, // ��һ��������
		2, 3, 0 // �ڶ���������
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// ��������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// ��ɫ����
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // ���vbo
	glBindVertexArray(0); // ��� vao


	GLuint textureA;
	glGenTextures(1, &textureA);
	glBindTexture(GL_TEXTURE_2D, textureA);
	// ����ͼƬ
	int width, height,nrchannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load("container.jpg", &width, &height, &nrchannel,0);
	if (image)
	{
		// ����2d ����� texture û�й�ϵ �����Զ������ ourTexture
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
		// ����2d ����� texture û�й�ϵ �����Զ������ ourTexture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load image error";
	}
	stbi_image_free(image2);
	glBindTexture(GL_TEXTURE_2D, 0);


	// �������
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(-1.0f, 1, 0));

	
	glfwSetKeyCallback(window, key_callback);
	// ������Ϣ����
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);


		// ��Ⱦʱ��λ��
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureB);
		myshader->Use();
		
		
		

		glUniform1i(glGetUniformLocation(myshader->Program, "ourTexture2"), 1);
		glUniform1i(glGetUniformLocation(myshader->Program, "ourTexture1"), 0);
		glUniformMatrix4fv(glGetUniformLocation(myshader->Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		glBindVertexArray(VAO);
		glPointSize(5);
		// ������
//		glDrawArrays(GL_POINTS, 0, 6);
		// ��������
//		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;

	return 0;

}