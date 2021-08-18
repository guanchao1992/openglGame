#include "TextureRanderComponent.h"
#include "GameApp.h"
#include <2d/VertexBuffers.hpp>
#include "AreaComponent.h"


void TextureRanderComponent::doBegin()
{
	__super::doBegin();
	auto app = GameApp::getInstance();
	_program = app->getProgram("texture");
	_vertexLocation = glGetAttribLocation(_program, "a_vertex");
	_textCoordLocation = glGetAttribLocation(_program, "a_texCoord");
	_texture0Location = glGetUniformLocation(_program, "CC_Texture0");
	_makeColorLocation = glGetUniformLocation(_program, "u_makeColor");

}

void TextureRanderComponent::doEnd()
{
	__super::doEnd();

}

void TextureRanderComponent::update()
{

}

void TextureRanderComponent::rander()
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

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glUniform1i(_texture0Location, 0);//这里的0和glActiveTexture后面的0是一个意思

	glUniform4f(_makeColorLocation, color._r, color._g, color._b, color._l);

	GLint g_projectMatrix = glGetUniformLocation(_program, "u_projectMatrix");
	glUniformMatrix4fv(g_projectMatrix, 1, GL_FALSE, projectTransform);

	glBindVertexArray(_verticesVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void TextureRanderComponent::draw()
{
	__super::draw();
	if (!_active)
		return;
	if (!_redraw)
		return;
	_redraw = false;

	genBuffer();

	auto node = (Node*)_object;
	auto areaCom = _object->getComponent<AreaComponent>();
	auto size = areaCom->getSize();
	auto anchor = areaCom->getAnchor();

	auto pVectexs = getVectexBuffer<TNVertex>(4);
	Vector2 vec[] = { {0,0},{1,0},{1,1},{0,1} };
	for (int i = 0; i < 4; i++)
	{
		pVectexs[i].vertexs[0] = (vec[i]._x - anchor._x) * size._width;
		pVectexs[i].vertexs[1] = (vec[i]._y - anchor._y) * size._height;
		pVectexs[i].vertexs[2] = node->getPosition()._z;
		pVectexs[i].vertexs[3] = 1.0f;

		pVectexs[i].texCoord[0] = vec[i]._x;
		pVectexs[i].texCoord[1] = vec[i]._y;
	}

	// Basic blending equation.
	glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);

	//重新创建缓冲区
	glBufferData(GL_ARRAY_BUFFER, 4 * (4 + 2) * sizeof(GLfloat), (GLfloat*)pVectexs, GL_DYNAMIC_DRAW);

	glBindVertexArray(_verticesVAO);

	glVertexAttribPointer(_vertexLocation, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offsetof(TNVertex, vertexs));
	glEnableVertexAttribArray(_vertexLocation);

	glVertexAttribPointer(_textCoordLocation, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)offsetof(TNVertex, texCoord));
	glEnableVertexAttribArray(_textCoordLocation);
}

void TextureRanderComponent::setTextureID(GLint id)
{
	_textureId = id;
}

