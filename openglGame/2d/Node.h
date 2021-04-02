#pragma once

#include <memory>
#include "base/Size.h"
#include "base/Vector2.h"
#include "base/Vector3.h"
#include <vector>
#include "base/Shader.h"
#include "base/Vector4.h"
#include "control/TimerController.h"

using namespace std;


//Node的子类需要在外部使用宏StatementNode做好准备工作
#define	StatementNode(ClassType);	class ClassType;typedef shared_ptr<ClassType> SP##ClassType;

//Node的子类需要在类内部使用宏StatementCreateNode，创建相关的static create函数
#define StatementCreate(ClassType); public: static shared_ptr<ClassType> create() \
									{	shared_ptr<ClassType> node = make_shared<ClassType>();\
										node->record(node); node->init(); return node; }

#define StatementCreateN1(ClassType,T1,N1); public: static shared_ptr<ClassType> create(T1 N1) \
									{	shared_ptr<ClassType> node = make_shared<ClassType>();\
										node->record(node); node->init(N1); return node; }

#define StatementCreateN2(ClassType,T1,N1,T2,N2); public: static shared_ptr<ClassType> create(T1 N1,T2 N2) \
									{	shared_ptr<ClassType> node = make_shared<ClassType>();\
										node->record(node); node->init(N1,N2); return node; }

StatementNode(Node)
class Node
{
	StatementCreate(Node)
protected:
public:
	//Node() {};
	~Node(); 
	void record(SPNode selfNode); //记录智能指针。该记录会在removeFromParent中删除。
public:
	virtual void init() {};
	virtual void reshape();
	void rander();		
	virtual void randerOne();

	virtual void visit(const GLfloat *parentTransform, GLboolean parentFlag);
	virtual void onDraw();
	GLint getProgram() { return _shader->getProgram(); };

	void addChild(SPNode node,int zOrder = 0);
	void removeFromParent();
	void removeAllChild();
	const vector<SPNode>& getChilds();
	SPNode getChildByTag(int tag);			//找到子节点中第一个匹配tag的项
	void setPosition(const Vector2&pos);
	void setPosition(float x, float y);
	void setEulerAngle(float angleZ);
	void setAngle(float angleZ);			//2d游戏默认的是绕Z轴旋转
	void setAngleCoordinate(float angleX, float angleY, float angleZ);		//分别绕着坐标轴X轴，Y轴，Z轴各旋转一次。
	void setRotateAxis(Vector3 vec, float angle);		//设置一个向量，以该向量为轴旋转。

	void setScaleX(float scale);
	void setScaleY(float scale);
	void setScale(float scaleX, float scaleY);

	void setContentSize(const Size&size);

	void refreshTransformParent(); //更新 _transform
	void refreshOrder();	//刷新 节点顺序

	void setColor(const Vector4&color);
	void setColor(float r, float g, float b, float l);

	const Vector4& getColor() { return _color; }
	const Vector2& getPosition() { return _position; }
	const Size& getContentSize() { return _contentSize; }
	Node* getParent() { return _parent; }

	void setZOrder(int localZOrder);
	int getZOrder() { return _localZOrder; }

	void setTag(int tag);
	int getTag() { return _tag; }

	int addTimer(float interval, int num, TimerCallback callback);
	void killTimer(int killId);
	void killAllTimer();

	void setVisible(bool visible);
	bool isVisible() { return _visible; }
	//debug
	//获得所有子节点数量
	int getAllChildNum();
protected:

	SPShader _shader = nullptr;
	Size _contentSize = Size(10.f, 10.f);	//暂时未用到
	Vector2 _position = Vector2(0.f, 0.f);

	//旋转顺序是ZYX
	float _angleX = 0.0f;				//绕X轴旋转角度（临时计算数据）
	float _angleY = 0.0f;				//绕Y轴旋转角度（临时计算数据）
	float _angleZ = 0.0f;				//绕Z轴旋转角度（临时计算数据）

	//两种旋转计算方式
	Vector3		_rotateAxis = Vector3(0.f, 0.f, 0.f);	//给定的轴向量
	float		_angleAxis = 0.0f;

	float _scaleX = 1.0f;
	float _scaleY = 1.0f;

	Vector4 _color = Vector4(1.f, 1.f, 1.f, 1.f);
	Node* _parent = nullptr;

	shared_ptr<vector<SPNode>> _childs = make_shared<vector<SPNode>>();

	shared_ptr<vector<SPNode>> _visitLeft = make_shared<vector<SPNode>>();
	shared_ptr<vector<SPNode>> _visitRight = make_shared<vector<SPNode>>();

	int _localZOrder = 0;
	int _tag = 0;

	GLfloat _projectTransform[16]; // transform to draw
	GLfloat _transform[16]; // transform to parent

	bool _revisit = true;	//需要重新计算变换矩阵
	bool _redraw = true;	//需要刷新缓冲区数据
	bool _reorder = true;	//需要重新对子节点进行排序
	bool _revertexs = true; //需要重新创建缓冲区
	bool _visible = true;	//是否显示

	shared_ptr<vector<int>> _timerids = make_shared<vector<int>>();
};


