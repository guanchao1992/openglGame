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
	void setContentSize(const Size&size);
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
	Vector4 _color;
	SPNode _parent;
	SPNode _this;		//引用计数自增，控制清空内存的时机

	shared_ptr<vector<SPNode>> _childs = make_shared<vector<SPNode>>();

	GLfloat _mvpMatrix[16]; // model view project
	GLfloat _transform[16];

	bool _revisit = true;
	bool _redraw = true;
};


