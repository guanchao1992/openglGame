#include "FontController.h"
#include <assert.h>
#include <freetype/ftglyph.h>


static xFreeTypeLib g_FreeTypeLib;

shared_ptr<Font> Font::create(const char*fontFile, int fontSize)
{
	shared_ptr<Font> font = make_shared<Font>();
	font->_fontName = fontFile;
	font->_fontSize = fontSize;
	font->init();
	return font;
}

void Font::init()
{
}

xCharTexture* Font::getTextChar(wchar_t ch)
{
	auto &charTexs = _fcharTexs[_fontSize];

	auto it = charTexs.find(ch);
	if (it != charTexs.end())
	{
		return &charTexs[ch];
	}

	FT_Set_Pixel_Sizes(_ftFace, _fontSize, _fontSize);

	/* 装载字形图像到字形槽（将会抹掉先前的字形图像） */
	if (FT_Load_Char(_ftFace, ch, /*FT_LOAD_RENDER|*/FT_LOAD_FORCE_AUTOHINT |
		(true ? FT_LOAD_TARGET_NORMAL : FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO)))
	{
		return nullptr;
	}

	xCharTexture& charTex = charTexs[ch];

	//得到字模
	FT_Glyph glyph;
	//把字形图像从字形槽复制到新的FT_Glyph对象glyph中。这个函数返回一个错误码并且设置glyph。 
	if (FT_Get_Glyph(_ftFace->glyph, &glyph))
		return nullptr;

	//转化成位图
	FT_Render_Glyph(_ftFace->glyph, FT_RENDER_MODE_LCD);//FT_RENDER_MODE_NORMAL  ); 
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	//取道位图数据
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	//把位图数据拷贝自己定义的数据区里.这样旧可以画到需要的东西上面了。
	int width = bitmap.width;
	int height = bitmap.rows;

	_ftFace->size->metrics.y_ppem;		//伸缩距离到设备空间
	_ftFace->glyph->metrics.horiAdvance;  //水平文本排列

	charTex._width = width;
	charTex._height = height;
	charTex._adv_x = _ftFace->glyph->advance.x / 64.0f;  //步进宽度
	charTex._adv_y = _ftFace->size->metrics.y_ppem;		//m_FT_Face->glyph->metrics.horiBearingY / 64.0f;
	charTex._delta_x = (float)bitmap_glyph->left;			//left:字形原点(0,0)到字形位图最左边象素的水平距离.它以整数象素的形式表示。 
	charTex._delta_y = (float)bitmap_glyph->top - height;	//Top: 类似于字形槽的bitmap_top字段。
	glGenTextures(1, &charTex._texID);
	glBindTexture(GL_TEXTURE_2D, charTex._texID);
	char* pBuf = new char[width * height * 4];
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			unsigned char _vl = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];
			pBuf[(4 * i + (height - j - 1) * width * 4)] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 1] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 2] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 3] = _vl;
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);  //指定一个二维的纹理图片
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);							   //glTexParameteri():纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);								//纹理进行混合

	delete[] pBuf;
	return &charTex;
}

void FontController::init()
{
	if (FT_Init_FreeType(&_library))
	{
		assert(false, "初始化FreeType失败了");
	}
}


void FontController::reset()
{
}

shared_ptr<Font> FontController::loadFont(const char*fontFile)
{
	//FT_Face    m_FT_Face;
	auto it = _fonts.find(fontFile);
	if (it != _fonts.end())
	{
		return it->second;
	}
	auto font = Font::create(fontFile, 20);
	_fonts[fontFile] = font;
	//加载一个字体,取默认的Face,一般为Regualer
	if (FT_New_Face(_library, fontFile, 0, &font->_ftFace))
	{
		assert(false, "加载字体失败");
	}
	//选择字符表
	FT_Select_Charmap(font->_ftFace, FT_ENCODING_UNICODE);
	return font;
}

