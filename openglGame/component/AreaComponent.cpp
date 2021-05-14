#include "AreaComponent.h"
#include "2d/Node.h"
#include <GameApp.h>
#include "OutlineBoxComponent.h"


void AreaComponent::doBegin()
{
	__super::doBegin();
}

void AreaComponent::doEnd()
{
	__super::doEnd();
}

void AreaComponent::setSize(const Size&size)
{
	_contentSize = size;

	auto outlineBoxCom = _object->getComponent<OutlineBoxComponent>();
	if (outlineBoxCom)
	{
		outlineBoxCom->reDraw();
	}
}

void AreaComponent::setAnchor(const Vector2&anchor)
{
	_anchor = anchor;
	auto randerCom = dynamic_pointer_cast<RanderComponent>(getComponent(COMPONENT_RANDER));
	if (randerCom)
	{
		randerCom->reDraw();
	}
	auto outlineCom = dynamic_pointer_cast<RanderComponent>(getComponent(COMPONENT_OUTLINE));
	if (outlineCom)
	{
		outlineCom->reDraw();
	}
}

bool AreaComponent::isPosInArea(const Vector2& pos)
{
	Vector2 temp_pos(pos._x + _anchor._x * _contentSize._width, pos._y + _anchor._y * _contentSize._height);
	if (temp_pos._x<0 || temp_pos._x>_contentSize._width || temp_pos._y<0 || temp_pos._y>_contentSize._height)
	{
		return false;
	}
	return true;
}


const Rect& AreaComponent::getAreaRect(bool isNew)
{
	//²âÊÔµÄ£¬²»¹æ·¶
	if (isNew)
	{
		_rectLast = _rect;
		auto node = (Node*)getObject();

		_rect._left = node->getPosition()._x - _anchor._x * _contentSize._width;
		_rect._bottom = node->getPosition()._y - _anchor._y * _contentSize._height;
		_rect._right = _rect._left + _contentSize._width;
		_rect._top = _rect._bottom + _contentSize._height;
	}
	return _rect;
}

const Rect& AreaComponent::getAreaRectLast()
{
	return _rectLast;
}
