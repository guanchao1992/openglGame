#include "Button.h"
#include "component/AreaComponent.h"
#include "component/TextureRanderComponent.h"
#include "control/TextureController.h"
#include "GameEvent.h"
#include "component/MouseComponent.h"

Button::~Button()
{

}

shared_ptr<Button> Button::create(const char*imgNormal, const char*imgSelect)
{
	shared_ptr<Button> node = make_shared<Button>();
	node->init(imgNormal, imgSelect);
	return node;
}

void Button::init(const char*imgNormal, const char*imgSelect)
{
	_imgNormal = imgNormal;
	_imgSelect = imgSelect;

	auto normalTexture = TextureController::getInstance()->loadPng(imgNormal);
	_textureNormalId = normalTexture->_textureId;

	auto selectTexture = TextureController::getInstance()->loadPng(imgSelect);
	_textureSelectId = selectTexture->_textureId;

	auto areaCom = addComponent<AreaComponent>();
	areaCom->setSize(Size(normalTexture->_width, normalTexture->_height));
	areaCom->setAnchor(Vector2(0.5, 0.5));
	auto textureCom = addComponent<TextureRanderComponent>();

	textureCom->setTextureID(_textureNormalId);

	auto mouseCom = addComponent<MouseComponent>();
	mouseCom->setMouseKeyFunc([&](MouseComponent&com, const MouseKeyEvent&et) {
		if (et._isDown)
		{
			setScale(1.1);
		}
		else
		{
			setScale(1.0);
		}
	});
	mouseCom->setMouseMoveInFunc([&](MouseComponent&com, const MouseMoveEvent&et) {
		getComponent<TextureRanderComponent>()->setTextureID(_textureSelectId);
		if (com.isThisDown() && (et._buttons & 1))
		{
			setScale(1.1);
		}
		else
		{
			setScale(1.0);
		}
	});
	mouseCom->setMouseMoveOutFunc([&](MouseComponent&com, const MouseMoveEvent&et) {
		getComponent<TextureRanderComponent>()->setTextureID(_textureNormalId);
		setScale(1.0);
	});
}

void Button::setCallBack(std::function<void()>func)
{
	getComponent<MouseComponent>()->setMouseClickFunc(func);
}

void Button::setContentSize(const Size&size)
{
	auto areaCom = getComponent<AreaComponent>();
	areaCom->setSize(size);
}

void Button::setTitle(const string&str, const char*font, int fontSize)
{
	if (_title == nullptr)
	{
		_title = Text::create(str, font, fontSize);
		addChild(_title);
		_title->getComponent<AreaComponent>()->setAnchor(Vector2(0.5, 0.5));
	}
	else
	{
		_title->setString(str);
	}
}

void Button::setTitle(const wstring&str, const char*font, int fontSize)
{
	if (_title == nullptr)
	{
		_title = Text::create(str, font, fontSize);
		addChild(_title, 10);
		_title->getComponent<AreaComponent>()->setAnchor(Vector2(0.5, 0.5));
	}
	else
	{
		_title->setString(str);
	}
}
