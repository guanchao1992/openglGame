#include "OutlineBoxComponent.h"
#include "2d/Node.h"
#include <GameApp.h>
#include "AreaComponent.h"
#include <2d/VertexBuffers.hpp>


OutlineBoxComponent::~OutlineBoxComponent()
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

void OutlineBoxComponent::doBegin()
{
	__super::doBegin();

	auto areaCom = _object->getComponent<AreaComponent>();
	if (!areaCom)
	{
		areaCom = _object->addComponent<AreaComponent>();
	}
	auto randerCom = dynamic_pointer_cast<RanderComponent>(_object->getComponent(COMPONENT_RANDER));
	if (!randerCom)
	{
		randerCom = _object->addComponent<RanderComponent>();
	}
	randerCom->setOutlineBoxComponent(this);

	auto app = GameApp::getInstance();
	_program = app->getProgram("filldraw");

	_vertexLocation = glGetAttribLocation(_program, "a_vertex");
	_colorLocation = glGetAttribLocation(_program, "a_color");
	_makeColorLocation = glGetUniformLocation(_program, "u_makeColor");
	_projectMatrix = glGetUniformLocation(_program, "u_projectMatrix");
}

void OutlineBoxComponent::doEnd()
{
	__super::doEnd();
	auto randerCom = dynamic_pointer_cast<RanderComponent>(_object->getComponent(COMPONENT_RANDER));
	if (!randerCom)
	{
		randerCom = _object->addComponent<RanderComponent>();
	}
	randerCom->setOutlineBoxComponent(nullptr);
}

void OutlineBoxComponent::update()
{
}

void OutlineBoxComponent::rander()
{
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

	if (_fill)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
	else
	{
		glDrawArrays(GL_LINE_STRIP, 0, 5);
	}

	glBindVertexArray(0);
	glUseProgram(0);
}

void OutlineBoxComponent::draw()
{
	if (!_active)
		return;
	if (!_redraw)
		return;
	_redraw = false;

	auto areaCom = _object->getComponent<AreaComponent>();
	auto size = areaCom->getSize();
	auto anchor = areaCom->getAnchor();

	Vector2 vec[] = { {0,0},{size._width,0},{size._width,size._height},{0,size._height},{0,0} };
	auto pVectexs = getVectexBuffer<FDVertex>(5);

	for (int i = 0; i < 5; ++i)
	{
		pVectexs[i].vertexs[0] = vec[i]._x - anchor._x * size._width;
		pVectexs[i].vertexs[1] = vec[i]._y - anchor._y * size._height;
		pVectexs[i].vertexs[2] = 0.0f;
		pVectexs[i].vertexs[3] = 1.0f;

		pVectexs[i].colors[0] = _color._r;
		pVectexs[i].colors[1] = _color._g;
		pVectexs[i].colors[2] = _color._b;
		pVectexs[i].colors[3] = _color._l;
	}

	if (_verticesVBO == -1)
	{
		glGenBuffers(1, &_verticesVBO);
	}
	if (_verticesVAO == -1)
	{
		// Create the VAO for the program.
		glGenVertexArrays(1, &_verticesVAO);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);

	glBufferData(GL_ARRAY_BUFFER, 5 * (4 + 4) * sizeof(GLfloat), (GLfloat*)pVectexs, GL_DYNAMIC_DRAW);

	glBindVertexArray(_verticesVAO);

	glVertexAttribPointer(_vertexLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, vertexs));
	glEnableVertexAttribArray(_vertexLocation);
	glVertexAttribPointer(_colorLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, colors));
	glEnableVertexAttribArray(_colorLocation);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}
