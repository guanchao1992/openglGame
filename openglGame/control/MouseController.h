#pragma once
#include "base/ControllerBase.hpp"
#include "component/MouseComponent.h"
#include <vector>
#include <memory>

using namespace std;

class MouseController : public ControllerBaseT<MouseController>
{
public:
	void init();
	void addMouseComponent(MouseComponent* com);
	void removeMouseComponent(MouseComponent* com);
	void sortAllComs();
private:
	shared_ptr<vector<MouseComponent*>> _mouseComs = make_shared<vector<MouseComponent*>>();

	shared_ptr<dexode::eventbus::Listener< dexode::eventbus::Bus>> _listener = nullptr;
};

