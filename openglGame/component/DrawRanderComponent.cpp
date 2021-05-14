#include "DrawRanderComponent.h"
#include "GameApp.h"
#include <2d/VertexBuffers.hpp>
#include "AreaComponent.h"


void DrawRanderComponent::doBegin() 
{
	__super::doBegin();
	
	auto app = GameApp::getInstance();
	_program = app->getProgram("filldraw");

	_vertexLocation = glGetAttribLocation(_program, "a_vertex");
	_colorLocation = glGetAttribLocation(_program, "a_color");
	_makeColorLocation = glGetUniformLocation(_program, "u_makeColor");
	_projectMatrix = glGetUniformLocation(_program, "u_projectMatrix");
}

void DrawRanderComponent::doEnd() 
{
	__super::doEnd();
	
}

void DrawRanderComponent::update()
{
}

void DrawRanderComponent::rander()
{
	__super::rander();
	if (!_active)
		return;
	Node* node = (Node*)_object;
	if (!node)
		return;
	auto& color = node->getColor();
	auto projectTransform = node->getProjectTransform();

	glUseProgram(_program);
	glUniformMatrix4fv(_projectMatrix, 1, GL_FALSE, projectTransform);
	glUniform4f(_makeColorLocation, color._r, color._g, color._b, color._l);
	glBindVertexArray(_verticesVAO);
	if (_signs.size() > 0)
	{
		for (auto it = _signs.begin(); it != _signs.end(); it++)
		{
			glDrawArrays(it->first, it->second.first, it->second.second);
		}
	}
	else
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, _vertexs.size());
	}

	glBindVertexArray(0);
	glUseProgram(0);
}

void DrawRanderComponent::draw()
{
	__super::draw();
	if (!_active)
		return;
	if (!_redraw)
		return;
	_redraw = false;

	genBuffer();

	auto areaCom = _object->getComponent<AreaComponent>();
	auto size = areaCom->getSize();
	auto anchor = areaCom->getAnchor();

	auto pVectexs = getVectexBuffer<FDVertex>(_vertexs.size());
	int i = 0;
	for (auto it = _vertexs.begin(); it != _vertexs.end(); it++)
	{
		pVectexs[i].vertexs[0] = it->_x - anchor._x * size._width;
		pVectexs[i].vertexs[1] = it->_y - anchor._y * size._height;
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
	glBufferData(GL_ARRAY_BUFFER, _vertexs.size() * (4 + 4) * sizeof(GLfloat), (GLfloat*)pVectexs, GL_DYNAMIC_DRAW);

	glBindVertexArray(_verticesVAO);

	glVertexAttribPointer(_vertexLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, vertexs));
	glEnableVertexAttribArray(_vertexLocation);
	glVertexAttribPointer(_colorLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, colors));
	glEnableVertexAttribArray(_colorLocation);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}


void DrawRanderComponent::clearAllVertex()
{
	_signs.clear();
	_last_sign = 0;
	_vertexs.clear();
	_colors.clear();
	_redraw = true;
}

void DrawRanderComponent::addVertex(const Vector2&pos, const Vector4&color)
{
	_vertexs.push_back(pos);
	_colors.push_back(color);
	_redraw = true;
}

void DrawRanderComponent::addVertex(float x, float y, const Vector4&color)
{
	addVertex(Vector2(x, y), color);
}

void DrawRanderComponent::addVertexs(const Vector2*poss, int size, const Vector4&color, GLenum drawType)
{
	for (int i = 0; i < size; ++i)
	{
		addVertex(poss[i], color);
	}
	signDraw(drawType);
}

void DrawRanderComponent::signDraw(GLenum drawType)
{
	if (_last_sign >= _vertexs.size())
	{
		//错误的顶点数据
		_last_sign = _vertexs.size();
		return;
	}
	_signs.push_back(pair<GLenum, pair<int, int>>(drawType, pair<int, int>(_last_sign, _vertexs.size() - _last_sign)));
	_last_sign = _vertexs.size();
}

