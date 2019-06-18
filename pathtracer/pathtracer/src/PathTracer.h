#pragma once

#include "Defines.h"

namespace PathTracer {

	class Window;

	class PathTracer
	{
	public:
		PathTracer() {}
		~PathTracer();

		void init(Window* window);
		void run();

	private:
		Window* m_Window;

		void traceScene(float);
		void setColor(int index, float* pixels, Color); 
	};

}