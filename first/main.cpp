#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Shader.h"
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ���û�����ESC��,��������window���ڵ�WindowShouldClose����Ϊtrue
	// �ر�Ӧ�ó���
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}



int main()
{
	
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
		// λ�� // ��ɫ
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // ����
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // ����
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // ����

		0.8f,0.8f, 0.0f,0.3f,0.5f,0.7f
	};
	GLuint indices[] = { // ��ʼ��0!
		0, 3, 2, // ��һ��������
		1, 2, 0 // �ڶ���������
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // ���vbo

	glBindVertexArray(0); // ��� vao



	glfwSetKeyCallback(window, key_callback);
	// ������Ϣ����
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);



		myshader->Use();
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