#include "GameApp.h"
#include<iostream>
#include "2d/FillDrawNode.h"
#include "2d/TextureNode.h"
#include "ShaderFiles.h"
#include "control/TextureController.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <synchapi.h>
#include <math.h>
#include <2d/FontDrawNode.h>
#include "nlohmann/json.hpp"
#include <iostream> 
#include <fstream> 

GameApp::GameApp()
{
	_listener = createListenerSP();
	_controllerMaster = ControllerMaster::getInstance();
}

GameApp::~GameApp()
{
}

void GameApp::init()
{
	/*
	*/
	_listener->listen([&](const Event& event) {
		printf("测试事件,接受到事件ID：%d\n", event._eventId);
	});

	this->initShader();

	_start = GameStart::create();
	_ui = GameUI::create();


	//画格子
	auto fd = FillDrawNode::create();
	fd->setPosition(0, 0);
	_start->addChild(fd, -1000);
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			if ((x + y) % 2 == 0)
			{
				fd->addVertex(Vector2(120 * x + 0, 120 * y + 0), Vector4(0.2, 0.2, 0.2, 1));
				fd->addVertex(Vector2(120 * x + 120, 120 * y + 0), Vector4(0.2, 0.2, 0.2, 1));
				fd->addVertex(Vector2(120 * x + 120, 120 * y + 120), Vector4(0.2, 0.2, 0.2, 1));
				fd->addVertex(Vector2(120 * x + 0, 120 * y + 120), Vector4(0.2, 0.2, 0.2, 1));
				fd->signDraw(GL_TRIANGLE_FAN);
			}
			else
			{
				fd->addVertex(Vector2(120 * x + 0, 120 * y + 0), Vector4(0.3, 0.3, 0.3, 1));
				fd->addVertex(Vector2(120 * x + 120, 120 * y + 0), Vector4(0.3, 0.3, 0.3, 1));
				fd->addVertex(Vector2(120 * x + 120, 120 * y + 120), Vector4(0.3, 0.3, 0.3, 1));
				fd->addVertex(Vector2(120 * x + 0, 120 * y + 120), Vector4(0.3, 0.3, 0.3, 1));
				fd->signDraw(GL_TRIANGLE_FAN);
			}
		}
	}

	char path[256];
	int index = 1;
	//画格子
	for (int x = 5; x < 10; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			auto tn = TextureNode::create();
			tn->addVertex(Vector2(0, 0), Vector2(0, 0));
			tn->addVertex(Vector2(0, 120), Vector2(0, 1));
			tn->addVertex(Vector2(120, 120), Vector2(1, 1));
			tn->addVertex(Vector2(120, 0), Vector2(1, 0));
			sprintf_s(path, 256, ".\\res\\test (%d).png", index++);
			auto pt = TextureController::getInstance()->loadPng(path);
			tn->setTextureID(pt->_textureId);

			tn->setPosition(Vector2(120 * x, 120 * y));
			_start->addChild(tn, -1000);
		}
	}

	_events->postpone(Event{ EventType::EVENT_GAME_RESTART });
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
	FontDrawNode::initProgram();


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

void GameApp::reshape()
{
	//Node::reshape();
	_reLoadView = false;

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

	_start->reshape();
	_ui->reshape();
}

void GameApp::visit(const GLfloat *parentTransform, GLboolean parentFlag)
{
	_start->visit(parentTransform, false);
	_ui->visit(_viewMatrix, false);
}

void GameApp::rander()
{
	_start->rander();
	_ui->rander();
}

void GameApp::update(float time)
{
	_controllerMaster->update(time);

	_start->update(time);
	_ui->update(time);

	_events->process();

	static float s_fps = 1.0f / 60;

	float pause_time = 0;
	if (s_fps > time )
	{
		float sti = s_fps - time ;

		Sleep(sti * 1000);
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

shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> GameApp::createListenerSP()
{
	return make_shared<dexode::eventbus::Listener<dexode::eventbus::Bus>>(_events);
}

int GameApp::getNodeCount()
{
	return _ui->getAllChildNum() + _start->getAllChildNum();
}
