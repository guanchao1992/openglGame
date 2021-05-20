#include "GameApp.h"
#include<iostream>
#include "ShaderFiles.h"
#include "control/TextureController.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <synchapi.h>
#include <math.h>
#include "nlohmann/json.hpp"
#include <iostream> 
#include <fstream> 
#include "component/DrawRanderComponent.h"
#include "component/TextureRanderComponent.h"
#include <functional>
#include "control/MouseController.h"
#include "component/AreaComponent.h"
#include "Game2DFight/GameMainFight.h"

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
	_listener->listen([this](const Event& event) {
		printf("测试事件,接受到事件ID：%d\n", event._eventId);
	});
	*/
	this->initShader();
	this->setProjectSize(1400, 900);

	_appNode = Node::create();
	_bg = Node::create();
	_appNode->addChild(_bg, 0);

	_ui = GameUI::create();
	_appNode->addChild(_ui, 100);

	auto appDrawCom = _bg->addComponent<DrawRanderComponent>();
	appDrawCom->addVertex(Vector2(0, 0), Vector4(0.3, 0.3, 0, 0.5));
	appDrawCom->addVertex(Vector2(_projectWidth, 0), Vector4(0.3, 0.3, 0, 0.5));
	appDrawCom->addVertex(Vector2(_projectWidth, _projectHeight), Vector4(0.3, 0.3, 0, 0.5));
	appDrawCom->addVertex(Vector2(0, _projectHeight), Vector4(0.3, 0.3, 0, 0.5));
	appDrawCom->signDraw(GL_TRIANGLE_FAN);
	_bg->setPosition(0, 0);
	//_bg->setColor(Vector4(0.3, 0.3, 0, 0.5));

	//_start = GameStart::create();
	_start = GameMainFight::create();
	_appNode->addChild(_start, 10);


	/*
	char path[256];
	int index = 1;
	//画格子
	for (int x = 5; x < 10; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			auto tn = Node::create();
			tn->addComponent<AreaComponent>()->setSize(Size(120, 120));
			auto textureCom = tn->addComponent<TextureRanderComponent>();
			sprintf_s(path, 256, ".\\res\\test (%d).png", index++);
			auto pt = TextureController::getInstance()->loadPng(path);
			textureCom->setTextureID(pt->_textureId);

			tn->setPosition(Vector2(120 * x, 120 * y));
			_start->addChild(tn, -1000);
		}
	}

	*/
	postEvent(EVENT_GAME_RESTART);
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
		
		_shaders.insert(map<string, SPShader>::value_type(shaderName, shader));
	}


	return 0;
}

int GameApp::removeAllShader()
{
	for (auto it = _shaders.begin(); it != _shaders.end(); it++)
	{
		glusProgramDestroy(it->second->_sprogram.get());
	}
	_shaders.clear();
	return 0;
}

int GameApp::initTouchUI()
{
	_listener = GameApp::getInstance()->createListenerSP();
	//_listener->listen([this](const MouseKeyEvent& et) { });
	_listener->listen<MouseKeyEvent>(std::bind(&GameApp::onTouchHandler, this, std::placeholders::_1));
	return 0;
}

void GameApp::onTouchHandler(const MouseKeyEvent& et)
{
	//_ui->onTouchHandler(et);
	//this->_ui->onTouchHandler();
}

//getSprogram(const char*name);
GLint GameApp::getProgram(const char* name)
{
	auto sp_shader = _shaders.at(name);
	if (sp_shader != nullptr)
	{
		return sp_shader->getProgram();
	}
	return -1;
}

SPShader GameApp::getShader(const char*name)
{
	auto sp_shader = _shaders.at(name);
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

	float w_s = _viewWidth / _projectWidth;
	float h_s = _viewHeight / _projectHeight;
	_proScale = w_s < h_s ? w_s : h_s;

	const GLfloat biasMatrix[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };
	glusMatrix4x4Copyf(_transform, biasMatrix, false);
	if (w_s < h_s)
	{
		_transform[12] = 0;
		_transform[13] = (_viewHeight / _proScale - _projectHeight) / 2;
	}
	else
	{
		_transform[12] = (_viewWidth / _proScale - _projectWidth) / 2;
		_transform[13] = 0;
	}

	GLfloat viewMatrix[] = {
		2 / _viewWidth * _proScale, 0.0f, 0.0f, 0.0f,
		0.0f, 2 / _viewHeight * _proScale, 0.0f, 0.0f,
		0.0f, 0.0f, 0.1 / _viewWidth * _proScale, 0.8 / _viewWidth * _proScale,
		-1, -1, -0.5f, 1.0f };

	glusMatrix4x4Copyf(_viewMatrix, viewMatrix, false);
	glusMatrix4x4Multiplyf(_modelViewMatrix, _viewMatrix, _modelMatrix);

	for (auto it = _shaders.begin(); it != _shaders.end(); it++)
	{
		auto program = it->second->getProgram();
		glUseProgram(program);
		GLint g_modelViewMatrix = glGetUniformLocation(program, "u_modelViewMatrix");
		glUniformMatrix4fv(g_modelViewMatrix, 1, GL_FALSE, _modelViewMatrix);
	}
	glUseProgram(0);

	//_appNode->reshape();
	_bg->reshape();
	_start->reshape();
	_ui->reshape();
}

void GameApp::visit()
{
	_bg->visit(_transform, false);
	_start->visit(_transform, false);
	_ui->visit(_transform, false);
}

void GameApp::rander()
{
	//_appNode->rander();
	_bg->rander();
	_start->rander();
	_ui->rander();
}

void GameApp::update(float time)
{
	_last_time = time;
	_controllerMaster->update(time);
	_events->process();
}

void GameApp::setViewSize(GLfloat width, GLfloat height)
{
	_viewWidth = width;
	_viewHeight = height;
	_reLoadView = true;
}

void GameApp::setProjectSize(GLfloat width, GLfloat height)
{
	_projectWidth = width;
	_projectHeight = height;
	_reLoadView = true;
}

void GameApp::setWindowSize(GLfloat width, GLfloat height)
{
	auto window = glfwGetCurrentContext();
	if (window)
	{
		glfwSetWindowSize(window, width, height);
	}
}

shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> GameApp::createListenerSP()
{
	return make_shared<dexode::eventbus::Listener<dexode::eventbus::Bus>>(_events);
}

int GameApp::getNodeCount()
{
	return _ui->getAllChildNum() + _start->getAllChildNum();
}

Vector2 GameApp::convertToWorld(Node*node, const Vector2&pos)
{
	GLfloat projectTransform[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f };

	glusMatrix4x4Multiplyf(projectTransform, projectTransform, _transform);

	vector<Node*> _quest_node;
	Node*temp_node = node;
	while (temp_node)
	{
		_quest_node.push_back(temp_node);
		temp_node = temp_node->getParent();
	}
	for (auto it = _quest_node.rbegin(); it != _quest_node.rend(); it++)
	{
		auto transform = (*it)->getTransformParent();
		glusMatrix4x4Multiplyf(projectTransform, projectTransform, transform);
	}

	GLfloat transform[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	pos._x / _proScale, pos._y / _proScale, 0.0f, 1.0f };

	glusMatrix4x4Multiplyf(transform, projectTransform, transform);
	
	return Vector2(transform[12], transform[13]);
}

Vector2 GameApp::convertViewToNode(Node*node, const Vector2&pos)
{
	GLfloat projectTransform[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f };

	glusMatrix4x4Multiplyf(projectTransform, projectTransform, _transform);

	vector<Node*> _quest_node;
	Node*temp_node = node;
	while (temp_node)
	{
		_quest_node.push_back(temp_node);
		temp_node = temp_node->getParent();
	}
	for (auto it = _quest_node.rbegin(); it != _quest_node.rend(); it++)
	{
		auto transform = (*it)->getTransformParent();
		glusMatrix4x4Multiplyf(projectTransform, projectTransform, transform);
	}
	glusMatrix4x4Inversef(projectTransform);

	GLfloat transform[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	pos._x / _proScale, pos._y / _proScale, 0.0f, 1.0f };

	glusMatrix4x4Multiplyf(transform, projectTransform, transform);

	return Vector2(transform[12], transform[13]);
}

void GameApp::postEvent(EventType type)
{
	_events->postpone(Event{ type });
}
