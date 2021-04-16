#pragma once
#include "component/Component.hpp"
#include <GL/glew.h>

class RanderComponent : public Component
{
public:
	~RanderComponent();
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_RANDER; }

	virtual void doBegin();

	virtual void rander() = 0;
	virtual void draw() = 0;

	void genBuffer();
	inline void reDraw() { _redraw = true; }
protected:
	GLint _program = -1;
	GLuint _verticesVBO = -1;
	GLuint _verticesVAO = -1;

	bool _redraw = true;
};

