#include "KeyboardController.h"
#include "GameApp.h"
#include <GLUS/glus_window.h>


void KeyboardController::init()
{
}

void KeyboardController::handlerKey(unsigned int key, bool down)
{
	auto it = _keysDown.find(key);
	if (down)
	{
		if (it == _keysDown.end())
		{
			_keysDown.insert(std::pair<unsigned int, bool>(key, true));
			GameApp::getInstance()->getEventBus()->postpone(KeyEvent{ EVENT_KEY, key, true });
		}
		else
		{
			if (!it->second)
			{
				it->second = true;
				GameApp::getInstance()->getEventBus()->postpone(KeyEvent{ EVENT_KEY, key, true});
			}
		}
	}
	else
	{
		if (it == _keysDown.end())
		{
		}
		else
		{
			if (it->second)
			{
				it->second = false;
				GameApp::getInstance()->getEventBus()->postpone(KeyEvent{ EVENT_KEY, key, false});
			}
		}
	}
}

bool KeyboardController::isDownKey(unsigned int key)
{
	return _keysDown[key];
}
