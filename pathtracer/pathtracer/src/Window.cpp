#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"

namespace PathTracer {

	bool Window::init(int width, int heigth, const char* title)
	{
		/* Initialize the library */
		if (!glfwInit())
			return false;

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(width, heigth, title, NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			return false;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		return true;
	}

	Window::~Window()
	{
		std::cout << "Not implemented" << std::endl;
	}

	void Window::setPixels(unsigned int* pixels) const
	{
		std::cout << "Not implemented" << std::endl;
	}
}