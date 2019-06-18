#pragma once

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
		void setColor(int index, float* pixels, float); // todo: add color parameter, t weghalen
	};

}