#include "DrawBoxNode.h"
#include "GameApp.h"


DrawBoxNode:: ~DrawBoxNode()
{

}

void DrawBoxNode::init()
{
	_shader = GameApp::getInstance()->getShader("filldraw");
	addVertex(Vector2(0, 0));
	addVertex(Vector2(40, 0));
	addVertex(Vector2(40, 40));
	addVertex(Vector2(0, 40));
	enforceVertex();
	resetBoxType(BOX_1);
}

void DrawBoxNode::resetBoxType(BoxType bt) {
	_boxType = bt;
	switch (_boxType)
	{
	case BOX_NULL:
		setColor(0, 0, 0, 0);
		break;
	case BOX_1:
		setColor(0.8, 0, 0, 1);
		break;
	case BOX_2:
		setColor(0, 0.8, 0, 1);
		break;
	case BOX_3:
		setColor(0, 0, 0.8, 1);
		break;
	case BOX_4:
		setColor(0.8, 0.8, 0, 1);
		break;
	default:
		break;
	}
}