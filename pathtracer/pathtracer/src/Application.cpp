#include <iostream>


#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"

int main()
{
	PathTracer::Window window;
	if (!window.init(640, 480, "Felix PathTracer"))
	{
		std::cout << "Failed to init window" << std::endl;
		return -1;
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window.getGlfwWindow()))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window.getGlfwWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}