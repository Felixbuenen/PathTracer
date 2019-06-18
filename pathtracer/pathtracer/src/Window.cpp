#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"

namespace PathTracer {

	// Shader sources
	const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    in vec2 texcoord;
    out vec2 Texcoord;
    void main()
    {
        Texcoord = texcoord;
        gl_Position = vec4(position, 0.0, 1.0);
    }
	)glsl";
	const GLchar* fragmentSource = R"glsl(
    #version 150 core
    in vec2 Texcoord;
    out vec4 outColor;
    uniform sampler2D pixels;
    void main()
    {
        outColor = texture(pixels, Texcoord);
    }
	)glsl";

	bool Window::init(int width, int height, const char* title)
	{
		/* Initialize the library */
		if (!glfwInit())
			return false;

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
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

		m_Width = width;
		m_Height = height;

		initBuffers();

		return true;
	}

	void Window::updateScreen()
	{
		glBindTexture(GL_TEXTURE_2D, m_TexID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, m_Pixels);
	}

	void Window::initBuffers()
	{
		// Create Vertex Array Object
		glGenVertexArrays(1, &m_Vao);
		glBindVertexArray(m_Vao);

		// Create a Vertex Buffer Object and copy the vertex data to it
		glGenBuffers(1, &m_Vbo);

		GLfloat vertices[] = {
			//  Position Texcoords
			-1.f,  1.f,	 0.0f, 0.0f, // Top-left
			 1.f,  1.f,	 1.0f, 0.0f, // Top-right
			 1.f, -1.f,	 1.0f, 1.0f, // Bottom-right
			-1.f, -1.f,	 0.0f, 1.0f  // Bottom-left
		};

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Create an element array
		glGenBuffers(1, &m_Ebo);

		GLuint elements[] = {
			0, 1, 2,
			2, 3, 0
		};

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

		// Create and compile the vertex shader
		m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_VertexShader, 1, &vertexSource, NULL);
		glCompileShader(m_VertexShader);

		// Create and compile the fragment shader
		m_FragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_FragShader, 1, &fragmentSource, NULL);
		glCompileShader(m_FragShader);

		// Link the vertex and fragment shader into a shader program
		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, m_VertexShader);
		glAttachShader(m_ShaderProgram, m_FragShader);
		glBindFragDataLocation(m_ShaderProgram, 0, "outColor");
		glLinkProgram(m_ShaderProgram);
		glUseProgram(m_ShaderProgram);

		// Specify the layout of the vertex data
		GLint posAttrib = glGetAttribLocation(m_ShaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

		GLint texAttrib = glGetAttribLocation(m_ShaderProgram, "texcoord");
		glEnableVertexAttribArray(texAttrib);
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

		// Load textures
		glGenTextures(1, &m_TexID);

		// init pixels to red
		m_Pixels = new float[m_Width * m_Height * 3];
		for (int h = 0; h < m_Height; h++)
		{
			for (int w = 0; w < m_Width; w++)
			{
				m_Pixels[(m_Width * h + w) * 3] = 1.f;
				m_Pixels[(m_Width * h + w) * 3 + 1] = 0.f;
				m_Pixels[(m_Width * h + w) * 3 + 2] = 0.f;
			}
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TexID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, m_Pixels);
		glUniform1i(glGetUniformLocation(m_ShaderProgram, "pixels"), 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void Window::clearBuffers()
	{
		glDeleteTextures(1, &m_TexID);

		glDeleteProgram(m_ShaderProgram);
		glDeleteShader(m_FragShader);
		glDeleteShader(m_VertexShader);

		glDeleteBuffers(1, &m_Ebo);
		glDeleteBuffers(1, &m_Vbo);

		glDeleteVertexArrays(1, &m_Vao);

		delete[] m_Pixels;		
		glfwTerminate();
	}

	Window::~Window()
	{
		clearBuffers();
		std::cout << "ALL CLEAR" << std::endl;
	}
}