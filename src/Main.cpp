#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "Shader.hpp"
#include<thread>
#include<chrono>
#include"square.hpp"
#include<vector>
using namespace std;

const int width = 500, height = 500;
const string title = "Blocks Game";
std::vector<Square*> vector1;

void draw(Shader& program, std::vector<Square*> vector1) {
	for (auto next : vector1)
	{
		program.change3f("uMove", next->GetPosition());
		program.change4f("Color", next->GetColor());
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}




glm::vec4 color2(1.0f, 1.0f, 0.0f, 1.0f);
glm::vec4 color1(0.0f, 0.0f, 1.0f, 1.0f);
glm::vec3 local_position = glm::vec3(0.0f, 0.0f, 0.0f);
float length = 0.05f;
float speed = length;
float vertices[] = {
	 length / 2,  length / 2,0.0f,
	 length / 2, -length / 2,0.0f,
	-length / 2, -length / 2,0.0f,

	 length / 2,  length / 2,0.0f,
	-length / 2,  length / 2,0.0f,
	-length / 2, -length / 2,0.0f
};










int main() {
	//---------------------------------------------------------------------------
	if (!glfwInit())
	{
		cout << endl << "glfw Baslatilamadi";
		glfwTerminate();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		cout << endl << "Pencere Baslatilamadi !";
		glfwTerminate();
	}
	int Bufferwidth, Bufferheight;
	glfwGetFramebufferSize(window, &Bufferwidth, &Bufferheight);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << endl << "glew Baslatilamadi !";
		glfwTerminate();
		glfwDestroyWindow(window);
	}

	glViewport(0, 0, Bufferwidth, Bufferheight);
	//---------------------------------------------------------------------------
	//Shader Program

	Shader program;
	//CreateShader function's third parameter is shader number . i saved shader ids to an unsigned int array
	program.CreateShader("./Shaders/vshader.glsl", GL_VERTEX_SHADER, 0);
	program.CreateShader("./Shaders/fshader.glsl", GL_FRAGMENT_SHADER, 1);
	program.Attach(0);
	program.Attach(1);
	program.LinkProgram();
	program.DeleteShaders();
	//VertexArrayObject----------------------------------------------------------------------------
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//-----------------------------------------------------------------------------

	program.ConnectVariableID("uMove");
	program.ConnectVariableID("Color");
	Square sqr1(local_position.x, local_position.y, length, color1, Square::DIRECTION_RIGHT);
	Square sqr2(local_position.x, local_position.y, length, color2, Square::DIRECTION_LEFT);
	vector1.push_back(&sqr1);
	vector1.push_back(&sqr2);

	int points = 0;
	while (!glfwWindowShouldClose(window))
	{
		//INPUT----------------------------
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwTerminate();
			glfwDestroyWindow(window);
			break;
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT))
		{
			//farklý yönlere ilerliyorlar
			vector1[0]->SetDirection(Square::DIRECTION_RIGHT);
			vector1[1]->SetDirection(Square::DIRECTION_LEFT);

		}if (glfwGetKey(window, GLFW_KEY_LEFT))
		{
			vector1[0]->SetDirection(Square::DIRECTION_LEFT);
			vector1[1]->SetDirection(Square::DIRECTION_RIGHT);
		}if (glfwGetKey(window, GLFW_KEY_UP))
		{
			vector1[0]->SetDirection(Square::DIRECTION_UP);
			vector1[1]->SetDirection(Square::DIRECTION_DOWN);

		}if (glfwGetKey(window, GLFW_KEY_DOWN))
		{
			vector1[0]->SetDirection(Square::DIRECTION_DOWN);
			vector1[1]->SetDirection(Square::DIRECTION_UP);
		}
		//buttons duty is only changing our direction
		if (glfwGetKey(window,GLFW_KEY_R))
		{
			vector1[0]->Reset();
			vector1[1]->Reset();
			points = 0;
			system("cls");
		}



		//Moving square
		vector1[0]->move_square();
		vector1[1]->move_square();
		//this function is adding square's length to position vector
		//----------------------------------

		if ((abs(vector1[0]->GetPosition().x-vector1[1]->GetPosition().x)<=length)&& (abs(vector1[0]->GetPosition().y - vector1[1]->GetPosition().y) <= length))
		{
			points++;
			cout << endl << "Puan : " << points;
		}


		//BackgroundColor------------
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		//---------------------------
		//changing position every frame

		//Drawing Square
		glUseProgram(program.getProgramID());
		glBindVertexArray(VAO);
		draw(program, vector1);
		glBindVertexArray(0);
		program.DeleteProgram();
		//----------------
		//delay effect
		std::this_thread::sleep_for(chrono::milliseconds(90));

		glfwPollEvents();
		glfwSwapBuffers(window);
	}





	return 0;
}
