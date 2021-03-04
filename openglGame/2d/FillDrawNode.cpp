#include "FillDrawNode.h"
#include "GameApp.h"
#include <GL/glew.h>
#include "VertexBuffers.hpp"


GLint FillDrawNode::g_vertexLocation = -1;
GLint FillDrawNode::g_colorLocation = -1;

void FillDrawNode::initProgram()
{
	auto app = GameApp::getInstance();
	auto program = app->getProgram("filldraw");

	g_vertexLocation = glGetAttribLocation(program, "a_vertex");
	g_colorLocation = glGetAttribLocation(program, "a_color");


	//GLfloat colorV4[] = { 1.0f,0.0f,0.0f,1.0f };
	//glUniform4fv(g_colorLocation, 1, colorV4);
}

FillDrawNode::~FillDrawNode()
{
	if (_verticesVBO != -1)
	{
		glDeleteBuffers(1, &_verticesVBO);
		_verticesVBO = -1;
	}

	if (_verticesVAO != -1)
	{
		glDeleteVertexArrays(1, &_verticesVAO);
		_verticesVAO = -1;
	}

}

void FillDrawNode::init()
{
	_shader = GameApp::getInstance()->getShader("filldraw");

}

void FillDrawNode::randerOne()
{
	if (!_shader)
		return;

	auto program = _shader->getProgram();
	glUseProgram(program);

	GLint g_projectMatrix = glGetUniformLocation(program, "u_projectMatrix");
	glUniformMatrix4fv(g_projectMatrix, 1, GL_FALSE, _projectTransform);
	
	glBindVertexArray(_verticesVAO);

	glDrawArrays(GL_TRIANGLE_FAN, 0, _vertexs.size());

	glBindVertexArray(0);

	glUseProgram(0);
}

void FillDrawNode::onDraw()
{
	if (!_redraw)
		return;
	_redraw = false;

	if (_verticesVBO == -1)
	{
		glGenBuffers(1, &_verticesVBO);
	}
	if (_verticesVAO == -1)
	{
		// Create the VAO for the program.
		glGenVertexArrays(1, &_verticesVAO);
	}

	auto pVectexs = getVectexBuffer<FDVertex>(_vertexs.size());
	int i = 0;
	for (auto it = _vertexs.begin(); it != _vertexs.end(); it++)
	{
		GLfloat mtx[] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			it->_x ,it->_y , 0.0f, 1.0f };

		pVectexs[i].vertexs[0] = mtx[12];
		pVectexs[i].vertexs[1] = mtx[13];
		pVectexs[i].vertexs[2] = 0.0f;
		pVectexs[i].vertexs[3] = 1.0f;

		pVectexs[i].colors[0] = _color._r;
		pVectexs[i].colors[1] = _color._g;
		pVectexs[i].colors[2] = _color._b;
		pVectexs[i].colors[3] = _color._l;
		i = i + 1;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);
	if (_revertexs)
	{
		glBufferData(GL_ARRAY_BUFFER, _vertexs.size() * (4 + 4) * sizeof(GLfloat), (GLfloat*)pVectexs, GL_STATIC_DRAW);
	}

	glBindVertexArray(_verticesVAO);

	glVertexAttribPointer(g_vertexLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, vertexs));
	glEnableVertexAttribArray(g_vertexLocation);
	glVertexAttribPointer(g_colorLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, colors));
	glEnableVertexAttribArray(g_colorLocation);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void FillDrawNode::clearAllVertex()
{
	_vertexs.clear();
	_redraw = true;
	_revertexs = true;
}

void FillDrawNode::addVertex(const Vector2&pos)
{
	_vertexs.push_back(pos);
	_redraw = true;
	_revertexs = true;
}
