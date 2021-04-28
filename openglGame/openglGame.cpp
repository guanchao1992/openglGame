﻿/**
 * OpenGL 3 - Example 02
 *
 * @author	Norbert Nopper norbert@nopper.tv
 *
 * Homepage: http://nopper.tv
 *
 * Copyright Norbert Nopper
 */

#include <stdio.h>

#include "GameApp.h"

#include "GL/glus.h"

#include "ft2build.h"
#include "freetype/freetype.h"
#include <nlohmann/json.hpp>
#include <iostream> 
#include <fstream> 
#include "control/KeyboardController.h"

FT_Library g_library;
FT_Error error;
FT_Face g_face;

GLuint g_ftx;
GLUSboolean init(GLUSvoid)
{
	auto app = GameApp::getInstance();
	app->init();

	// Basic blending equation.
	glEnable(GL_BLEND);

	//glClearDepth(1.0f);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	app->visit();

	/*
	auto error = FT_Init_FreeType(&g_library);					
	error = FT_New_Face(g_library, "res/simhei.ttf", 0, &g_face);		
	error = FT_Select_Charmap(g_face, FT_ENCODING_UNICODE);

	error = FT_Set_Char_Size(g_face, 50 * 64, 0, 100, 0); 
	FT_Set_Pixel_Sizes(g_face, 24, 0);

	FT_Load_Char(g_face, 880, FT_LOAD_RENDER);


	FT_GlyphSlot glyphSlot = g_face->glyph;

	glGenTextures(1, &g_ftx);    // Using your API here
	glBindTexture(GL_TEXTURE_2D, g_ftx);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Setup some parameters for texture filters and mipmapping 

	GLint alignment;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLint fmt = GL_RED;
	glTexImage2D(GL_TEXTURE_2D, 0, fmt, glyphSlot->bitmap.width, glyphSlot->bitmap.rows,
		0, fmt, GL_UNSIGNED_BYTE, glyphSlot->bitmap.buffer);
	//glTexSubImage2D(,)
	glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
	*/

	return GLUS_TRUE;
}

static int redisplay_interval;

GLUSvoid reshape(GLUSint width, GLUSint height)
{
	auto app = GameApp::getInstance();
	app->reshape();
	app->setViewSize(width, height);
	glViewport(0, 0, width, height);
}

GLUSboolean update(GLUSfloat time)
{
	auto app = GameApp::getInstance();
	app->update(time);
	if (app->isReLoadView())
	{
		app->reshape();
	}
	app->visit();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.5);

	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 4000000);
	glOrtho();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	gluLookAt(0, -2000000, 2000000, 0, 0, 0, 0, 0, 1);
	*/

	GameApp::getInstance()->rander();

	return GLUS_TRUE;
}

GLUSvoid terminate(GLUSvoid)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(0);

	GameApp::getInstance()->removeAllShader();
}

int initWindow(GLUSint width, GLUSint height)
{
	EGLint eglConfigAttributes[] = {
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_DEPTH_SIZE, 0,
			EGL_STENCIL_SIZE, 0,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
			EGL_NONE
	};

	EGLint eglContextAttributes[] = {
			EGL_CONTEXT_MAJOR_VERSION, 3,
			EGL_CONTEXT_MINOR_VERSION, 2,
			EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE, EGL_TRUE,
			EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
			EGL_NONE
	};
	if (!glusWindowCreate("GLUS Example Window", width, height, GLUS_FALSE, GLUS_FALSE, eglConfigAttributes, eglContextAttributes, 0))
	{
		printf("Could not create window!\n");
		return -1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	glusWindowSetInitFunc(init);
	glusWindowSetReshapeFunc(reshape);
	glusWindowSetUpdateFunc(update);
	glusWindowSetTerminateFunc(terminate);

	glusWindowSetKeyFunc([](const GLUSboolean pressed, const GLUSint key) {
		KeyboardController::getInstance()->handlerKey(key, pressed);
	});
	glusWindowSetMouseFunc(
		[](const GLUSboolean pressed, const GLUSint button, const GLUSint xPos, const GLUSint yPos) {
		GameApp::getInstance()->getEventBus()->postpone(MouseKeyEvent{ EVENT_MOUSEKEY,(float)xPos,GameApp::getInstance()->getViewHeight() - yPos ,button ,(bool)pressed });
	});
	glusWindowSetMouseMoveFunc([](const GLUSint buttons, const GLUSint xPos, const GLUSint yPos) {
		GameApp::getInstance()->getEventBus()->postpone(MouseMoveEvent{ EVENT_MOUSEMOUSE,(float)xPos,GameApp::getInstance()->getViewHeight() - yPos ,buttons });
	});
	glusWindowSetMouseWheelFunc([](const GLUSint buttons, const GLUSint ticks, const GLUSint xPos, const GLUSint yPos) {
		GameApp::getInstance()->getEventBus()->postpone(MouseWheelEvent{ EVENT_MOUSEWHEEL,(float)xPos,GameApp::getInstance()->getViewHeight() - yPos,ticks ,buttons });
	});

	nlohmann::json setting_json;
	std::ifstream iofile("./setting.json");
	if (iofile)
	{
		iofile >> setting_json;
	}
	else
	{
		setting_json["width"] = 1400;
		setting_json["height"] = 900;
		std::ofstream out_setting_json("./setting.json");
		out_setting_json << setting_json << std::endl;
	}
	GameApp::getInstance()->setViewSize(setting_json["width"], setting_json["height"]);

	if (initWindow(setting_json["width"], setting_json["height"]) == -1)
	{
		return -1;
	}

	glusWindowRun();
	return 0;
}


