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
	//_ui->setVisible(false);

	auto bgColor = Vector4(0.5, 0.5, 0.4, 0.5);
	auto appDrawCom = _bg->addComponent<DrawRanderComponent>();
	appDrawCom->addVertex(Vector3(0, 0, 0), bgColor);
	appDrawCom->addVertex(Vector3(_projectWidth, 0, 0), bgColor);
	appDrawCom->addVertex(Vector3(_projectWidth, _projectHeight, 0), bgColor);
	appDrawCom->addVertex(Vector3(0, _projectHeight, 0), bgColor);
	appDrawCom->signDraw(GL_TRIANGLE_FAN);
	auto bgAreaCom = _bg->addComponent<AreaComponent>();
	bgAreaCom->setSize(Size(_projectWidth, _projectHeight));
	bgAreaCom->setAnchor(Vector2(0.5, 0.5));
	_bg->setPosition(0, 0, _projectWidth);

	_start = GameStart::create();
	//_start = GameMainFight::create();
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
	/*
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
	*/

	/*
	以下参数分别是:
		y方向的视角
		纵横比
		*剪裁*面到原点的距离
		远剪裁*面到原点的距离
	*/
	float fov = PI / 4;
	float aspect = 1.0f;// *_viewWidth / _viewHeight;
	float zn = 1000;
	float zf = 100000;

	GLfloat viewMatrix[] = {
		1 / (tan(fov * 0.5f) * aspect), 0.f, 0.f, 0.f,
		0.f, 1 / tan(fov * 0.5f), 0.f, 0.f,
		0.f, 0.f, zf / (zf - zn), 1.f / _viewWidth,
		0.0f, 0.0f, (zn * zf) / (zn - zf), 1.0f
	};

	//glewMatrixRotated
	//glusMatrix4x4RotateRzRxRyf(viewMatrix, 0, 11.25, 0);

	/*
	static GLUSfloat g_cameraPosition[3] = { .0f, .0f, 10.0f };
	glusMatrix4x4LookAtf(viewMatrix, 
		g_cameraPosition[0], g_cameraPosition[1], g_cameraPosition[2],
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	*/

	GLfloat modelMatrix[] = {
		1.0f/ _viewWidth * _proScale, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f/ _viewHeight * _proScale, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f / _viewWidth * _proScale * 0.1, 0.0f,
		-.0f, -.0f, -0.f, 1.0f };

	/*
	GLfloat modelMatrix[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.5f, 1.0f };
	*/
	/*
		transformMat = glm::rotate(transformMat, _angleZ, 0.f, 0.f, 1.f);
		transformMat = glm::rotate(transformMat, _angleY, 0.f, 1.f, 0.f);
	*/

	glusMatrix4x4Copyf(_viewMatrix, viewMatrix, false);
	glusMatrix4x4Copyf(_modelMatrix, modelMatrix, false);

	glusMatrix4x4Multiplyf(_modelViewMatrix, _modelMatrix, _viewMatrix);

	glusMatrix4x4Copyf(_reverseModelViewMatrix, _modelViewMatrix, false);
	glusMatrix4x4Inversef(_reverseModelViewMatrix);

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
	glEnable(GL_DEPTH_TEST);
	_bg->rander();
	_start->rander();
	glDisable(GL_DEPTH_TEST);
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

Vector3 GameApp::convertToWorld(Node*node, const Vector3&pos)
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
	pos._x / _proScale, pos._y / _proScale, pos._z / _proScale, 1.0f };

	glusMatrix4x4Multiplyf(transform, projectTransform, transform);
	
	return Vector3(transform[12], transform[13], transform[14]);
}

Vector3 GameApp::convertViewToNode(Node*node, const Vector3&pos)
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

	glusMatrix4x4Multiplyf(projectTransform, projectTransform, _modelViewMatrix);

	glusMatrix4x4Inversef(projectTransform);

	//GLfloat modelViewMatrix[16];
	//glusMatrix4x4Copyf(modelViewMatrix, _modelViewMatrix, false);
	//glusMatrix4x4Inversef(modelViewMatrix);

	//glusMatrix4x4Multiplyf(transform, viewMatrix, transform);


	float inPos[3] = { 2 * pos._x / _viewWidth + 1, 2 * pos._y / _viewHeight + 1, 0.2 * pos._z / _viewWidth };
	float outPos[3];
	glusMatrix4x4MultiplyVector3f(outPos, projectTransform, inPos);

	return Vector3(outPos[0], outPos[1], outPos[2]);
	//return Vector3(transform[12], transform[13], transform[14]);
}

Vector3 GameApp::posViewToWorld(int x, int y, float z)
{
	Vector3 out;
	auto n = _viewMatrix[10] * _viewMatrix[11] - _viewMatrix[10];
	auto f = _viewMatrix[10] * _viewMatrix[11] + _viewMatrix[10];

	out._x = (2 * x / _viewWidth * _proScale - 1) * (z + f) / n;
	out._y = (2 * y / _viewHeight * _proScale - 1) * (z + f) / n;
	//out._z = (2 * z / _viewWidth * _proScale - 0.5) * (z + f) / n;
	//2 / _viewWidth * _proScale * 0.1
	out._z = ((z / (_viewWidth * 5) - 0.5) / n);
		

	return out;
}

void GameApp::postEvent(EventType type)
{
	_events->postpone(Event{ type });
}
