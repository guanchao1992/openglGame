#pragma once
#include "Node.h"
#include <functional>

StatementNode(Text)
class Text :public Node
{
public: 
	Text();
	/*
	str ��ʾ���ַ���
	font �����ļ�·��
	fontSize �����С
	*/
	static shared_ptr<Text> create(const string&str, const char*font, int fontSize);
	static shared_ptr<Text> create(const wstring&str, const char*font, int fontSize);
private:
	void init(const string&str, const char*font, int fontSize);
	void init(const wstring&str, const char*font, int fontSize);
public:
	void setFont(const char*font);
	void setString(const string&str);
	//���Ҫ�ڴ����а������������ַ����������ÿ��
	void setString(const wstring&str);
	void setFontSize(int fontSize);
	void setMaxWidth(int maxWidth);

	void layout();
private:
};

