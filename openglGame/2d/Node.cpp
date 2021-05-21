#include "Node.h"
#include "GameApp.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <algorithm>
#include "control/TimerController.h"
#include "component/RanderComponent.h"

Node::~Node()
{
	_childs.clear();
	_visitLeft.clear();
	_visitRight.clear();
	_parent = nullptr;
	killAllTimer();
}

void Node::reshape()
{
	for (auto it = _childs.begin(); it != _childs.end(); it++)
	{
		(*it)->reshape();
	}
	_revisit = true;
	if (_randerComponent)
	{
		_randerComponent->reDraw();
	}
}

void Node::rander()
{
	if (!_visible)
	{
		return;
	}
	for (auto it = _visitLeft.begin(); it != _visitLeft.end(); it++)
	{
		(*it)->rander();
	}
	
	if (_randerComponent)
	{
		_randerComponent->rander();
		_randerComponent->randerOutLine();
	}
	for (auto it = _visitRight.begin(); it != _visitRight.end(); it++)
	{
		(*it)->rander();
	}
}

void Node::visit(const GLfloat *parentTransform, GLboolean parentFlag)
{
	if (!_visible)
	{
		return;
	}
	if (_revisit || parentFlag)
	{
		parentFlag = true;
		_revisit = false;

		refreshTransformParent();

		glusMatrix4x4Multiplyf(_projectTransform, parentTransform, _transform);
	}
	if (_reorder)
	{
		_reorder = false;
		refreshOrder();
	}
	if (_randerComponent)
	{
		_randerComponent->draw();
	}
	for (auto it = _childs.begin(); it != _childs.end(); it++)
	{
		(*it)->visit(_projectTransform, parentFlag);
	}
}

void Node::addChild(SPNode node, int zOrder)
{
	node->_parent = this;
	node->_localZOrder = zOrder;
	_childs.push_back(node);

	_reorder = true;
}

void Node::removeAllChild()
{
	_childs.clear();
	_visitLeft.clear();
	_visitRight.clear();
	_reorder = true;
}

void Node::removeFromParent()
{
	assert(_parent, "That node havent parent.");

	this->removeAllComponent();
	for (auto it = _parent->_visitLeft.begin(); it != _parent->_visitLeft.end(); it++)
	{
		if (*it == this)
		{
			_parent->_visitLeft.erase(it);
			break;
		}
	}
	for (auto it = _parent->_visitRight.begin(); it != _parent->_visitRight.end(); it++)
	{
		if (*it == this)
		{
			_parent->_visitRight.erase(it);
			break;
		}
	}
	for (auto it = _parent->_childs.begin(); it != _parent->_childs.end(); it++)
	{
		if ((*it).get() == this)
		{
			_parent->_childs.erase(it);
			return;
		}
	}
}

const vector<SPNode>& Node::getChilds()
{
	return _childs;
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
}

void Node::setPosition(const Vector3&pos)
{
	setPosition(pos._x, pos._y, pos._z);
}

void Node::setPosition(float x, float y, float z)
{
	_position._x = x;
	_position._y = y;
	_position._z = z;
	_revisit = true;
}


void Node::setEulerAngle(float angleZ)
{
	this->setAngleCoordinate(_angleX, _angleY, angleZ / PI * 180);
}

void Node::setAngle(float angle)
{
	this->setAngleCoordinate(_angleX, _angleY, angle);
}

void Node::setAngleCoordinate(float angleX, float angleY, float angleZ)
{
	_angleX = angleX;
	_angleY = angleY;
	_angleZ = angleZ;

	_revisit = true;
}

void Node::setRotateAxis(Vector3 vec, float angle)
{
	_rotateAxis = vec;
	_angleAxis = angle;

	_revisit = true;
}

void Node::setScaleX(float scale)
{
	setScale(scale, _scaleY, _scaleZ);
}

void Node::setScaleY(float scale)
{
	setScale(_scaleX, scale, _scaleZ);
}

void Node::setScale(float scaleX, float scaleY, float scaleZ)
{
	_scaleX = scaleX;
	_scaleY = scaleY;
	_scaleZ = scaleZ;

	_revisit = true;
}

void Node::setScale(float scale)
{
	_scaleX = scale;
	_scaleY = scale;
	_scaleZ = scale;

	_revisit = true;
}

void Node::refreshTransformParent()
{
	glm::mat4 transformMat(1.0f);

	transformMat = glm::translate(transformMat, _position._x, _position._y, _position._z);

	if (_angleZ != 0)
		transformMat = glm::rotate(transformMat, _angleZ, 0.f, 0.f, 1.f);
	if (_angleY != 0)
		transformMat = glm::rotate(transformMat, _angleY, 0.f, 1.f, 0.f);
	if (_angleX != 0)
		transformMat = glm::rotate(transformMat, _angleX, 1.f, 0.f, 0.f);
	if (_angleAxis != 0)
		transformMat = glm::rotate(transformMat, _angleAxis, _rotateAxis._x, _rotateAxis._y, _rotateAxis._z);

	if (_scaleX != 1.0f || _scaleY != 1.0f || _scaleZ != 1.0f)
		transformMat = glm::scale(transformMat, _scaleX, _scaleY, _scaleZ);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			auto index = i * 4 + j;
			_transform[index] = transformMat[i][j];
		}
	}
}

GLfloat* Node::getTransformParent()
{
	refreshTransformParent();
	return _transform;
}

void Node::setColor(const Vector4&color)
{
	_color = color;
}

void Node::setColor(float r, float g, float b, float l)
{
	_color.setVector(r, g, b, l);
}

void Node::setZOrder(int localZOrder)
{
	if (_localZOrder == localZOrder)
		return;
	_localZOrder = localZOrder;
	if (_parent != nullptr)
	{
		_parent->_reorder = true;
	}
}

void Node::refreshOrder()
{
	_visitLeft.clear();
	_visitRight.clear();

	for (auto it = _childs.begin(); it != _childs.end(); it++)
	{
		if ((*it)->getZOrder() < 0)
		{
			_visitLeft.push_back(it->get());
		}
		else
		{
			_visitRight.push_back(it->get());
		}
	}
	/*
	sort(_visitLeft.begin(), _visitLeft.end(), [](SPNode a, SPNode b) {
		return a->getZOrder() < b->getZOrder();
	});
	sort(_visitRight.begin(), _visitRight.end(), [](SPNode a, SPNode b) {
		return a->getZOrder() < b->getZOrder();
	});
	*/
	_visitLeft.sort();
}

void Node::setTag(int tag)
{
	_tag = tag;
}

SPNode Node::getChildByTag(int tag)
{
	for (auto it = _childs.begin(); it != _childs.end(); it++)
	{
		if ((*it)->getTag() == tag)
		{
			return(*it);
		}
	}
	return nullptr;
}

int Node::addTimer(float interval, int num, TimerCallback callback)
{
	//_timerids =
	int timerId = TimerController::getInstance()->addTimer(interval, num, callback);
	_timerids.push_back(timerId);
	return timerId;
}

void Node::killTimer(int timerId)
{
	for (auto it = _timerids.begin(); it != _timerids.end(); it++)
	{
		if ((*it) == timerId)
		{
			_timerids.erase(it);
			TimerController::getInstance()->killTimer(timerId);
			break;
		}
	}
}

void Node::killAllTimer()
{
	for (auto it = _timerids.begin(); it != _timerids.end(); it++)
	{
		TimerController::getInstance()->killTimer(*it);
	}
	_timerids.clear();
}

void Node::setVisible(bool visible)
{
	_visible = false;
}

int Node::getAllChildNum()
{
	auto size = 1;
	for (auto it = _childs.begin(); it != _childs.end(); it++)
	{
		size += (*it)->getAllChildNum();
	}
	return size;
}

void Node::setRanderComponent(RanderComponent* com)
{
	_randerComponent = com;
}

