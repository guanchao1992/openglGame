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

//Node��������Ҫ���ⲿʹ�ú�StatementNode����׼������
#define	StatementNode(ClassType);	class ClassType;typedef shared_ptr<ClassType> SP##ClassType;

//Node��������Ҫ�����ڲ�ʹ�ú�StatementCreateNode��������ص�static create����
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
	SPNode getChildByTag(int tag);			//�ҵ��ӽڵ��е�һ��ƥ��tag����
	void setPosition(const Vector2&pos);
	void setPosition(float x, float y);
	void setPosition(const Vector3&pos);
	void setPosition(float x, float y, float z);
	void setEulerAngle(float angleZ);
	void setAngle(float angleZ);			//2d��ϷĬ�ϵ�����Z����ת
	void setAngleCoordinate(float angleX, float angleY, float angleZ);		//�ֱ�����������X�ᣬY�ᣬZ�����תһ�Ρ�
	void setRotateAxis(Vector3 vec, float angle);		//����һ���������Ը�����Ϊ����ת��

	void setScaleX(float scale);
	void setScaleY(float scale);
	void setScale(float scaleX, float scaleY, float scaleZ);
	void setScale(float scale);

	void refreshTransformParent(); //���� _transform
	GLfloat* getTransformParent();
	void refreshOrder();	//ˢ�� �ڵ�˳��

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
	//��������ӽڵ�����
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

	//��ת˳����ZYX
	float _angleX = 0.0f;				//��X����ת�Ƕȣ���ʱ�������ݣ�
	float _angleY = 0.0f;				//��Y����ת�Ƕȣ���ʱ�������ݣ�
	float _angleZ = 0.0f;				//��Z����ת�Ƕȣ���ʱ�������ݣ�

	//������ת���㷽ʽ
	Vector3		_rotateAxis = Vector3(0.f, 0.f, 0.f);	//������������
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

	bool _revisit = true;	//��Ҫ���¼���任����
	bool _reorder = true;	//��Ҫ���¶��ӽڵ��������
	bool _visible = true;	//�Ƿ���ʾ

	vector<int> _timerids;

protected:
	RanderComponent* _randerComponent = nullptr;		//����ģ�������ʾ
};

