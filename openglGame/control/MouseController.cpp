#include "MouseController.h"
#include "GameApp.h"

MouseController::~MouseController()
{
}

void MouseController::init()
{
	_listener = GameApp::getInstance()->createListenerSP();
	_listener->listen([this](const MouseKeyEvent& et) {
		sortAllComs();
		for (auto it : _mouseComs)
		{
			if (it->onMouseKeyEvent(et))
			{
				return;
			}
		}
		if (!et._isDown)
		{
			for (auto it : _mouseComs)
			{
				it->_isThisDown = false;
			}
		}
	});
	_listener->listen([this](const MouseMoveEvent& et) {
		sortAllComs();
		bool cutoff = false;
		for (auto it : _mouseComs)
		{
			if (cutoff)
			{
				it->doMouseOut(et);
			}
			else if (it->onMouseMoveEvent(et))
			{
				cutoff = true;
			}
		}
	});
}

void MouseController::addMouseComponent(MouseComponent* com)
{
	_mouseComs.push_back(com);
}

void MouseController::removeMouseComponent(MouseComponent* com)
{
	for (auto it = _mouseComs.begin(); it != _mouseComs.end(); it++)
	{
		if (*it == com)
		{
			_mouseComs.erase(it);
			break;
		}
	}
}

int compareOrder(Node*a, Node*b)
{
	if (!a || !b)
		return 0;
	if (a->getParent() == b->getParent())
	{
		if (a->getZOrder() != b->getZOrder())
		{
			return b->getZOrder() - a->getZOrder();
		}
		else
		{
			if (a->getParent())
			{
				for (auto it : a->getParent()->getChilds())
				{
					if (it.get() == a)
					{
						return 1;
					}
					else if (it.get() == b)
					{
						return -1;
					}
				}
			}
		}
	}
	auto temp_order_1 = compareOrder(a->getParent(), b);
	if (temp_order_1 != 0)
	{
		return temp_order_1;
	}
	auto temp_order_2 = compareOrder(a, b->getParent());
	if (temp_order_2 != 0)
	{
		return temp_order_2;
	}

	return 0;
}

void MouseController::sortAllComs()
{
	auto app = GameApp::getInstance();
	//_mouseKeyComs

	sort(_mouseComs.begin(), _mouseComs.end(), [this](MouseComponent* a, MouseComponent* b) {
		Node *nodeA = (Node*)a->getObject();
		Node *nodeB = (Node*)b->getObject();
		if (!nodeA || !nodeB)
			return false;
		return compareOrder(nodeA, nodeB) < 0;
	});
}
