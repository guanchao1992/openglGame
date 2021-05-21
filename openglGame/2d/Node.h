#pragma once

#include <memory>
#include "base/Size.h"
#include "base/Vector2.h"
#include "base/Vector3.h"
#include <vector>
#include "base/Shader.h"
#include "base/Vector4.h"
#include "control/TimerController.h"
#include "Object.hpp"
#include <list>

using namespace std;

class Component;
class Object;
class RanderComponent;
class MouseComponent;

//Node的子类需要在外部使用宏StatementNode做好准备工作
#define	StatementNode(ClassType);	class ClassType;typedef shared_ptr<ClassType> SP##ClassType;

//Node的子类需要在类内部使用宏StatementCreateNode，创建相关的static create函数
#define StatementCreate(ClassType); public: static shared_ptr<ClassType> create() \
									{	shared_ptr<ClassType> node = make_shared<ClassType>();node->init(); return node; }


StatementNode(Node)
class Node : public Object
{
	StatementCreate(Node)
protected:
public:
	~Node();
public:
	virtual void init() {};
	virtual void reshape();
	void rander();
	virtual void visit(const GLfloat *parentTransform, GLboolean parentFlag);

	void addChild(SPNode node,int zOrder = 0);
	void removeFromParent();
	void removeAllChild();
	const vector<SPNode>& getChilds();
	SPNode getChildByTag(int tag);			//找到子节点中第一个匹配tag的项
	void setPosition(const Vector2&pos);
	void setPosition(float x, float y);
	void setPosition(const Vector3&pos);
	void setPosition(float x, float y, float z);
	void setEulerAngle(float angleZ);
	void setAngle(float angleZ);			//2d游戏默认的是绕Z轴旋转
	void setAngleCoordinate(float angleX, float angleY, float angleZ);		//分别绕着坐标轴X轴，Y轴，Z轴各旋转一次。
	void setRotateAxis(Vector3 vec, float angle);		//设置一个向量，以该向量为轴旋转。

	void setScaleX(float scale);
	void setScaleY(float scale);
	void setScale(float scaleX, float scaleY, float scaleZ);
	void setScale(float scale);

	void refreshTransformParent(); //更新 _transform
	GLfloat* getTransformParent();
	void refreshOrder();	//刷新 节点顺序

	void setColor(const Vector4&color);
	void setColor(float r, float g, float b, float l);

	const Vector4& getColor() { return _color; }
	const Vector3& getPosition() { return _position; }
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

	//
	GLfloat* getProjectTransform() { return _projectTransform; }

	bool operator < (Node b)
	{
		return this->_localZOrder < b._localZOrder;
	}
	bool operator > (Node b)
	{
		return this->_localZOrder > b._localZOrder;
	}

public:
	void setRanderComponent(RanderComponent* com);
protected:

	Vector3 _position = Vector3(0.f, 0.f, 0.f);

	//旋转顺序是ZYX
	float _angleX = 0.0f;				//绕X轴旋转角度（临时计算数据）
	float _angleY = 0.0f;				//绕Y轴旋转角度（临时计算数据）
	float _angleZ = 0.0f;				//绕Z轴旋转角度（临时计算数据）

	//两种旋转计算方式
	Vector3		_rotateAxis = Vector3(0.f, 0.f, 0.f);	//给定的轴向量
	float		_angleAxis = 0.0f;

	float _scaleX = 1.0f;
	float _scaleY = 1.0f;
	float _scaleZ = 1.0f;

	Vector4 _color = Vector4(1.f, 1.f, 1.f, 1.f);
	Node* _parent = nullptr;

	vector<SPNode> _childs;
	std::list<Node*> _visitLeft;
	std::list<Node*> _visitRight;

	int _localZOrder = 0;
	int _tag = 0;

	GLfloat _projectTransform[16]; // transform to draw
	GLfloat _transform[16]; // transform to parent

	bool _revisit = true;	//需要重新计算变换矩阵
	bool _reorder = true;	//需要重新对子节点进行排序
	bool _visible = true;	//是否显示

	vector<int> _timerids;

protected:
	RanderComponent* _randerComponent = nullptr;		//特殊的，用于显示
};

