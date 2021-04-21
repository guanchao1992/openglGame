#pragma once
#include "Node.h"
#include <functional>

StatementNode(Button)
class Button :public Node
{
public: 
	static shared_ptr<Button> create(const char*title, const char*imgNormal, const char*imgSelect);

	void setCallBack(std::function<void()>func);
private:
	void init(const char*title, const char*imgNormal, const char*imgSelect);

private:
	string _title;
	string _imgNormal;
	string _imgSelect;
	
	GLint _textureNormalId;
	GLint _textureSelectId;

	std::function<void()> _funcCallBack = nullptr;
};

