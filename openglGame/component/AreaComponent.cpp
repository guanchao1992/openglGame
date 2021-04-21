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
