#include "FontRanderComponent.h"
#include "GameApp.h"
#include <2d/VertexBuffers.hpp>
#include <control/FontController.h>
#include <base/Tools.h>
#include "AreaComponent.h"

void FontRanderComponent::setFont(const string& fontFile)
{
	_font = FontController::getInstance()->loadFont(fontFile.c_str());
}

void FontRanderComponent::doBegin()
{
	__super::doBegin();
	auto app = GameApp::getInstance();
	_program = app->getProgram("texture");
	_vertexLocation = glGetAttribLocation(_program, "a_vertex");
	_textCoordLocation = glGetAttribLocation(_program, "a_texCoord");
	_texture0Location = glGetUniformLocation(_program, "CC_Texture0");
	_makeColorLocation = glGetUniformLocation(_program, "u_makeColor");

}

void FontRanderComponent::doEnd()
{
	__super::doEnd();
}

void FontRanderComponent::update()
{

}

void FontRanderComponent::rander()
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

	GLint g_projectMatrix = glGetUniformLocation(_program, "u_projectMatrix");
	glUniformMatrix4fv(g_projectMatrix, 1, GL_FALSE, projectTransform);

	glActiveTexture(GL_TEXTURE0 + 0);

	glBindVertexArray(_verticesVAO);

	glUniform4f(_makeColorLocation, color._r, color._g, color._b, color._l);

	auto num = _vertexs.size() / 4;
	for (int i = 0; i < num; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, _textureIds[i]);
		glUniform1i(_texture0Location, 0);
		glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void FontRanderComponent::draw()
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

	auto pVectexs = getVectexBuffer<TNVertex>(_vertexs.size());
	int i = 0;
	static Vector2 texCoords[] = { {0,0},{0,1},{1,1},{1,0} };
	for (auto it = _vertexs.begin(); it != _vertexs.end(); it++)
	{
		pVectexs[i].vertexs[0] = it->_x - anchor._x * size._width;
		pVectexs[i].vertexs[1] = it->_y - anchor._y * size._height + size._height;
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

	glVertexAttribPointer(_vertexLocation, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offsetof(TNVertex, vertexs));
	glEnableVertexAttribArray(_vertexLocation);

	glVertexAttribPointer(_textCoordLocation, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offsetof(TNVertex, texCoord));
	glEnableVertexAttribArray(_textCoordLocation);
}

void FontRanderComponent::clearAllVertex()
{
	_vertexs.clear();
	_textureIds.clear();
	_redraw = true;
}

void FontRanderComponent::setText(const std::string&str)
{
	setText(s2ws(str));
}

void FontRanderComponent::setText(const std::wstring&wstr)
{
	setText(wstr.c_str());
}

void FontRanderComponent::setFontSize(int fontSize)
{
	_font->_fontSize = fontSize;
	setText(_text.c_str());
}

void FontRanderComponent::setText(const wchar_t*str)
{
	_text = str;
	layout();
}

void FontRanderComponent::setMaxWidth(unsigned int maxWidth)
{
	_maxWidth = maxWidth;
	layout();
}

void FontRanderComponent::layout()
{
	clearAllVertex();
	size_t nLen = wcslen(_text.c_str());
	unsigned int str_w = 0;
	float size_w = 0;
	int str_h = _font->_fontSize;
	int off_y = _font->_fontSize*0.2;
	for (int i = 0; i < nLen; ++i)
	{
		auto char_texture = _font->getTextChar(_text.c_str()[i]);

		if (str_w + char_texture->_adv_x > _maxWidth)
		{
			str_w = 0;
			str_h += _font->_fontSize;
			size_w = _maxWidth;
		}

		_vertexs.push_back(Vector2(str_w + char_texture->_delta_x, -str_h + off_y + char_texture->_delta_y));
		_vertexs.push_back(Vector2(str_w + char_texture->_delta_x, -str_h + off_y + char_texture->_height + char_texture->_delta_y));
		_vertexs.push_back(Vector2(str_w + char_texture->_delta_x + char_texture->_width, -str_h + off_y + char_texture->_height + char_texture->_delta_y));
		_vertexs.push_back(Vector2(str_w + char_texture->_delta_x + char_texture->_width, -str_h + off_y + char_texture->_delta_y));
		_textureIds.push_back(char_texture->_texID);

		str_w += char_texture->_adv_x;
	}
	if (size_w < str_w)
	{
		size_w = str_w;
	}

	auto areaCom = _object->getComponent<AreaComponent>();
	areaCom->setSize(Size(size_w, str_h));
}
