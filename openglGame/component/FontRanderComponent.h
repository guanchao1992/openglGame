#pragma once
#include "RanderComponent.h"
#include <vector>
#include "Base/Vector2.h"

#define DEFAULTE_FONT_FILE		"res/simhei.ttf"

using namespace std;
class Font;

class FontRanderComponent : public RanderComponent
{

public:
	FontRanderComponent();
	virtual const char* getName() { return "FontRanderComponent"; }

	virtual void doBegin();
	virtual void doEnd();
	virtual void update();

	virtual void rander();
	virtual void draw();

public:
	void clearAllVertex();
	void setText(const std::string&str);
	void setText(const std::wstring&wstr);
	void setText(const wchar_t*str);
	void setFontSize(int fontSize);
	void setFont(const string& fontFile);
	void setMaxWidth(unsigned int maxWidth);

	void layout();

private:
	int _vertexLocation;
	int _textCoordLocation;
	int _texture0Location;
	int _makeColorLocation;

private:
	vector<Vector2> _vertexs;
	vector<GLuint> _textureIds;

	shared_ptr<Font> _font;
	wstring _text;
	int _fontSize = 20;
	unsigned int _maxWidth = -1;
};

