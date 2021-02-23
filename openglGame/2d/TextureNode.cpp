#include "TextureNode.h"
#include "GameApp.h"
#include <GL/glew.h>
#include "ImageLoad.h"


static unique_ptr<TNVertex[]>ptnVectexs(new TNVertex[64]);
static size_t fdVectexsSize = 64;


GLint TextureNode::g_vertexLocation = -1;
GLint TextureNode::g_textCoordLocation = -1;
GLint TextureNode::g_texture0Location = -1;

GLuint _textureTest1 = -1;

static GLuint g_testTexture;

void TextureNode::initProgram()
{
	//GLUStgaimage image;
	//glusImageLoadTga("d:\\test_tag (1).tga", &image);

	//_textureTest1 = CreateTextureFromPng("d:\\pngtest3.png");

	//glGenTextures(1, &g_testTexture);
	//glBindTexture(GL_TEXTURE_2D, g_testTexture);

	//glTexImage2D(GL_TEXTURE_2D, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data);


	//format png_tex->internalFormat
	//GL_ALPHA

	//glTexImage2D(GL_TEXTURE_2D, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data);
	//glTexImage2D(GL_TEXTURE_2D, 0, png_tex->format, png_tex->width, png_tex->height, 0, png_tex->format, GL_UNSIGNED_BYTE, png_tex->texels);

	// Mipmap generation is now included in OpenGL 3 and above
	//glGenerateMipmap(GL_TEXTURE_2D);

	auto app = GameApp::getInstance();
	auto program = app->getProgram("texture");

	g_vertexLocation = glGetAttribLocation(program, "a_vertex");
	g_textCoordLocation = glGetAttribLocation(program, "a_texCoord");
	

	//GLint g_modelViewMatrix = glGetUniformLocation(it->second->getProgram(), "u_modelViewMatrix");
	//glUniformMatrix4fv(g_modelViewMatrix, 1, GL_FALSE, _modelViewMatrix);
	g_texture0Location = glGetUniformLocation(program, "CC_Texture0");


	//GLfloat colorV4[] = { 1.0f,0.0f,0.0f,1.0f };
	//glUniform4fv(g_colorLocation, 1, colorV4);
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

	auto a = offsetof(TNVertex, vertexs);
	auto b = offsetof(TNVertex, texCoord);
}

void TextureNode::rander()
{
	Node::rander();
	if (!_shader)
	{
		return;
	}

	glUseProgram(_shader->getProgram());

	//glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);

	glBindVertexArray(_verticesVAO);

	glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0 + _textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glUniform1i(g_texture0Location, _textureId);

	glDrawArrays(GL_TRIANGLE_FAN, 0, _vertexs.size());
}

void TextureNode::draw(const GLfloat* parentTransform)
{
	Node::draw(parentTransform);
	if (!_shader)
	{
		return;
	}
	if (!_redraw)
	{
		return;
	}
	_redraw = false;

	int i = 0;
	for (auto it = _vertexs.begin(); it != _vertexs.end(); it++)
	{
		GLfloat mtx[] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			it->_x + _position._x ,it->_y + _position._y , 0.0f, 1.0f };

		glusMatrix4x4Multiplyf(mtx, parentTransform, mtx);

		ptnVectexs.get()[i].vertexs[0] = mtx[12];
		ptnVectexs.get()[i].vertexs[1] = mtx[13];
		ptnVectexs.get()[i].vertexs[2] = 0.0f;
		ptnVectexs.get()[i].vertexs[3] = 1.0f;

		const auto &texCoord = _texCoords[i];
		ptnVectexs.get()[i].texCoord[0] = texCoord._x;
		ptnVectexs.get()[i].texCoord[1] = texCoord._y;
		i = i + 1;
	}

	// Basic blending equation.
	glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, fdVectexsSize * (4 + 2) * sizeof(GLfloat), (GLfloat*)ptnVectexs.get(), GL_STATIC_DRAW);

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

void TextureNode::enforceVertex()
{
	if (fdVectexsSize < _vertexs.size())
	{
		fdVectexsSize = _vertexs.size() + 8;
		ptnVectexs.get_deleter();
		ptnVectexs = unique_ptr<TNVertex[]>(new TNVertex[fdVectexsSize]);

		//定点数发生变化，清空缓存去，在下面重新创建。
		glDeleteBuffers(1, &_verticesVBO);
		_verticesVBO = -1;
	}

	int i = 0;
	for (auto it = _vertexs.begin(); it != _vertexs.end(); it++)
	{
		ptnVectexs.get()[i].vertexs[0] = it->_x;
		ptnVectexs.get()[i].vertexs[1] = it->_y;
		ptnVectexs.get()[i].vertexs[2] = 0.0f;
		ptnVectexs.get()[i].vertexs[3] = 1.0f;

		const auto &texCoord = _texCoords[i];
		ptnVectexs.get()[i].texCoord[0] = texCoord._x;
		ptnVectexs.get()[i].texCoord[1] = texCoord._y;
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
	glBufferData(GL_ARRAY_BUFFER, fdVectexsSize * (4 + 2) * sizeof(GLfloat), (GLfloat*)ptnVectexs.get(), GL_STATIC_DRAW);

	glBindVertexArray(_verticesVAO);

	/*
	if (_textureTest == -1)
	{
		glGenTextures(1, &_textureTest);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureTest);

	glTexImage2D(GL_TEXTURE_2D, 0, GLUS_RGB, 300, 200, 0, GLUS_RGB, GL_UNSIGNED_BYTE, 0);

	// Mipmap generation is now included in OpenGL 3 and above
	glGenerateMipmap(GL_TEXTURE_2D);

	// Trilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);

	*/

	/*
	GLint program = _shader->getProgram();
	glUseProgram(program);

	glVertexAttribPointer(g_vertexLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, vertexs));
	glEnableVertexAttribArray(g_vertexLocation);
	glVertexAttribPointer(g_colorLocation, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)offsetof(FDVertex, colors));
	glEnableVertexAttribArray(g_colorLocation);
	*/

}

void TextureNode::setTextureID(GLint id)
{
	_textureId = id;
	_redraw = true;
}

