#pragma once

#include <memory>
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "Base/Vector3.h"
#include <vector>
#include "Shader.h"
#include "Base/Vector4.h"

using namespace std;


#define	StatementNode(ClassType);	class ClassType;typedef shared_ptr<ClassType> SP##ClassType;

StatementNode(Node)
class Node
{
protected:
	//
	//Node() {};
	//~Node() {};
public:
	static SPNode create();
public:
	virtual void init(SPNode selfNode);
	virtual void reshape();
	virtual void rander();
	virtual void draw();
	GLint getProgram() { return _shader->getProgram(); };

	void addChild(SPNode node);
	void removeFromParent();
	void removeChild(SPNode node);
	void setPosition(const Vector2&pos);
	void setContentSize(const Size&size);
	void setColor(const Vector4&color);

	const Vector4& getColor() { return _color; }
	const Vector2& getPosition() { return _position; }
	const Size& getContentSize() { return _contentSize; }
	SPNode getParent() { return _parent; }
protected:
	SPShader _shader;
	Size _contentSize;
	Vector2 _position;
	Vector4 _color;
	SPNode _parent;
	SPNode _this;		//引用计数自增，控制清空内存的时机

	shared_ptr<vector<SPNode>> _childs = make_shared<vector<SPNode>>();

	bool _redraw = true;
};


