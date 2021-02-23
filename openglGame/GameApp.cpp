#include "GameApp.h"
#include<iostream>
#include "2d/FillDrawNode.h"
#include "2d/ImageLoad.h"
#include "2d/TextureNode.h"
#include "ShaderFiles.h"

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

void GameApp::init()
{
	this->initShader();

	//画格子
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			auto fd = FillDrawNode::create();
			fd->addVertex(Vector2(0, 0));
			fd->addVertex(Vector2(120, 0));
			fd->addVertex(Vector2(120, 120));
			fd->addVertex(Vector2(0, 120));

			fd->setPosition(Vector2(120 * x, 120 * y));
			if ((x + y) % 2 == 0)
			{
				fd->setColor(Vector4(0.2, 0.2, 0.2, 1));
			}
			else
			{
				fd->setColor(Vector4(0.3, 0.3, 0.3, 1));
			}
			fd->enforceVertex();

			this->addChild(fd);
		}
	}


	//_textureTest1 = loadPNGTexture("d:\\res\\test (3).png");

	_start = GameStart::create();
	//addChild(_start);

	char path[256];
	int index = 1;
	//画格子
	for (int x = 5; x < 10; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			auto tn = TextureNode::create();
			tn->addVertex(Vector2(0, 0), Vector2(0, 0));
			tn->addVertex(Vector2(120, 0), Vector2(1, 0));
			tn->addVertex(Vector2(120, 120), Vector2(1, 1));
			tn->addVertex(Vector2(0, 120), Vector2(0, 1));
			sprintf_s(path, 256, ".\\res\\test (%d).png", index++);
			tn->setTextureID(loadPNGTexture(path));

			tn->setPosition(Vector2(120 * x, 120 * y));
			if ((x + y) % 2 == 0)
			{
				//tn->setColor(Vector4(0.2, 0.2, 0.2, 1));
			}
			else
			{
				//tn->setColor(Vector4(0.3, 0.3, 0.3, 1));
			}
			tn->enforceVertex();

			this->addChild(tn);
		}
	}

}

int GameApp::initShader()
{
	glusMatrix4x4Identityf(_viewMatrix);
	glusMatrix4x4Identityf(_modelMatrix);

	for (int i = 0; i < sizeof(G_SHADERS) / sizeof(char*); ++i)
	{
		const char* shaderName = G_SHADERS[i];

		SPShader shader = make_shared<Shader>();
		shader->loadShader(shaderName);
		
		_shaders->insert(map<string, SPShader>::value_type(shaderName, shader));
	}

	FillDrawNode::initProgram();
	TextureNode::initProgram();

	//filldraw
	//auto app = GameApp::getInstance();

	return 0;
}

int GameApp::removeAllShader()
{
	for (auto it = _shaders->begin(); it != _shaders->end(); it++)
	{
		glusProgramDestroy(it->second->_sprogram.get());
	}
	_shaders->clear();
	return 0;
}

//getSprogram(const char*name);
GLint GameApp::getProgram(const char* name)
{
	auto sp_shader = _shaders->at(name);
	if (sp_shader != nullptr)
	{
		return sp_shader->getProgram();
	}
	return -1;
}

SPShader GameApp::getShader(const char*name)
{
	auto sp_shader = _shaders->at(name);
	if (sp_shader != nullptr)
	{
		return sp_shader;
	}
	return nullptr;
}


void GameApp::addNode(SPNode node)
{
	_childs->push_back(node);
}

void GameApp::rander()
{
	Node::rander();

	//do something
}

void GameApp::draw(const GLfloat *parentTransform)
{
	Node::draw(parentTransform);

	//do something
}

void GameApp::reshape()
{
	Node::reshape();
	_reLoadView = false;
	//_redraw = true;

	GLfloat modelViewMatrix[16];

	GLfloat viewMatrix[] = { 
		2 / _viewWidth, 0.0f, 0.0f, 0.0f,
		0.0f, 2 / _viewHeight, 0.0f, 0.0f,
		0.0f, 0.0f, 1.f, 0.0f,
		-1, -1, 0.0f, 1.0f };

	glusMatrix4x4Copyf(_viewMatrix, viewMatrix, false);

	glusMatrix4x4Multiplyf(_modelViewMatrix, _viewMatrix, _modelMatrix);

	for (auto it = _shaders->begin(); it != _shaders->end(); it++)
	{
		auto program = it->second->getProgram();
		glUseProgram(program);
		GLint g_modelViewMatrix = glGetUniformLocation(program, "u_modelViewMatrix");
		glUniformMatrix4fv(g_modelViewMatrix, 1, GL_FALSE, _modelViewMatrix);
	}
	glUseProgram(0);
}

void GameApp::update(float time)
{
	_start->update(time);


	static float t_time = 0, f;
	static int frame = 0;
	static int timebase = 0;
	char s[256] = { 0 };
	frame++;
	t_time = t_time + time;
	if (t_time - timebase > 1) {
		sprintf_s(s, 256, "FPS:%4.2f", frame * 1.0 / (t_time - timebase));
		timebase = t_time;
		frame = 0;
		printf("帧率为：%s\n", s);
	}
}

void GameApp::setViewSize(GLfloat widht, GLfloat height)
{
	_viewWidth = widht;
	_viewHeight = height;
	_reLoadView = true;
}

void GameApp::setProjectSize(GLfloat widht, GLfloat height)
{
	_projectWidth = widht;
	_projectHeight = height;
	_reLoadView = true;
}


GLUSvoid GameApp::programKey(const GLUSboolean pressed, const GLUSint key)
{
	if (key == GLFW_KEY_UP || key == 'w' || key == 'W')
	{ 
		if (pressed)
		{
			printf("上键 按下");
		}
		else
		{
			printf("上键 弹起");
		}
		_start->onUp(pressed);
	}
	if (key == GLFW_KEY_DOWN || key == 's' || key == 'S')
	{
		if (pressed)
		{
			printf("下键 按下");
		}
		else
		{
			printf("下键 弹起");
		}
		_start->onDown(pressed);
	}
	if (key == GLFW_KEY_LEFT || key == 'a' || key == 'A')
	{
		if (pressed)
		{
			printf("左键 按下");
		}
		else
		{
			printf("左键 弹起");
		}
		_start->onLeft(pressed);
	}
	if (key == GLFW_KEY_RIGHT || key == 'd' || key == 'D')
	{
		if (pressed)
		{
			printf("右键 按下");
		}
		else
		{
			printf("右键 弹起");
		}
		_start->onRight(pressed);
	}
	if (key == GLFW_KEY_SPACE)
	{
		if (pressed)
		{
			printf("右键 按下");
		}
		else
		{
			printf("右键 弹起");
		}
		_start->onRotate(pressed);
	}
}
