/**
 * OpenGL 3 - Example 02
 *
 * @author	Norbert Nopper norbert@nopper.tv
 *
 * Homepage: http://nopper.tv
 *
 * Copyright Norbert Nopper
 */
#define CRTDBG_MAP_ALLOC    
#include <stdlib.h>    
#include <crtdbg.h> 

/*
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new (DBG_NEW)
#endif 
#endif  // _DEBUG
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
#include <profileapi.h>
#include <synchapi.h>


LARGE_INTEGER g_nLast;
LARGE_INTEGER g_nNow;
LARGE_INTEGER g_freq;
LONGLONG g_interval;
LONGLONG g_frameInterval;
LONG g_waitMS;

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

	QueryPerformanceCounter(&g_nLast);
	QueryPerformanceFrequency(&g_freq);
	g_frameInterval = g_freq.QuadPart / 120;

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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.5);
	GameApp::getInstance()->rander();

	/*
	static float t_time = 0.f;
	static int frame = 0;
	static int timebase = 0;
	//static char s[256] = { 0 };
	static wchar_t s[256] = { 0 };
	frame++;
	t_time = t_time + time;
	if (t_time > 1.f) {
		//sprintf_s(s, 256, "FPS:%4.2f", frame * 1.0 / (t_time - timebase));

		printf("FPS:%4.2f  node数量：%d", frame * 1.0f / t_time, GameApp::getInstance()->getNodeCount());

		timebase = t_time;
		t_time = 0;
		frame = 0;
	}
	*/

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

	GLUSboolean run = GLUS_TRUE;

	if (!glusWindowStartup())
	{
		return GLUS_FALSE;
	}

	while (run)
	{
		QueryPerformanceCounter(&g_nNow);
		g_interval = g_nNow.QuadPart - g_nLast.QuadPart;
		if (g_interval >= g_frameInterval)
		{
			g_nLast.QuadPart = g_nNow.QuadPart;
			run = glusWindowLoop();
		}
		else
		{
			g_waitMS = (g_frameInterval - g_interval) * 1000LL / g_freq.QuadPart;
			if (g_waitMS > 1L)
			{
				Sleep(g_waitMS);
			}
		}
	}
	glusWindowShutdown();
	return 0;
}


