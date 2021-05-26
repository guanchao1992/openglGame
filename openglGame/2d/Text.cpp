#include "Text.h"
#include "component/AreaComponent.h"
#include "component/TextureRanderComponent.h"
#include "control/TextureController.h"
#include "GameEvent.h"
#include "component/MouseComponent.h"
#include "component/FontRanderComponent.h"

Text::Text()
{
	_color.setVector(1, 1, 1, 1);
}

//DEFAULTE_FONT_FILE
shared_ptr<Text> Text::create(const string&str, const char*font, int fontSize)
{
	shared_ptr<Text> node = make_shared<Text>();
	node->init(str, font, fontSize);
	return node;
}

shared_ptr<Text> Text::create(const wstring&str, const char*font, int fontSize)
{

	shared_ptr<Text> node = make_shared<Text>();
	node->init(str, font, fontSize);
	return node;
}

void Text::init(const string&str, const char*font, int fontSize)
{
	auto areaCom = addComponent<AreaComponent>();
	auto randerCom = addComponent<FontRanderComponent>();

	randerCom->setFont(font);
	randerCom->setText(str);
	randerCom->setFontSize(fontSize);
}

void Text::init(const wstring&str, const char*font, int fontSize)
{
	auto areaCom = addComponent<AreaComponent>();
	auto randerCom = addComponent<FontRanderComponent>();

	randerCom->setFont(font);
	randerCom->setText(str);
	randerCom->setFontSize(fontSize);
}

void Text::setFont(const char*font)
{
	auto randerCom = getComponent<FontRanderComponent>();
	randerCom->setFont(font);

	randerCom->reDraw();
}

void Text::setString(const string&str)
{
	auto randerCom = getComponent<FontRanderComponent>();
	randerCom->setText(str);

	randerCom->reDraw();
}

void Text::setString(const wstring&str)
{
	auto randerCom = getComponent<FontRanderComponent>();
	randerCom->setText(str);

	randerCom->reDraw();
}

void Text::setFontSize(int fontSize)
{
	auto randerCom = getComponent<FontRanderComponent>();
	randerCom->setFontSize(fontSize);

	randerCom->reDraw();
}

void Text::setMaxWidth(int maxWidth)
{
	auto randerCom = getComponent<FontRanderComponent>();
	randerCom->setMaxWidth(maxWidth);

	randerCom->reDraw();
}

void Text::layout()
{
	auto fontRanderCom = getComponent<FontRanderComponent>();
}
