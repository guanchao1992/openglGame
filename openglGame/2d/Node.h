#pragma once

#include <memory>
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "Base/Vector3.h"
#include <vector>
#include "Base/Shader.h"
#include "Base/Vector4.h"

using namespace std;


//Node的子类需要在外部使用宏StatementNode做好准备工作
#define	StatementNode(ClassType);	class ClassType;typedef shared_ptr<ClassType> SP##ClassType;

//Node的子类需要在类内部使用宏StatementCreateNode，创建相关的static create函数
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
	void record(SPNode selfNode); //记录智能指针。该记录会在removeFromParent中删除。
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
	void setAngle(float angle);			//2d游戏默认的是绕Z轴旋转
	void setAngleCoordinate(float angleX, float angleY, float angleZ);		//分别绕着坐标轴X轴，Y轴，Z轴各旋转一次。
	void setRotateAxis(Vector3 vec, float angle);		//设置一个向量，以该向量为轴旋转。

	void setScaleX(float scale);
	void setScaleY(float scale);
	void setScale(float scaleX, float scaleY);

	void setContentSize(const Size&size);

	void refreshTransformParent(); //更新 _transform

	void setColor(const Vector4&color);
	void setColor(float r, float g, float b, float l);

	const Vector4& getColor() { return _color; }
	const Vector2& getPosition() { return _position; }
	const Size& getContentSize() { return _contentSize; }
	SPNode getParent() { return _parent; }


	void recodeDraw();//将要重绘

protected:

	SPShader _shader;
	Size _contentSize;
	Vector2 _position;

	//旋转顺序是ZYX
	float _angleX = 0.0f;				//绕X轴旋转角度（临时计算数据）
	float _angleY = 0.0f;				//绕Y轴旋转角度（临时计算数据）
	float _angleZ = 0.0f;				//绕Z轴旋转角度（临时计算数据）

	//两种旋转计算方式
	Vector3		_rotateAxis;	//给定的轴向量
	float		_angleAxis;

	float _scaleX = 1.0f;
	float _scaleY = 1.0f;

	Vector4 _color;
	SPNode _parent;
	SPNode _this;		//引用计数自增，控制清空内存的时机

	shared_ptr<vector<SPNode>> _childs = make_shared<vector<SPNode>>();

	GLfloat _mvTransform[16]; // transform to draw
	GLfloat _transform[16]; // transform to parent

	bool _revisit = true;
	bool _redraw = true;	//重绘总开关
	bool _repos = true;		//坐标发生变动
};


