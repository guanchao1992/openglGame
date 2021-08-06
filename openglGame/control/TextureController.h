#pragma once

#include "base/Singleton.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <memory>
#include "base/ControllerBase.hpp"
#include <string>

using namespace std;

class gl_texture_t {
public:
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLint internalFormat;
	GLuint id;
	GLubyte *texels;
};

struct Texture
{
	GLuint	_textureId;
	string	_filename;	//key  �����������������һ����ͼƬ
	GLenum	_target;
	GLsizei _width;		//ԭʼ�ߴ� ��
	GLsizei _height;	//ԭʼ�ߴ� ��
	GLenum	_format;	//��ʽ
};

typedef shared_ptr<Texture> SPTexture;

class TextureController :public ControllerBaseT<TextureController>
{
	//SingletonClase(TextureController);
public:
	SPTexture loadPng(const char*path);
private:
	shared_ptr<map<string, SPTexture>> _textures = make_shared<map<string, SPTexture>>();
	shared_ptr<map<GLuint, string>> _texture2s = make_shared<map<GLuint, string>>();	//�����������
};


