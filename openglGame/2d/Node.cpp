#include "Node.h"
#include "GameApp.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

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
	if (_revisit)
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

		//glusMatrix4x4Multiplyf(_mvTransform, parentTransform, selfMatrix);

		refreshTransformParent();

		glusMatrix4x4Multiplyf(_mvTransform, parentTransform, _transform);
	}

	this->draw(_mvTransform);

	for (auto it = _childs->begin(); it != _childs->end(); it++)
	{
		(*it)->visit(_mvTransform, parentFlag);
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

void Node::setAngle(float angle)
{
	this->setAngleCoordinate(_angleX, _angleY, _angleZ);
}

void Node::setAngleCoordinate(float angleX, float angleY, float angleZ)
{
	_angleX = angleX;
	_angleY = angleY;
	_angleZ = angleZ;

	_revisit = true;
	recodeDraw();
}

void Node::setRotateAxis(Vector3 vec, float angle)
{
	_rotateAxis = vec;
	_angleAxis = angle;

	_revisit = true;
	recodeDraw();
}

void Node::setScaleX(float scale)
{
	setScale(scale, _scaleY);
}

void Node::setScaleY(float scale)
{
	setScale(_scaleX, scale);
}

void Node::setScale(float scaleX, float scaleY)
{
	_scaleX = scaleX;
	_scaleY = scaleY;
	_revisit = true;
	recodeDraw();
}

void Node::setContentSize(const Size&size)
{
	_contentSize = size;
	_revisit = true;
	recodeDraw();
}

void Node::refreshTransformParent()
{
	glm::mat4 transformMat(1.0f);

	transformMat = glm::translate(transformMat, _position._x, _position._y, 0.0f);


	if (_angleZ != 0)
		transformMat = glm::rotate(transformMat, _angleZ, 0.f, 0.f, 1.f);
	if (_angleY != 0)
		transformMat = glm::rotate(transformMat, _angleY, 0.f, 1.f, 0.f);
	if (_angleX != 0)
		transformMat = glm::rotate(transformMat, _angleX, 1.f, 0.f, 0.f);
	if (_angleAxis != 0)
		transformMat = glm::rotate(transformMat, _angleAxis, _rotateAxis._x, _rotateAxis._y, _rotateAxis._z);

	if (_scaleX != 1.0f || _scaleY != 1.0f)
		transformMat = glm::scale(transformMat, _scaleX, _scaleY, 1.0f);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			auto index = i * 4 + j;
			_transform[index] = transformMat[i][j];
		}
	}
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
