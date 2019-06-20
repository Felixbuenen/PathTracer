#include <iostream>


#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "PathTracer.h"
#include "Window.h"
#include "Objects/Sphere.h"
#include "Defines.h"

using namespace PathTracer;

int main()
{
	Window window;
	if (!window.init(480, 480, "Felix PathTracer"))
	{
		std::cout << "Failed to init window" << std::endl;
		return -1;
	}

	// create objects
	Sphere* sphere = new Sphere(glm::vec3(0, 0, 10), 2.f, Color(255, 69, 0), 0.f);
	std::vector<IObject*> objects;
	objects.push_back(sphere);

	Scene scene(objects);

	::PathTracer::PathTracer pathTracer;
	pathTracer.init(&window, &scene);
	pathTracer.run();

	return 0;
}

