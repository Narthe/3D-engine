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
		fprintf(
			stderr,
			"ERROR: Could not destroy the VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void GameObject::CreateShaders()
{
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
		fprintf(
			stderr,
			"ERROR: Could not create the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void GameObject::DestroyVBO()
{
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
		fprintf(
			stderr,
			"ERROR: Could not destroy the VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void GameObject::DestroyShaders()
{
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
		fprintf(
			stderr,
			"ERROR: Could not destroy the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}