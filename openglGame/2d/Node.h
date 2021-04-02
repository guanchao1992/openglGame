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


//Node��������Ҫ���ⲿʹ�ú�StatementNode����׼������
#define	StatementNode(ClassType);	class ClassType;typedef shared_ptr<ClassType> SP##ClassType;

//Node��������Ҫ�����ڲ�ʹ�ú�StatementCreateNode��������ص�static create����
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
	void record(SPNode selfNode); //��¼����ָ�롣�ü�¼����removeFromParent��ɾ����
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
	SPNode getChildByTag(int tag);			//�ҵ��ӽڵ��е�һ��ƥ��tag����
	void setPosition(const Vector2&pos);
	void setPosition(float x, float y);
	void setEulerAngle(float angleZ);
	void setAngle(float angleZ);			//2d��ϷĬ�ϵ�����Z����ת
	void setAngleCoordinate(float angleX, float angleY, float angleZ);		//�ֱ�����������X�ᣬY�ᣬZ�����תһ�Ρ�
	void setRotateAxis(Vector3 vec, float angle);		//����һ���������Ը�����Ϊ����ת��

	void setScaleX(float scale);
	void setScaleY(float scale);
	void setScale(float scaleX, float scaleY);

	void setContentSize(const Size&size);

	void refreshTransformParent(); //���� _transform
	void refreshOrder();	//ˢ�� �ڵ�˳��

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
	//��������ӽڵ�����
	int getAllChildNum();
protected:

	SPShader _shader = nullptr;
	Size _contentSize = Size(10.f, 10.f);	//��ʱδ�õ�
	Vector2 _position = Vector2(0.f, 0.f);

	//��ת˳����ZYX
	float _angleX = 0.0f;				//��X����ת�Ƕȣ���ʱ�������ݣ�
	float _angleY = 0.0f;				//��Y����ת�Ƕȣ���ʱ�������ݣ�
	float _angleZ = 0.0f;				//��Z����ת�Ƕȣ���ʱ�������ݣ�

	//������ת���㷽ʽ
	Vector3		_rotateAxis = Vector3(0.f, 0.f, 0.f);	//������������
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

	bool _revisit = true;	//��Ҫ���¼���任����
	bool _redraw = true;	//��Ҫˢ�»���������
	bool _reorder = true;	//��Ҫ���¶��ӽڵ��������
	bool _revertexs = true; //��Ҫ���´���������
	bool _visible = true;	//�Ƿ���ʾ

	shared_ptr<vector<int>> _timerids = make_shared<vector<int>>();
};


