#pragma once
#include "Node.h"
#include <functional>

StatementNode(Text)
class Text :public Node
{
public: 
	Text();
	/*
	str 显示的字符串
	font 字体文件路径
	fontSize 字体大小
	*/
	static shared_ptr<Text> create(const string&str, const char*font, int fontSize);
	static shared_ptr<Text> create(const wstring&str, const char*font, int fontSize);
private:
	void init(const string&str, const char*font, int fontSize);
	void init(const wstring&str, const char*font, int fontSize);
public:
	void setFont(const char*font);
	void setString(const string&str);
	//如果要在代码中包含中文文字字符串，必须用宽的
	void setString(const wstring&str);
	void setFontSize(int fontSize);
	void setMaxWidth(int maxWidth);

	void layout();
private:
};

