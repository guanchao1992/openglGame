#include "Node.h"
#include "GameApp.h"


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
	recodeDraw();

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

void Node::visit(const GLfloat *parentTransform, GLboolean parentFlag)
{
	if (_revisit || true)
	{
		parentFlag = true;
		_revisit = false;
		_redraw = true;
		GLfloat selfMatrix[16] =
		{
			1.0f ,0.0f ,0.0f,0.0f,
			0.0f ,1.0f ,0.0f,0.0f,
			0.0f ,0.0f ,1.0f,0.0f,
			getPosition()._x ,getPosition()._y ,0.0f,1.0f,
		};

		glusMatrix4x4Multiplyf(_transform, parentTransform, selfMatrix);
	}


	this->draw(parentTransform);

	for (auto it = _childs->begin(); it != _childs->end(); it++)
	{
		(*it)->visit(_transform, parentFlag);
	}
}

//如果发生了更改，需要重新
void Node::draw(const GLfloat *parentTransform)
{
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

vector<SPNode> Node::getChilds()
{
	return *_childs;
}


void Node::setPosition(const Vector2&pos)
{
	setPosition(pos._x, pos._y);
}

void Node::setPosition(float x, float y)
{
	_position._x = x;
	_position._y = y;
	_revisit = true;
	recodeDraw();
}

void Node::setContentSize(const Size&size)
{
	_contentSize = size;
	_revisit = true;
	recodeDraw();
}

void Node::setColor(const Vector4&color)
{
	_color = color;
	recodeDraw();
}

void Node::setColor(float r, float g, float b, float l)
{
	_color.setVector(r, g, b, l);
	recodeDraw();
}

void Node::recodeDraw()
{
	if (_redraw)
	{
		return;
	}
	_redraw = true;
	for (auto it = _childs->begin(); it != _childs->end(); it++)
	{
		(*it)->recodeDraw();
	}
}
