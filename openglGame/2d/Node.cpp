#include "Node.h"


SPNode Node::create()
{
	SPNode node = make_shared<Node>();
	node->record(node);
	return node;
}

void Node::record(SPNode selfNode)
{
	_this = selfNode;
}

void Node::reshape()
{
	for (auto it = _childs->begin(); it != _childs->end(); it++)
	{
		(*it)->reshape();
	}
	_redraw = true;

	//do something
}

void Node::rander()
{
	for (auto it = _childs->begin(); it != _childs->end(); it++)
	{
		(*it)->rander();
	}

	//do something
}

//如果发生了更改，需要重新
void Node::draw()
{
	for (auto it = _childs->begin(); it != _childs->end(); it++)
	{
		(*it)->draw();
	}
	//do something
}

void Node::addChild(SPNode node)
{
	node->_parent = this->_this;
	_childs->push_back(node);
}

void Node::removeChild(SPNode node)
{
	for (auto it = _childs->begin(); it != _childs->end(); it++)
	{
		if (*it == node)
		{
			node->_parent = nullptr;
			_childs->erase(it);
			break;
		}
	}
}

void Node::removeFromParent()
{
	this->_parent->removeChild(this->_this);
}


void Node::setPosition(const Vector2&pos)
{
	_position = pos;
	_redraw = true;
}

void Node::setPosition(float x, float y)
{
	_position._x = x;
	_position._y = y;
	_redraw = true;
}

void Node::setContentSize(const Size&size)
{
	_contentSize = size;
	_redraw = true;
}

void Node::setColor(const Vector4&color)
{
	_color = color;
	_redraw = true;
}
