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
	auto com = addComponent<DrawRanderComponent>();
	com->addVertex(Vector2(0.f, 0));
	com->addVertex(Vector2(40.f, 0));
	com->addVertex(Vector2(40.f, 40));
	com->addVertex(Vector2(0.f, 40));
	resetBoxType(BOX_1);
}

void DrawBoxNode::resetBoxType(BoxType bt) {
	_boxType = bt;
	switch (_boxType)
	{
	case BOX_NULL:
		setColor(0.f, 0.f, 0.f, 0);
		break;
	case BOX_1:
		setColor(0.8f, 0.f, 0.f, 1);
		break;
	case BOX_2:
		setColor(0.f, 0.8f, 0.f, 1);
		break;
	case BOX_3:
		setColor(0.f, 0.f, 0.8f, 1);
		break;
	case BOX_4:
		setColor(0.8f, 0.8f, 0.f, 1);
		break;
	default:
		break;
	}
}

void TxcBoxNode::init()
{
	//_shader = GameApp::getInstance()->getShader("texture");
	addComponent<AreaComponent>()->setSize(Size(40.f, 40));
	auto com = addComponent<TextureRanderComponent>();
	auto texture = TextureController::getInstance()->loadPng(".\\res\\test (1).png");
	com->setTextureID(texture->_textureId);
	resetBoxType(BOX_1);
}

void TxcBoxNode::resetBoxType(BoxType bt)
{
	//nothing
}
