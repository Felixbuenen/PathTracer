#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/geometric.hpp"

#include "PathTracer.h"
#include "Window.h"

namespace PathTracer {

	PathTracer::~PathTracer()
	{
	}

	void PathTracer::init(Window* window, Scene* scene)
	{
		m_Window = window;
		m_Scene = scene;

		// calculate screen corners
		glm::vec3 camPos = glm::vec3(0, 0, 0);
		glm::vec3 camDir = glm::vec3(0, 0, 1);
		float camScreenDist = 1.2f;

		glm::vec3 screenCentre = camPos + camDir * camScreenDist;
		
		glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), camDir);
		glm::vec3 up = glm::cross(camDir, right);

		p0 = screenCentre - right + up;
		p1 = screenCentre + right + up;
		p2 = screenCentre - right - up;
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

			// print fps
			float fps = 1.f / deltaTime;
			std::cout << "FPS: " << fps << std::endl;
	
			// trace scene
			render(deltaTime);

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

	void PathTracer::render(float t)
	{
		unsigned int windowWidth = m_Window->getWidth();
		unsigned int windowHeight = m_Window->getHeight();
		float* pixels = m_Window->getPixels();

		Ray ray;
		ray.origin = glm::vec3(0, 0, 0); // CHANGE TO CAM POSITION

		for (int i = 0; i < windowWidth; i++)
		{
			for (int j = 0; j < windowHeight; j++)
			{
				int index = (j * windowWidth + i) * 3;
				
				// create ray
				/*
				for(int i; i < maxSamples; i++) { color += m_Scene->trace(); }
				color /= maxSamples;
				*/
				if (i == 240 && j == 240)
				{
					int askjfd = 0;
				}

				updateScreenRay(ray, i, j);
				Color color = m_Scene->trace(ray, 0);
				setColor(index, pixels, color);
			}
		}

		m_Window->updateScreen();
	}

	void PathTracer::setColor(int index, float* pixels, Color t)
	{
		pixels[index] = t.r / 255.f;
		pixels[index + 1] = t.g / 255.f;
		pixels[index + 2] = t.b / 255.f;
	}

	void PathTracer::updateScreenRay(Ray& ray, int x, int y)
	{
		float u = (float)x / m_Window->getWidth();
		float v = (float)y / m_Window->getHeight();

		glm::vec3 screenPos = p0 + u * (p1 - p0) + v * (p2 - p0);
		ray.dir = glm::normalize(screenPos - glm::vec3(0, 0, 0)); // CHANGE TO CAM POSITION
	}
}

