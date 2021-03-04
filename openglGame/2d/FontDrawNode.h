#pragma once


#include <stdio.h>

#include "GameApp.h"

#include "GL/glus.h"

#include "ft2build.h"
#include "freetype/freetype.h"

#include "TextureNode.h"
#include <string>
#include <control/FontController.h>

#define DEFAULTE_FONT_FILE		"res/simhei.ttf"

StatementNode(FontDrawNode)
class FontDrawNode :public Node
{
	StatementCreateN1(FontDrawNode, const char*, fontFile)
public:
	~FontDrawNode();
	void init(const char*fontFile);

	virtual void randerOne();
	virtual void onDraw();

	void clearAllVertex();

public:
	static void initProgram();

	void setText(const wchar_t*str);
	void setFontSize(int fontSize);
private:

	GLuint _verticesVBO = -1;
	GLuint _verticesVAO = -1;
private:
	vector<Vector2> _vertexs;
	vector<GLuint> _textureIds;

	shared_ptr<Font> _font;
	wstring _text;

	//FT_Library _library;


	//FT_Face _face;
};
