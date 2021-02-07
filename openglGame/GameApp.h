#pragma once
#include <map>
#include <memory>
#include "GL/glus.h"
#include "Shader.h"
#include "Base/Singleton.h"
#include <vector>
#include "Node.h"

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
	virtual void draw();
	virtual void reshape();
	//��һЩ����֮�����������
	void update(float time);
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

	GLfloat _projectionMatrix[16];
	GLfloat _viewMatrix[16];
	GLfloat _modelMatrix[16];

	GLfloat _viewWidth;			//���ڿ��
	GLfloat _viewHeight;		//���ڸ߶�
	GLfloat _projectWidth;		//��ƿ��
	GLfloat _projectHeight;		//��Ƹ߶�

	GLboolean _reLoadView;	//���¼��ش���
};

