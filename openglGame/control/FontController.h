#pragma once

#include "base/ControllerBase.hpp"
#include<map>
#include <GL/glew.h>
#include "ft2build.h"
#include <freetype/freetype.h>
#include <string>


struct xCharTexture
{
	GLuint  _texID;
	wchar_t _chaID;
	int     _width;
	int     _height;
	int     _adv_x;
	int     _adv_y;
	int     _delta_x;
	int     _delta_y;
public:
	xCharTexture()
	{
		_texID = 0;
		_chaID = 0;
		_width = 0;
		_height = 0;
	}
};

class xFreeTypeLib
{
	FT_Library m_FT2Lib;
	FT_Face    m_FT_Face;

public:
	int   m_w;
	int   m_h;
	void load(const char* font_file, int _w, int _h);
	GLuint loadChar(wchar_t ch);
};

class Font
{
public:
	static shared_ptr<Font> create(const char*fontFile,int fontSize);
	void init();

	xCharTexture* getTextChar(wchar_t ch);

	string		_fontName;
	int			_fontSize = 20;
	FT_Face		_ftFace;
	static xFreeTypeLib _FreeTypeLib;

	//×ÖºÅ£¬ÐòºÅ£¬ÎÆÀí
	map<int, map<wchar_t, xCharTexture>>	_fcharTexs;
};

class FontController :public ControllerBaseT<FontController>
{
public:
	virtual void init();
	virtual void reset();
	shared_ptr<Font> loadFont(const char*fontFile);

private:
	FT_Library _library = nullptr;
	//shared_ptr<map<int, SPTimer>> _timers = make_shared<map<int, shared_ptr<Timer>>>();
	//int _nextIndex = 1;
	map<string, shared_ptr<Font>> _fonts;
};
