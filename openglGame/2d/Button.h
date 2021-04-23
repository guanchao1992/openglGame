#pragma once
#include "Node.h"
#include <functional>
#include "Text.h"

StatementNode(Button)
class Button :public Node
{
public:
	~Button();
public: 
	static shared_ptr<Button> create(const char*imgNormal, const char*imgSelect);

	void setCallBack(std::function<void()>func);
private:
	void init(const char*imgNormal, const char*imgSelect);

public:
	void setContentSize(const Size&size);
	void setTitle(const string&str, const char*font, int fontSize);
	void setTitle(const wstring&str, const char*font, int fontSize);

private:
	SPText _title;
	string _imgNormal;
	string _imgSelect;
	
	GLint _textureNormalId;
	GLint _textureSelectId;

};

