#include "Shader.h"

Shader::Shader()
{
}

int Shader::loadShader(const char* shaderName)
{
	GLUStextfile vertexSource;
	GLUStextfile fragmentSource;

	char vertPath[256];
	char fragPath[256];

	sprintf_s(vertPath, "../Shader/%s.vert.glsl", shaderName);
	sprintf_s(fragPath, "../Shader/%s.frag.glsl", shaderName);

	//bool vert

	glusFileLoadText(vertPath, &vertexSource);
	glusFileLoadText(fragPath, &fragmentSource);

	glusProgramBuildFromSource(_sprogram.get(), (const GLUSchar**)&vertexSource.text, 0, 0, 0, (const GLUSchar**)&fragmentSource.text);

	glusFileDestroyText(&vertexSource);
	glusFileDestroyText(&fragmentSource);

	return 0;
}
