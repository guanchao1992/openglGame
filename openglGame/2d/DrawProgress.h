#pragma once

#include "Node.h"
#include "base/Vector3.h"
#include "Base/Vector4.h"


class DrawProgress;

StatementNode(DrawProgress)
//简单的进度条
class DrawProgress :public Node
{
public:
	static shared_ptr<DrawProgress> create(const Vector4&barColor, const Vector4&bgColor, const Size&size)
	{
		shared_ptr<DrawProgress> node = make_shared<DrawProgress>(); 
		node->init(barColor, bgColor, size);
		return node;
	}
public:
	void init(const Vector4&barColor, const Vector4&bgColor, const Size&size);
	void reDraw();
	void setProportion(float proportion);
private:

	Vector4 _barColor;
	Vector4 _bgColor;
	float _proportion = 1;	//0~1
};

