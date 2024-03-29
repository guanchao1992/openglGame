#pragma once

#include "Node.h"
#include "base/Vector3.h"

enum BoxType
{
	BOX_NULL = 0,
	BOX_1,
	BOX_2,
	BOX_3,
	BOX_4,
};

StatementNode(DrawBoxNode)
class DrawBoxNode :public Node
{
	StatementCreate(DrawBoxNode);
public:
	~DrawBoxNode();
	void init();
	void resetBoxType(BoxType bt);
	BoxType getBoxType() { return _boxType; }
private:
	BoxType _boxType;
};


StatementNode(TxcBoxNode)
class TxcBoxNode :public Node
{
	StatementCreate(TxcBoxNode);
public:
	void init();
	void resetBoxType(BoxType bt);
private:
};

