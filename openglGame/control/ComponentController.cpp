#include "ComponentController.hpp"
#include "GameApp.h"
#include <GLUS/glus_window.h>
#include "TimerController.h"
#include <functional>

ComponentController::~ComponentController()
{ }

void ComponentController::init()
{
}

void ComponentController::update(float time)
{
	_del_components_map.clear();
}
