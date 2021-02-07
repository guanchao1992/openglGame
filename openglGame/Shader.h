#pragma once

#include <memory>
#include "GL/glus.h"


using namespace std;

class Shader;
typedef shared_ptr<Shader> SPShader;
typedef shared_ptr<GLUSprogram> SPGLUSprogram;

class Shader
{
public:
	Shader();
public:
	int loadShader(const char* shaderName);

	template<typename TT> void glUniformMatrix4fv(const TT &t);


	GLint getProgram() { return _sprogram->program; };


	SPGLUSprogram _sprogram = make_shared<GLUSprogram>();
};

