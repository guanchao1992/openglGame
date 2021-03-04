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

	/* װ������ͼ�����βۣ�����Ĩ����ǰ������ͼ�� */
	if (FT_Load_Char(_ftFace, ch, /*FT_LOAD_RENDER|*/FT_LOAD_FORCE_AUTOHINT |
		(true ? FT_LOAD_TARGET_NORMAL : FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO)))
	{
		return nullptr;
	}

	xCharTexture& charTex = charTexs[ch];

	//�õ���ģ
	FT_Glyph glyph;
	//������ͼ������β۸��Ƶ��µ�FT_Glyph����glyph�С������������һ�������벢������glyph�� 
	if (FT_Get_Glyph(_ftFace->glyph, &glyph))
		return nullptr;

	//ת����λͼ
	FT_Render_Glyph(_ftFace->glyph, FT_RENDER_MODE_LCD);//FT_RENDER_MODE_NORMAL  ); 
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	//ȡ��λͼ����
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	//��λͼ���ݿ����Լ��������������.�����ɿ��Ի�����Ҫ�Ķ��������ˡ�
	int width = bitmap.width;
	int height = bitmap.rows;

	_ftFace->size->metrics.y_ppem;		//�������뵽�豸�ռ�
	_ftFace->glyph->metrics.horiAdvance;  //ˮƽ�ı�����

	charTex._width = width;
	charTex._height = height;
	charTex._adv_x = _ftFace->glyph->advance.x / 64.0f;  //�������
	charTex._adv_y = _ftFace->size->metrics.y_ppem;		//m_FT_Face->glyph->metrics.horiBearingY / 64.0f;
	charTex._delta_x = (float)bitmap_glyph->left;			//left:����ԭ��(0,0)������λͼ��������ص�ˮƽ����.�����������ص���ʽ��ʾ�� 
	charTex._delta_y = (float)bitmap_glyph->top - height;	//Top: ���������β۵�bitmap_top�ֶΡ�
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);  //ָ��һ����ά������ͼƬ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);							   //glTexParameteri():�������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);								//������л��

	delete[] pBuf;
	return &charTex;
}

void FontController::init()
{
	if (FT_Init_FreeType(&_library))
	{
		assert(false, "��ʼ��FreeTypeʧ����");
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
	//����һ������,ȡĬ�ϵ�Face,һ��ΪRegualer
	if (FT_New_Face(_library, fontFile, 0, &font->_ftFace))
	{
		assert(false, "��������ʧ��");
	}
	//ѡ���ַ���
	FT_Select_Charmap(font->_ftFace, FT_ENCODING_UNICODE);
	return font;
}

