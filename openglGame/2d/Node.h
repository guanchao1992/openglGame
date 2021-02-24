#pragma once

#include <memory>
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "Base/Vector3.h"
#include <vector>
#include "Base/Shader.h"
#include "Base/Vector4.h"

using namespace std;


//Node��������Ҫ���ⲿʹ�ú�StatementNode����׼������
#define	StatementNode(ClassType);	class ClassType;typedef shared_ptr<ClassType> SP##ClassType;

//Node��������Ҫ�����ڲ�ʹ�ú�StatementCreateNode��������ص�static create����
#define StatementCreate(ClassType); public: static shared_ptr<ClassType> create() \
									{	shared_ptr<ClassType> node = make_shared<ClassType>();\
										node->record(node); node->init(); return node; }


StatementNode(Node)
class Node
{
	StatementCreate(Node)
protected:
	//
	//Node() {};
	//~Node() {};
public:
	void record(SPNode selfNode); //��¼����ָ�롣�ü�¼����removeFromParent��ɾ����
public:
	virtual void init() {};
	virtual void reshape();
	virtual void rander();

	virtual void visit(const GLfloat *parentTransform, GLboolean parentFlag);
	virtual void draw(const GLfloat *parentTransform);
	GLint getProgram() { return _shader->getProgram(); };

	void addChild(SPNode node);
	void removeFromParent();
	void removeChild(SPNode node);
	vector<SPNode> getChilds();
	void setPosition(const Vector2&pos);
	void setPosition(float x, float y);
	void setAngle(float angle);			//2d��ϷĬ�ϵ�����Z����ת
	void setAngleCoordinate(float angleX, float angleY, float angleZ);		//�ֱ�����������X�ᣬY�ᣬZ�����תһ�Ρ�
	void setRotateAxis(Vector3 vec, float angle);		//����һ���������Ը�����Ϊ����ת��

	void setScaleX(float scale);
	void setScaleY(float scale);
	void setScale(float scaleX, float scaleY);

	void setContentSize(const Size&size);

	void refreshTransformParent(); //���� _transform

	void setColor(const Vector4&color);
	void setColor(float r, float g, float b, float l);

	const Vector4& getColor() { return _color; }
	const Vector2& getPosition() { return _position; }
	const Size& getContentSize() { return _contentSize; }
	SPNode getParent() { return _parent; }


	void recodeDraw();//��Ҫ�ػ�

protected:

	SPShader _shader;
	Size _contentSize;
	Vector2 _position;

	//��ת˳����ZYX
	float _angleX = 0.0f;				//��X����ת�Ƕȣ���ʱ�������ݣ�
	float _angleY = 0.0f;				//��Y����ת�Ƕȣ���ʱ�������ݣ�
	float _angleZ = 0.0f;				//��Z����ת�Ƕȣ���ʱ�������ݣ�

	//������ת���㷽ʽ
	Vector3		_rotateAxis;	//������������
	float		_angleAxis;

	float _scaleX = 1.0f;
	float _scaleY = 1.0f;

	Vector4 _color;
	SPNode _parent;
	SPNode _this;		//���ü�����������������ڴ��ʱ��

	shared_ptr<vector<SPNode>> _childs = make_shared<vector<SPNode>>();

	GLfloat _mvTransform[16]; // transform to draw
	GLfloat _transform[16]; // transform to parent

	bool _revisit = true;
	bool _redraw = true;	//�ػ��ܿ���
	bool _repos = true;		//���귢���䶯
};


