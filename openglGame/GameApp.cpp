#include "GameApp.h"
#include<iostream>
#include "FillDrawNode.h"
GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

void GameApp::init()
{
	this->initShader();

	//»­¸ñ×Ó
	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
		{
			auto fd = FillDrawNode::create();
			fd->addVertex(Vector2(0, 0));
			fd->addVertex(Vector2(40, 0));
			fd->addVertex(Vector2(40, 40));
			fd->addVertex(Vector2(0, 40));

			fd->setPosition(Vector2(40 * x, 40 * y));
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
}

int GameApp::initShader()
{
	glusMatrix4x4Identityf(_projectionMatrix);
	glusMatrix4x4Identityf(_viewMatrix);
	glusMatrix4x4Identityf(_modelMatrix);

	const char* shaders[] = { "rendershadow", "useshadow" ,"default", "filldraw"};

	for (int i = 0; i < sizeof(shaders) / sizeof(char*); ++i)
	{
		const char* shaderName = shaders[i];

		SPShader shader = make_shared<Shader>();
		shader->loadShader(shaderName);
		
		_shaders->insert(map<string, SPShader>::value_type(shaderName, shader));
	}

	FillDrawNode::initFillDrawProgram();
	//filldraw
	auto app = GameApp::getInstance();

	//glGetUniformLocation

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

void GameApp::draw()
{
	Node::draw();

	//do something
}

void GameApp::reshape()
{
	Node::reshape();
	_reLoadView = false;

	GLfloat biasMatrix[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	//ModelViewProject = Project * View * Model;
	GLfloat modelViewProjectionMatrix[16];
	GLfloat modelViewMatrix[16];

	GLfloat viewMatrix[] = { 
		2 / _viewWidth, 0.0f, 0.0f, 0.0f,
		0.0f, 2 / _viewHeight, 0.0f, 0.0f,
		0.0f, 0.0f, 1.f, 0.0f,
		-1, -1, 0.0f, 1.0f };
	glusMatrix4x4Copyf(_viewMatrix, viewMatrix, false);

	glusMatrix4x4Multiplyf(modelViewMatrix, _viewMatrix, _modelMatrix);
	glusMatrix4x4Multiplyf(modelViewProjectionMatrix, _projectionMatrix, modelViewMatrix);

	glusMatrix4x4Multiplyf(modelViewProjectionMatrix, modelViewProjectionMatrix, biasMatrix);

	for (auto it = _shaders->begin(); it != _shaders->end(); it++)
	{
		GLint g_modelViewProjectionMatrix = glGetUniformLocation(it->second->getProgram(), "u_modelViewProjectionMatrix");

		glUniformMatrix4fv(g_modelViewProjectionMatrix, 1, GL_FALSE, modelViewProjectionMatrix);

	}
}

void GameApp::update(float time)
{
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
