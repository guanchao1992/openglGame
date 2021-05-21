#pragma once
#include "base/ControllerBase.hpp"
#include <vector>
#include <memory>
#include "dexode/eventbus/Bus.hpp"
#include <map>

using namespace std;

class KeyboardController : public ControllerBaseT<KeyboardController>
{
public:
	void init();
	void handlerKey(unsigned int key, bool down);
	bool isDownKey(unsigned int key);
private:
	map<unsigned int, bool> _keysDown;
};

