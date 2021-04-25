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
	void visit(const GLfloat *parentTransform, GLboolean parentFlag);
	void rander();		
	//做一些绘制之外的其他操作
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
	GLfloat getProjectWidth() { return _viewWidth; }
	GLfloat getProjectHeight() { return _viewHeight; }

	int getNodeCount();

	void postEvent(EventType);	//只允许发普通的Event消息
protected:
	shared_ptr<map<string, SPShader>> _shaders = make_shared<map<string, SPShader>>();

	//GLfloat _projectionMatrix[16];
	GLfloat _viewMatrix[16];
	GLfloat _modelMatrix[16];
	GLfloat _modelViewMatrix[16];

	GLfloat _viewWidth;			//窗口宽度
	GLfloat _viewHeight;		//窗口高度
	GLfloat _projectWidth;		//设计宽度，未生效
	GLfloat _projectHeight;		//设计高度，未生效

	GLboolean _reLoadView = true;	//重新加载窗口

	shared_ptr<dexode::EventBus> _events = make_shared<dexode::EventBus>();
	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;

	shared_ptr<ControllerMaster> _controllerMaster;
public:
	SPNode	_appNode;
	shared_ptr<GameStart> _start;
	shared_ptr<GameUI> _ui;
};

