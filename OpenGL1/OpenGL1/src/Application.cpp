#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "uinput/winput/winput.h"
#include <chrono>
#define PI 3.14159265

void rotate(float* point, double degree) {
	float x = (float)point[0] * cos(degree * PI / 180) - point[1] * sin(degree * PI / 180);
	float y = (float)point[0] * sin(degree * PI / 180) + point[1] * cos(degree * PI / 180);
	point[0] = x;
	point[1] = y;
}

void drawCircle(GLfloat x, GLfloat y, GLfloat radius)
{
	int i;
	int triangleAmount = 1000;
	GLfloat twicePi = 2.0f * PI;

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(5.0);

	glBegin(GL_LINES);
	for (i = 0; i <= triangleAmount; i++)
	{
		glVertex2f(x, y);
		glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
	}
	glEnd();
}


int main()
{
	WInput input = WInput();

	// Define keycodes for x-axis input:
	short xAxisPlus = 'D';
	short xAxisNeg = 'A';
	// Define keycodes for y-axis input:
	short yAxisPlus = 'W';
	short yAxisNeg = 'S';

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(720, 720, "Input Testing", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW not initialised." << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[6] = {
		-0.5f,	-0.5f,
		 0.0f,	 0.5f,
		 0.5f,	-0.5f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	// Get the current time
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// Temporarily store current time
		std::chrono::milliseconds msTemp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		long long deltaTime = (msTemp - ms).count();
		ms = msTemp;

		input.update(deltaTime);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw joystick base
		glColor3f(0.5f, 0.5f, 0.5f);
		drawCircle(0.0f, 0.0f, 0.225f);

		// Draw joystick
		glColor3f(0.25f, 0.25f, 0.25f);
		drawCircle(input.getInputX() / 5.0f, input.getInputY() / 5.0f, 0.025f);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}