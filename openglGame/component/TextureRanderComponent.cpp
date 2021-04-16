#include "TextureRanderComponent.h"
#include "GameApp.h"
#include <2d/VertexBuffers.hpp>


void TextureRanderComponent::doBegin()
{
	auto app = GameApp::getInstance();
	_program = app->getProgram("texture");
	_vertexLocation = glGetAttribLocation(_program, "a_vertex");
	_textCoordLocation = glGetAttribLocation(_program, "a_texCoord");
	_texture0Location = glGetUniformLocation(_program, "CC_Texture0");
	_makeColorLocation = glGetUniformLocation(_program, "u_makeColor");

	_vertexs.push_back(Vector2(0, 0));
	_vertexs.push_back(Vector2(1, 0));
	_vertexs.push_back(Vector2(1, 1));
	_vertexs.push_back(Vector2(0, 1));
	_texCoords.push_back(Vector2(0, 0));
	_texCoords.push_back(Vector2(0, 1));
	_texCoords.push_back(Vector2(1, 1));
	_texCoords.push_back(Vector2(1, 0));
}

void TextureRanderComponent::doEnd()
{

}

void TextureRanderComponent::update()
{

}

void TextureRanderComponent::rander()
{
	Node* node = (Node*)_object;
	if (!node)
		return;
	auto& color = node->getColor();
	auto projectTransform = node->getProjectTransform();

	glUseProgram(_program);

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glUniform1i(_texture0Location, 0);//这里的0和glActiveTexture后面的0是一个意思

	glUniform4f(_makeColorLocation, color._r, color._g, color._b, color._l);

	GLint g_projectMatrix = glGetUniformLocation(_program, "u_projectMatrix");
	glUniformMatrix4fv(g_projectMatrix, 1, GL_FALSE, projectTransform);

	glBindVertexArray(_verticesVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, _vertexs.size());

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);

}

void TextureRanderComponent::draw()
{
	if (!_redraw)
		return;
	_redraw = false;

	genBuffer();

	auto pVectexs = getVectexBuffer<TNVertex>(_vertexs.size());
	int i = 0;
	for (auto it = _vertexs.begin(); it != _vertexs.end(); it++)
	{
		GLfloat mtx[] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			it->_x ,it->_y , 0.0f, 1.0f };

		pVectexs[i].vertexs[0] = mtx[12] * _size.m_width;
		pVectexs[i].vertexs[1] = mtx[13] * _size.m_height;
		pVectexs[i].vertexs[2] = 0.0f;
		pVectexs[i].vertexs[3] = 1.0f;

		const auto &texCoord = _texCoords[i];
		pVectexs[i].texCoord[0] = texCoord._x;
		pVectexs[i].texCoord[1] = texCoord._y;
		i = i + 1;
	}

	// Basic blending equation.
	glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);

	//重新创建缓冲区
	glBufferData(GL_ARRAY_BUFFER, _vertexs.size() * (4 + 2) * sizeof(GLfloat), (GLfloat*)pVectexs, GL_STATIC_DRAW);

	glBindVertexArray(_verticesVAO);

	glVertexAttribPointer(_vertexLocation, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offsetof(TNVertex, vertexs));
	glEnableVertexAttribArray(_vertexLocation);

	glVertexAttribPointer(_textCoordLocation, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offsetof(TNVertex, texCoord));
	glEnableVertexAttribArray(_textCoordLocation);

}

void TextureRanderComponent::setSize(const Size& size)
{
	_size = size;
}

void TextureRanderComponent::setTextureID(GLint id)
{
	_textureId = id;
	_redraw = true;
}

