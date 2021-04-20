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

const Size& AreaComponent::getSize()
{
	return _contentSize;
}

