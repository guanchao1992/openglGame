#include "FillDrawNode.h"
#include "GameApp.h"
#include <GL/glew.h>
#include "VertexBuffers.hpp"


GLint FillDrawNode::g_vertexLocation = -1;
GLint FillDrawNode::g_colorLocation = -1;
GLint FillDrawNode::g_makeColorLocation = -1;


void FillDrawNode::initProgram()
{
	auto app = GameApp::getInstance();
	auto program = app->getProgram("filldraw");

	g_vertexLocation = glGetAttribLocation(program, "a_vertex");
	g_colorLocation = glGetAttribLocation(program, "a_color");
	g_makeColorLocation = glGetUniformLocation(program, "u_makeColor");


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

	glUniform4f(g_makeColorLocation, _color._r, _color._g, _color._b, _color._l);
	
	glBindVertexArray(_verticesVAO);

	if (_signs.size() > 0)
	{
		int lastIndex = 0;
		for (int i = 0; i < _signs.size(); ++i)
		{
			glDrawArrays(_signs[i].second, lastIndex, _signs[i].first - lastIndex + 1);
			lastIndex = _signs[i].first + 1;
		}
	}
	else
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, _vertexs.size());
	}

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

		auto& color = _colors[i];
		pVectexs[i].colors[0] = color._r;
		pVectexs[i].colors[1] = color._g;
		pVectexs[i].colors[2] = color._b;
		pVectexs[i].colors[3] = color._l;
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

void FillDrawNode::addVertex(const Vector2&pos, const Vector4&color)
{
	_vertexs.push_back(pos);
	_colors.push_back(color);
	_redraw = true;
	_revertexs = true;
}

void FillDrawNode::addVertex(float x, float y, const Vector4&color)
{
	addVertex(Vector2(x, y), color);
}

void FillDrawNode::addVertexs(const Vector2*poss, int size, const Vector4&color, GLenum drawType)
{
	for (int i = 0; i < size; ++i)
	{
		addVertex(poss[i], color);
	}
	signDraw(drawType);
}

void FillDrawNode::signDraw(GLenum drawType)
{
	_signs.push_back(pair<int, int>(_vertexs.size() - 1, drawType));
}
