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
#include "FillDrawNode.h"
 /**
  * The used shader program.
  */
//static GLUSprogram g_program;

/**
 * The location of the vertex in the shader program.
 */

GLUSboolean init(GLUSvoid)
{
	auto app = GameApp::getInstance();
	app->init();

	auto fd = FillDrawNode::create();
	GameApp::getInstance()->addChild(fd);
	fd->addVertex(Vector2(-0.5,0));
	fd->addVertex(Vector2(0.5,0));
	fd->addVertex(Vector2(0,0.5));
	fd->setColor(Vector4(1, 0, 1, 1));
	fd->enforceVertex();


	auto fd2 = FillDrawNode::create();
	GameApp::getInstance()->addChild(fd2);
	fd2->addVertex(Vector2(-0.5, -0.5));
	fd2->addVertex(Vector2(0.5, -0.5));
	fd2->addVertex(Vector2(0, 0));
	fd2->setColor(Vector4(0, 0, 1, 1));
	fd2->enforceVertex();


	fd->draw();
	fd2->draw();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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

	app->draw();
	glClear(GL_DEPTH_BUFFER_BIT);
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

	if (!glusWindowCreate("GLUS Example Window", 640, 480, GLUS_FALSE, GLUS_FALSE, eglConfigAttributes, eglContextAttributes, 0))
	{
		printf("Could not create window!\n");
		return -1;
	}

	glusWindowRun();

	return 0;
}
