/**
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

#define VIEW_WIDTH 1000
#define VIEW_HEIGHT 800

const static GLfloat biasMatrix[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f };

GLUSboolean init(GLUSvoid)
{
	auto app = GameApp::getInstance();
	app->init();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Basic blending equation.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	app->visit(biasMatrix, false);

	return GLUS_TRUE;
}
static int redisplay_interval;

GLUSvoid reshape(GLUSint width, GLUSint height)
{
	auto app = GameApp::getInstance();
	app->setViewSize(width, height);
	app->reshape();

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
	app->visit(biasMatrix, app->isReLoadView());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	GameApp::getInstance()->rander();

	return GLUS_TRUE;
}

GLUSvoid terminate(GLUSvoid)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(0);

	GameApp::getInstance()->removeAllShader();
}

int main(int argc, char* argv[])
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

	glusWindowSetInitFunc(init);

	glusWindowSetReshapeFunc(reshape);

	glusWindowSetUpdateFunc(update);

	glusWindowSetTerminateFunc(terminate);

	
	glusWindowSetKeyFunc([](const GLUSboolean pressed, const GLUSint key) {
		auto app = GameApp::getInstance();
		app->programKey(pressed, key);
	});

	if (!glusWindowCreate("GLUS Example Window", VIEW_WIDTH, VIEW_HEIGHT, GLUS_FALSE, GLUS_FALSE, eglConfigAttributes, eglContextAttributes, 0))
	{
		printf("Could not create window!\n");
		return -1;
	}

	glusWindowRun();

	return 0;
}
