//#include <Windows.h>
//#include <iostream>

#include "FontDrawNode.h"
#include <string>
#include <freetype/ftglyph.h>
#include "VertexBuffers.hpp"


int FontDrawNode::g_vertexLocation = -1;
int FontDrawNode::g_textCoordLocation = -1;
int FontDrawNode::g_texture0Location = -1;
int FontDrawNode::g_makeColorLocation = -1;

FontDrawNode::~FontDrawNode()
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

void FontDrawNode::initProgram()
{
	auto app = GameApp::getInstance();
	auto program = app->getProgram("texture");
	g_vertexLocation = glGetAttribLocation(program, "a_vertex");
	g_textCoordLocation = glGetAttribLocation(program, "a_texCoord");
	g_texture0Location = glGetUniformLocation(program, "CC_Texture0");
	g_makeColorLocation = glGetUniformLocation(program, "u_makeColor");
}

void FontDrawNode::init(const char*fontFile)
{
	//g_FreeTypeLib.load(fontFile, 24, 24);
	_font = FontController::getInstance()->loadFont(fontFile);
	_shader = GameApp::getInstance()->getShader("texture");
}

void FontDrawNode::randerOne()
{
	if (!_shader)
		return;

	auto program = _shader->getProgram();
	glUseProgram(program);

	GLint g_projectMatrix = glGetUniformLocation(program, "u_projectMatrix");
	glUniformMatrix4fv(g_projectMatrix, 1, GL_FALSE, _projectTransform);

	glActiveTexture(GL_TEXTURE0 + 0);

	glBindVertexArray(_verticesVAO);

	glUniform4f(g_makeColorLocation, _color._r, _color._g, _color._b, _color._l);

	auto num = _vertexs.size() / 4;
	for (int i = 0; i < num; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, _textureIds[i]);
		glUniform1i(g_texture0Location, 0);
		glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void FontDrawNode::onDraw()
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
	static Vector2 texCoords[] = { {0,0},{0,1},{1,1},{1,0} };
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

		const auto &texCoord = texCoords[i % 4];

		pVectexs[i].texCoord[0] = texCoord._x;
		pVectexs[i].texCoord[1] = texCoord._y;
		i = i + 1;
	}

	// Basic blending equation.
	glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);

	//如果缓冲区大小发生改变，则重新创建缓冲区
	glBufferData(GL_ARRAY_BUFFER, _vertexs.size() * (4 + 2) * sizeof(GLfloat), (GLfloat*)pVectexs, GL_STATIC_DRAW);

	glBindVertexArray(_verticesVAO);

	glVertexAttribPointer(g_vertexLocation, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offsetof(TNVertex, vertexs));
	glEnableVertexAttribArray(g_vertexLocation);

	glVertexAttribPointer(g_textCoordLocation, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offsetof(TNVertex, texCoord));
	glEnableVertexAttribArray(g_textCoordLocation);
}

void FontDrawNode::clearAllVertex()
{
	_vertexs.clear();
	_textureIds.clear();
	_redraw = true;
}

void FontDrawNode::setText(const wchar_t*str)
{
	_text = str;
	clearAllVertex();
	size_t nLen = wcslen(str);
	float str_w = 0;
	for (int i = 0; i < nLen; ++i)
	{
		auto char_texture = _font->getTextChar(str[i]);

		_vertexs.push_back(Vector2(str_w, 0));
		_vertexs.push_back(Vector2(str_w, char_texture->_height));
		_vertexs.push_back(Vector2(str_w + char_texture->_width, char_texture->_height));
		_vertexs.push_back(Vector2(str_w + char_texture->_width, 0));
		_textureIds.push_back(char_texture->_texID);

		str_w += char_texture->_width;
	} 
}

void FontDrawNode::setFontSize(int fontSize)
{
	_font->_fontSize = fontSize;
	setText(_text.c_str());
}
