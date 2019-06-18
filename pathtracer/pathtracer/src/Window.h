#pragma once

struct GLFWwindow;

namespace PathTracer {

	class Window
	{
	public:
		Window() { }
		~Window();

		//void setPixels(unsigned int* pixels) const;
		bool init(int width, int heigth, const char* title);

		void updateScreen();
		inline float* getPixels() const { return m_Pixels; }
		inline unsigned int getWidth() const { return m_Width; }
		inline unsigned int getHeight() const { return m_Height; }
		inline GLFWwindow* getGlfwWindow() const { return m_Window; }

	private:
		void initBuffers();
		void clearBuffers();

	private:
		unsigned int m_Width, m_Height;
		float* m_Pixels;
		GLFWwindow* m_Window;

		// ---------- OpenGL vars ------------
		// buffer IDs
		GLuint m_TexID;
		GLuint m_Vbo, m_Vao, m_Ebo;

		// texture data
		GLuint m_ShaderProgram, m_VertexShader, m_FragShader;
	};

}