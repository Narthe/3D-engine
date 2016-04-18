#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "glew.h"
#include "freeglut.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class GameObject
{
public:
	GameObject();
	~GameObject();
	void init();
	void CreateVBO();
	void DestroyVBO();
	void CreateShaders();
	void DestroyShaders();

private:
	GLfloat m_Vertices[16] = {
		-0.8f, -0.8f, 0.0f, 1.0f,
		0.0f,  0.8f, 0.0f, 1.0f,
		0.8f, -0.8f, 0.0f, 1.0f
	};
	GLfloat m_Colors[16] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};

	const GLchar* m_VertexShader = {
		"#version 400\n"\

		"layout(location=0) in vec4 in_Position;\n"\
		"layout(location=1) in vec4 in_Color;\n"\
		"out vec4 ex_Color;\n"\

		"void main(void)\n"\
		"{\n"\
		"  gl_Position = in_Position;\n"\
		"  ex_Color = in_Color;\n"\
		"}\n"
	};
	const GLchar* m_FragmentShader = {
		"#version 400\n"\


		"in vec4 ex_Color;\n"\
		"out vec4 out_Color;\n"\

		"void main(void)\n"\
		"{\n"\
		"  out_Color = ex_Color;\n"\
		"}\n"
	};

	GLuint			m_VaoId;
	GLuint			m_VboId;
	GLuint			m_ColorBufferId;
	GLuint			m_VertexShaderId;
	GLuint			m_FragmentShaderId;
	GLuint			m_ProgramId;
};

#endif