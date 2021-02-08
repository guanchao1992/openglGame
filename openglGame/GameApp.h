#pragma once
#include <map>
#include <memory>
#include "GL/glus.h"
#include "Base/Shader.h"
#include "Base/Singleton.h"
#include <vector>
#include "2d/Node.h"
#include "GameStart.h"

using namespace std;


class GameApp : public Node
{
	SingletonClase(GameApp);
protected:
	GameApp();
	~GameApp();
public:
	int initShader();
	int removeAllShader();

	virtual void init();
	virtual void rander();
	virtual void draw(const GLfloat *parentTransform);
	virtual void reshape();
	//做一些绘制之外的其他操作
	void update(float time);

	GLUSvoid programKey(const GLUSboolean pressed, const GLUSint key);
public:
	GLint getProgram(const char*name);
	SPShader getShader(const char*name);

	void addNode(SPNode node);
	void setViewSize(GLfloat widht, GLfloat height);
	void setProjectSize(GLfloat widht, GLfloat height);
	GLboolean isReLoadView() { return _reLoadView; }
	GLfloat getViewWidth() { return _viewWidth; }
	GLfloat getViewHeight() { return _viewHeight; }
	GLfloat getProjectWidth() { return _viewWidth; }
	GLfloat getProjectHeight() { return _viewHeight; }
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

	GLboolean _reLoadView;	//重新加载窗口
public:
	shared_ptr<GameStart> _start;
};

