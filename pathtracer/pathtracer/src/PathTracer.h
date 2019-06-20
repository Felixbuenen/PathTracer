#pragma once

#include "Scene.h"

namespace PathTracer {

	class Window;

	class PathTracer
	{
	public:
		PathTracer() {}
		~PathTracer();

		void init(Window* window, Scene* scene);
		void run();

	private:
		Window* m_Window;
		Scene* m_Scene;

		void render(float);
		void setColor(int index, float* pixels, Color);
		void updateScreenRay(Ray& ray, int x, int y);

		glm::vec3 p0, p1, p2; // left-up, right-up and left-bottom corner of screen in world space
	};

}