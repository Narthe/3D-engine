#include <iostream>

#include "GameObject.h"

GameObject::GameObject()
{
	init();
}

GameObject::~GameObject()
{
	DestroyVBO();
	DestroyShaders();
}

void GameObject::init()
{
	CreateVBO();
	CreateShaders();
}

void GameObject::CreateVBO()
{
	std::cout << "Create VBO " << std::endl;

	GLenum ErrorCheckValue = glGetError();

	glGenVertexArrays(1, &m_VaoId); // Generates Vertex Array Object in the GPU's memory 
	glBindVertexArray(m_VaoId);

	glGenBuffers(1, &m_VboId);	  // Generates a buffer in the GPU's memory
	glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW); // Copy the vertex data over to the GPU's memory
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); // Provides OpenGL with all of the necessary metadata to use the block of raw data that we've uploaded to the GPU's memory using glBufferData.
	glEnableVertexAttribArray(0); // Enable attributes

								  // Exact same way to set the color data
	glGenBuffers(1, &m_ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Colors), m_Colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Checking for errors
	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		std::cerr << "ERROR: Could not create a VBO: " << gluErrorString(ErrorCheckValue)  << std::endl;
		exit(-1);
	}
}

void GameObject::CreateShaders()
{
	std::cout << "Create Shaders " << std::endl;

	GLenum ErrorCheckValue = glGetError();

	m_VertexShaderId = glCreateShader(GL_VERTEX_SHADER); // Generate a new shader object
	glShaderSource(m_VertexShaderId, 1, &m_VertexShader, NULL); // Copies the shader source code and associates it with the shader object 
	glCompileShader(m_VertexShaderId); // Compile the shader

	m_FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShaderId, 1, &m_FragmentShader, NULL);
	glCompileShader(m_FragmentShaderId);

	// To combine both vertex and fragment shaders we need a shader program object
	m_ProgramId = glCreateProgram(); // Generates the program
	glAttachShader(m_ProgramId, m_VertexShaderId);
	glAttachShader(m_ProgramId, m_FragmentShaderId);
	glLinkProgram(m_ProgramId);
	glUseProgram(m_ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		std::cerr << "ERROR: Could not create the shaders: " << gluErrorString(ErrorCheckValue) << std::endl;
		exit(-1);
	}
}

void GameObject::DestroyVBO()
{
	std::cout << "Destroy VBO " << std::endl;

	GLenum ErrorCheckValue = glGetError(); // Clear any previous opengl error

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // 0 means no buffer should be tied to the GL_ARRAY_BUFFER target

	glDeleteBuffers(1, &m_ColorBufferId);
	glDeleteBuffers(1, &m_VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_VaoId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		std::cerr << "ERROR: Could not destroy the VBO: " << gluErrorString(ErrorCheckValue) << std::endl;
		exit(-1);
	}
}

void GameObject::DestroyShaders()
{
	std::cout << "Destroy Shaders " << std::endl;

	GLenum ErrorCheckValue = glGetError();

	glUseProgram(0); // Stop using the shader program

	glDetachShader(m_ProgramId, m_VertexShaderId);
	glDetachShader(m_ProgramId, m_FragmentShaderId);

	glDeleteShader(m_FragmentShaderId);
	glDeleteShader(m_VertexShaderId);

	glDeleteProgram(m_ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		std::cerr << "ERROR: Could not destroy the shaders: " << gluErrorString(ErrorCheckValue) << std::endl;
		exit(-1);
	}
}