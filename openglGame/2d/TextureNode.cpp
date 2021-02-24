#include "TextureNode.h"
#include "GameApp.h"
#include <GL/glew.h>
#include "control/TextureController.h"


static unique_ptr<TNVertex[]>ptnVectexs(new TNVertex[64]);
static size_t fdVectexsSize = 64;


GLint TextureNode::g_vertexLocation = -1;
GLint TextureNode::g_textCoordLocation = -1;
GLint TextureNode::g_texture0Location = -1;


void TextureNode::initProgram()
{
	auto app = GameApp::getInstance();
	auto program = app->getProgram("texture");

	g_vertexLocation = glGetAttribLocation(program, "a_vertex");
	g_textCoordLocation = glGetAttribLocation(program, "a_texCoord");
	
	g_texture0Location = glGetUniformLocation(program, "CC_Texture0");

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

void TextureNode::randerOne()
{
	if (!_shader)
		return;

	glUseProgram(_shader->getProgram());

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glUniform1i(g_texture0Location, 0);//这里的0和glActiveTexture后面的0是一个意思

	glBindVertexArray(_verticesVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, _vertexs.size());

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void TextureNode::draw(const GLfloat* transform)
{
	if (!_redraw)
		return;
	_redraw = false;

	int i = 0;
	for (auto it = _vertexs.begin(); it != _vertexs.end(); it++)
	{
		GLfloat mtx[] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			it->_x ,it->_y , 0.0f, 1.0f };

		glusMatrix4x4Multiplyf(mtx, transform, mtx);

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

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		static int num = 0;
		printf("error:0x%04X in %s %s %d.---%d\n", err, __FILE__, __FUNCTION__, __LINE__, ++num);
	}

}

void TextureNode::setTextureID(GLint id)
{
	_textureId = id;
	_redraw = true;
}

