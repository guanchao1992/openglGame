#include "TextureNode.h"
#include "GameApp.h"
#include <GL/glew.h>
#include "control/TextureController.h"
#include "VertexBuffers.hpp"


int TextureNode::g_vertexLocation = -1;
int TextureNode::g_textCoordLocation = -1;
int TextureNode::g_texture0Location = -1;
int TextureNode::g_makeColorLocation = -1;


void TextureNode::initProgram()
{
	auto app = GameApp::getInstance();
	auto program = app->getProgram("texture");
	g_vertexLocation = glGetAttribLocation(program, "a_vertex");
	g_textCoordLocation = glGetAttribLocation(program, "a_texCoord");
	g_texture0Location = glGetUniformLocation(program, "CC_Texture0");
	g_makeColorLocation = glGetUniformLocation(program, "u_makeColor");

}

TextureNode::~TextureNode()
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

void TextureNode::init()
{
	_shader = GameApp::getInstance()->getShader("texture");

}

void TextureNode::randerOne()
{
	if (!_shader)
		return;

	auto program = _shader->getProgram();
	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glUniform1i(g_texture0Location, 0);//这里的0和glActiveTexture后面的0是一个意思
	glUniform4f(g_makeColorLocation, _color._r, _color._g, _color._b, _color._l);

	GLint g_projectMatrix = glGetUniformLocation(program, "u_projectMatrix");
	glUniformMatrix4fv(g_projectMatrix, 1, GL_FALSE, _projectTransform);

	glBindVertexArray(_verticesVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, _vertexs.size());

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void TextureNode::onDraw()
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

	auto pVectexs = getVectexBuffer<TNVertex>(_vertexs.size());
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

		const auto &texCoord = _texCoords[i];
		pVectexs[i].texCoord[0] = texCoord._x;
		pVectexs[i].texCoord[1] = texCoord._y;
		i = i + 1;
	}

	// Basic blending equation.
	glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);
	if (_revertexs)
	{
		glBufferData(GL_ARRAY_BUFFER, _vertexs.size() * (4 + 2) * sizeof(GLfloat), (GLfloat*)pVectexs, GL_STATIC_DRAW);
	}

	glBindVertexArray(_verticesVAO);

	glVertexAttribPointer(g_vertexLocation, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offsetof(TNVertex, vertexs));
	glEnableVertexAttribArray(g_vertexLocation);

	glVertexAttribPointer(g_textCoordLocation, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offsetof(TNVertex, texCoord));
	glEnableVertexAttribArray(g_textCoordLocation);

}

void TextureNode::clearAllVertex()
{
	_vertexs.clear();
	_texCoords.clear();
	_redraw = true;
}

void TextureNode::addVertex(const Vector2&pos, const Vector2&texCoord)
{
	_vertexs.push_back(pos);
	_texCoords.push_back(texCoord);
	_redraw = true;
}

void TextureNode::setTextureID(GLint id)
{
	_textureId = id;
	_redraw = true;
}

