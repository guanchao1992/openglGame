#include "RouteComponent.h"
#include "2d/Node.h"
#include <GameApp.h>
#include "OutlineBoxComponent.h"


void RouteComponent::doBegin()
{
	__super::doBegin();
}

void RouteComponent::doEnd()
{
	__super::doEnd();
}

void RouteComponent::resetRoutes()
{
	for (size_t i = 0; i < 10; i++)
	{
		Vector2 v2(i / 10.0f, 0);
		_routes.push_back(v2);
	}
}

Vector2 RouteComponent::getRoutes(float t)
{
	int index = ((int)(t));
	int index1 = index % _routes.size();
	int index2 = (index1 + 1) % _routes.size();

	const Vector2& pos1 = _routes[index1];
	const Vector2& pos2 = _routes[index2];

	Vector2 pos((t - index) * (pos2._x - pos1._x) + pos1._x, (t - index) * (pos2._y - pos1._y) + pos1._y);

	return pos;
}
