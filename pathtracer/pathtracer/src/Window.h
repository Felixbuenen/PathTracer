#pragma once

struct GLFWwindow;

namespace PathTracer {

	class Window
	{
	public:
		Window() { }
		~Window();

		void setPixels(unsigned int* pixels) const;
		bool init(int width, int heigth, const char* title);

		inline unsigned int* getPixels() const { return m_Pixels; }
		inline GLFWwindow* getGlfwWindow() const { return m_Window; } // remove dis

	private:
		unsigned int m_Width, m_Height;
		unsigned int* m_Pixels;
		GLFWwindow* m_Window;
	};

}