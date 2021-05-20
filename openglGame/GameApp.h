#pragma once
#include <map>
#include <memory>
#include "GL/glus.h"
#include "base/Shader.h"
#include "base/Singleton.h"
#include <vector>
#include "2d/Node.h"
#include "GameStart.h"
#include "dexode/EventBus.hpp"
#include "GameEvent.h"
#include "base/ControllerBase.hpp"
#include "GameUI.h"

using namespace std;

class GameApp
{
public: 
	//SingletonClase(GameApp);

	static shared_ptr<GameApp> getInstance() 
	{ 
		static shared_ptr<GameApp> instance = make_shared<GameApp>();
		//instance->record(instance);
		return instance;
	}

public:

	GameApp();
	~GameApp();
	int initShader();
	int removeAllShader();

	int initTouchUI();
	void onTouchHandler(const MouseKeyEvent& et);

	void init();
	void reshape();
	void visit();
	void rander();		
	//��һЩ����֮�����������
	void update(float time);

	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> createListenerSP();

	inline shared_ptr<dexode::EventBus> getEventBus() { return _events; }

	Vector2 convertToWorld(Node*node, const Vector2&pos);
	Vector2 convertViewToNode(Node*node, const Vector2&pos);
public:
	GLint getProgram(const char*name);
	SPShader getShader(const char*name);

	void setViewSize(GLfloat widht, GLfloat height);
	void setProjectSize(GLfloat widht, GLfloat height);
	GLboolean isReLoadView() { return _reLoadView; }
	GLfloat getViewWidth() { return _viewWidth; }
	GLfloat getViewHeight() { return _viewHeight; }
	GLfloat getProjectWidth() { return _projectWidth; }
	GLfloat getProjectHeight() { return _projectHeight; }
	void setWindowSize(GLfloat width, GLfloat height);
	inline GLfloat getProScale() { return _proScale; }

	int getNodeCount();

	void postEvent(EventType);	//ֻ������ͨ��Event��Ϣ

	inline float getLastTime() { return _last_time; }
protected:
	map<string, SPShader> _shaders;

	//GLfloat _projectionMatrix[16];
	GLfloat _viewMatrix[16];
	GLfloat _modelMatrix[16];
	GLfloat _modelViewMatrix[16];

	GLfloat _viewWidth;			//���ڿ��
	GLfloat _viewHeight;		//���ڸ߶�
	GLfloat _projectWidth;		//��ƿ�ȣ���ʼ�����������
	GLfloat _projectHeight;		//��Ƹ߶ȣ���ʼ�����������
	GLfloat _transform[16];
	GLfloat _proScale = 1;

	GLboolean _reLoadView = true;	//���¼��ش���

	shared_ptr<dexode::EventBus> _events = make_shared<dexode::EventBus>();
	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;

	shared_ptr<ControllerMaster> _controllerMaster;

	float _last_time = 0.0f;
public:
	SPNode	_appNode;
	SPNode	_bg;
	SPNode	_start;
	SPNode	_ui;
	//shared_ptr<GameStart> _start;
	//shared_ptr<GameUI> _ui;
};

