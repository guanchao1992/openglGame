#include "DrawBoxNode.h"
#include "GameApp.h"
#include <control/TextureController.h>


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

void TxcBoxNode::init()
{
	_shader = GameApp::getInstance()->getShader("texture");
	addVertex(Vector2(0, 0), Vector2(0, 0));
	addVertex(Vector2(40, 0), Vector2(0, 1));
	addVertex(Vector2(40, 40), Vector2(1, 1));
	addVertex(Vector2(0, 40), Vector2(1, 0));
	auto texture = TextureController::getInstance()->loadPng("d:/pngtest3.png");
	setTextureID(texture->_textureId);
	resetBoxType(BOX_1);
}

void TxcBoxNode::resetBoxType(BoxType bt)
{
	//nothing
}
