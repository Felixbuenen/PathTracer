#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "PathTracer.h"
#include "Window.h"

namespace PathTracer {

	PathTracer::~PathTracer()
	{
	}

	void PathTracer::init(Window* window)
	{
		m_Window = window;
	}

	void PathTracer::run()
	{
		GLFWwindow* glfwWindow = m_Window->getGlfwWindow();
		float lastFrame = 0.0f;
		float currentFrame = 0.0f;
		float red = 0.0f;
		const float speed = 100.f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(glfwWindow))
		{
			// get delta time
			currentFrame = glfwGetTime();
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			
			// calculate red
			red += deltaTime * speed;
			if (red > 255) red = 0;

			// trace scene
			traceScene(red / 255.f);

			// Clear the screen to black
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw a rectangle from the 2 triangles using 6 indices
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			/* Swap front and back buffers */
			glfwSwapBuffers(glfwWindow);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	void PathTracer::traceScene(float t)
	{
		std::cout << t << std::endl;
		unsigned int windowWidth = m_Window->getWidth();
		unsigned int windowHeight = m_Window->getHeight();
		float* pixels = m_Window->getPixels();

		for (int i = 0; i < windowWidth; i++)
		{
			for (int j = 0; j < windowHeight; j++)
			{
				int index = (j * windowWidth + i) * 3;
				setColor(index, pixels, t);
			}
		}

		m_Window->updateScreen();
	}

	void PathTracer::setColor(int index, float* pixels, float t)
	{
		// todo: add color parameter
		// for now: red

		pixels[index] = 0.0;
		pixels[index + 1] = t;
		pixels[index + 2] = 0.f;
	}

}

