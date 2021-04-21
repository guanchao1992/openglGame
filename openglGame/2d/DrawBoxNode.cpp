#include "DrawBoxNode.h"
#include "GameApp.h"
#include <control/TextureController.h>
#include "component/DrawRanderComponent.h"
#include "component/TextureRanderComponent.h"
#include "component/AreaComponent.h"


DrawBoxNode:: ~DrawBoxNode()
{

}

void DrawBoxNode::init()
{
//	_shader = GameApp::getInstance()->getShader("filldraw");
	auto com = addComponent<DrawRanderComponent>();
	com->addVertex(Vector2(0, 0));
	com->addVertex(Vector2(40, 0));
	com->addVertex(Vector2(40, 40));
	com->addVertex(Vector2(0, 40));
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
	//_shader = GameApp::getInstance()->getShader("texture");
	addComponent<AreaComponent>()->setSize(Size(40, 40));
	auto com = addComponent<TextureRanderComponent>();
	auto texture = TextureController::getInstance()->loadPng(".\\res\\test (1).png");
	com->setTextureID(texture->_textureId);
	resetBoxType(BOX_1);
}

void TxcBoxNode::resetBoxType(BoxType bt)
{
	//nothing
}
