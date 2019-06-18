#include <iostream>


#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "PathTracer.h"
#include "Window.h"

int main()
{
	PathTracer::Window window;
	if (!window.init(640, 480, "Felix PathTracer"))
	{
		std::cout << "Failed to init window" << std::endl;
		return -1;
	}

	PathTracer::PathTracer pathTracer;
	pathTracer.init(&window);
	pathTracer.run();

	return 0;
}