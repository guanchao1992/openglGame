#pragma once
#include <stdio.h>

#include "png.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>

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
/* Texture id for the demo */

gl_texture_t *ReadPNGFromFile(const char *filename);
GLuint loadPNGTexture(const char *filename);
void GetPNGtextureInfo(int color_type, gl_texture_t *texinfo);
unsigned int LoadTex(string Image);

GLuint CreateTextureFromPng(const char* filename);
