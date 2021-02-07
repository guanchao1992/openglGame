#include "FillDrawNode.h"
#include "GameApp.h"
#include <GL/glew.h>


static unique_ptr<FDVertex[]>pfdVectexs(new FDVertex[64]);
static int fdVectexsSize = 64;

GLint FillDrawNode::g_vertexLocation = -1;
GLint FillDrawNode::g_colorLocation = -1;

void FillDrawNode::initFillDrawProgram()
{
	auto app = GameApp::getInstance();
	auto program = app->getProgram("filldraw");

	g_vertexLocation = glGetAttribLocation(program, "a_vertex");

	g_colorLocation = glGetAttribLocation(program, "a_color");


	//GLfloat colorV4[] = { 1.0f,0.0f,0.0f,1.0f };
	//glUniform4fv(g_colorLocation, 1, colorV4);
}

SPFillDrawNode FillDrawNode::create()
{
	SPFillDrawNode node = make_shared<FillDrawNode>();
	node->init(node);
	return node;
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

void FillDrawNode::init(SPNode node)
{
	Node::init(node);
	_shader = GameApp::getInstance()->getShader("filldraw");


}

void FillDrawNode::rander()
{
	Node::rander();

	glUseProgram(_shader->getProgram());
	glBindVertexArray(_verticesVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, _vertexs.size());
}

void FillDrawNode::draw()
{
	Node::draw();
	if (!_redraw)
	{
		return;
	}
	_redraw = false;


	int i = 0;
	for (auto it = _vertexs.begin(); it != _vertexs.end(); it++)
	{
		pfdVectexs.get()[i].vertexs[0] = it->_x + _position._x;
		pfdVectexs.get()[i].vertexs[1] = it->_y + _position._y;
		pfdVectexs.get()[i].vertexs[2] = 0.0f;
		pfdVectexs.get()[i].vertexs[3] = 1.0f;

		pfdVectexs.get()[i].colors[0] = _color._r;
		pfdVectexs.get()[i].colors[1] = _color._g;
		pfdVectexs.get()[i].colors[2] = _color._b;
		pfdVectexs.get()[i].colors[3] = _color._l;
		i = i + 1;
	}

	GLint program = _shader->getProgram();
	glUseProgram(program);

	//glGenBuffers(1, &_verticesVBO);

	glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, fdVectexsSize * (4 + 4) * sizeof(GLfloat), (GLfloat*)pfdVectexs.get(), GL_STATIC_DRAW);

	//glGenVertexArrays(1, &_verticesVAO);
	glBindVertexArray(_verticesVAO);

	glVertexAttribPointer(g_vertexLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, vertexs));
	glEnableVertexAttribArray(g_vertexLocation);
	glVertexAttribPointer(g_colorLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, colors));
	glEnableVertexAttribArray(g_colorLocation);

	// Use the program.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void FillDrawNode::clearAllVertex()
{
	_vertexs.clear();
	_redraw = true;
}

void FillDrawNode::addVertex(const Vector2&pos)
{
	_vertexs.push_back(pos);
	_redraw = true;
}

void FillDrawNode::enforceVertex()
{
	if (fdVectexsSize < _vertexs.size())
	{
		fdVectexsSize = _vertexs.size() + 8;
		pfdVectexs.get_deleter();
		pfdVectexs = unique_ptr<FDVertex[]>(new FDVertex[fdVectexsSize]);

		//定点数发生变化，清空缓存去，在下面重新创建。
		glDeleteBuffers(1, &_verticesVBO);
		_verticesVBO = -1;
	}

	int i = 0;
	for (auto it = _vertexs.begin(); it != _vertexs.end(); it++)
	{
		pfdVectexs.get()[i].vertexs[0] = it->getX();
		pfdVectexs.get()[i].vertexs[1] = it->getY();
		pfdVectexs.get()[i].vertexs[2] = 0.0f;
		pfdVectexs.get()[i].vertexs[3] = 1.0f;

		pfdVectexs.get()[i].colors[0] = _color._r;
		pfdVectexs.get()[i].colors[1] = _color._g;
		pfdVectexs.get()[i].colors[2] = _color._b;
		pfdVectexs.get()[i].colors[3] = _color._l;
		i = i + 1;
	}

	if (_verticesVBO == -1)
	{
		glGenBuffers(1, &_verticesVBO);
	}

	if (_verticesVAO == -1)
	{
		// Create the VAO for the program.
		glGenVertexArrays(1, &_verticesVAO);
		//glDeleteVertexArrays(1, &_verticesVAO);
	}

	glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);
	//创建并初始化缓冲区对象的数据存储
	//创建缓冲区大小 = 顶点数 * （顶点位置+顶点颜色）()
	glBufferData(GL_ARRAY_BUFFER, fdVectexsSize * (4 + 4) * sizeof(GLfloat), (GLfloat*)pfdVectexs.get(), GL_STATIC_DRAW);

	glBindVertexArray(_verticesVAO);

	/*
	GLint program = _shader->getProgram();
	glUseProgram(program);

	glVertexAttribPointer(g_vertexLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, vertexs));
	glEnableVertexAttribArray(g_vertexLocation);
	glVertexAttribPointer(g_colorLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, colors));
	glEnableVertexAttribArray(g_colorLocation);
	*/

}
