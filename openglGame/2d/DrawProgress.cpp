#include "DrawProgress.h"
#include "GameApp.h"
#include <control/TextureController.h>
#include "component/DrawRanderComponent.h"
#include "component/TextureRanderComponent.h"
#include "component/AreaComponent.h"


void DrawProgress::init(const Vector4&barColor, const Vector4&bgColor, const Size&size)
{
	addComponent<AreaComponent>()->setSize(size);
	addComponent<DrawRanderComponent>();

	_barColor = barColor;
	_bgColor = bgColor;

	reDraw();
}

void DrawProgress::reDraw()
{
	auto size = getComponent<AreaComponent>()->getSize();
	auto com = getComponent<DrawRanderComponent>();
	com->clearAllVertex();
	com->addVertex(Vector2(0.f, 0), _bgColor);
	com->addVertex(Vector2(size._width, 0), _bgColor);
	com->addVertex(Vector2(size._width, size._height), _bgColor);
	com->addVertex(Vector2(0.f, size._height), _bgColor);
	com->signDraw(GL_TRIANGLE_FAN);

	com->addVertex(Vector2(0.f, 0), _barColor);
	com->addVertex(Vector2(size._width * _proportion, 0), _barColor);
	com->addVertex(Vector2(size._width * _proportion, size._height), _barColor);
	com->addVertex(Vector2(0.f, size._height), _barColor);
	com->signDraw(GL_TRIANGLE_FAN);
}

void DrawProgress::setProportion(float proportion)
{
	_proportion = proportion;
	if (_proportion < 0)
	{
		_proportion = 0;
	}
	else if (_proportion > 1)
	{
		_proportion = 1;
	}
	reDraw();
}
