#include "ActorTipsComponent.h"
#include <GameApp.h>
#include "Game2DFight/Actor.h"
#include "FontRanderComponent.h"
#include "AreaComponent.h"


void ActorTipsComponent::doBegin()
{
	__super::doBegin();
	Node* node = (Node*)_object;

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&ActorTipsComponent::update, this, std::placeholders::_1));
}

void ActorTipsComponent::doEnd()
{
	__super::doEnd();
	TimerController::getInstance()->killTimer(_timerId);

}

bool ActorTipsComponent::update(float time)
{
	if (!_active)
		return false;
	Actor*actor = (Actor*)_object;

	//_listTexts.pop_front();

	bool hasDel = false;
	for (auto it = _listTexts.begin(); it != _listTexts.end();)
	{
		auto nodetext = (*it);
		nodetext->setPosition(nodetext->getPosition() + Vector3(0, 150 * time, 0));
		if (nodetext->getPosition()._y > 100)
		{
			hasDel = true;
			nodetext->removeFromParent();
			it = _listTexts.erase(it);
		}
		else
		{
			it++;
		}
	}
	if (hasDel)
	{
	}
	return false;
}

void ActorTipsComponent::addTips(const wchar_t*text)
{
	auto nodetext = Text::create(text, DEFAULTE_FONT_FILE, 24);
	nodetext->setScale(0.6);
	nodetext->setPosition(-30, 0);
	nodetext->setColor(Vector4(0.1, 0.1, 0.1, 1));
	auto areaCom = nodetext->getComponent<AreaComponent>();
	areaCom->setAnchor(Vector2(1, 0));

	auto actor = (Actor*)_object;
	actor->addChild(nodetext);

	_listTexts.push_back(nodetext);
}
