#pragma once
#include "component/Component.hpp"
#include <GL/glew.h>

class OutlineBoxComponent;

class RanderComponent : public Component
{
public:
	RanderComponent();
	~RanderComponent();
public:
	virtual const char* getName() { return "RanderComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_RANDER; }

	virtual void doBegin();
	virtual void doEnd();

	virtual void rander();
	virtual void draw();
	virtual void randerOutLine();

	void genBuffer();
	inline void reDraw() { _redraw = true; }

	void setOutlineBoxComponent(OutlineBoxComponent*com);
protected:
	GLint _program = -1;
	GLuint _verticesVBO = -1;
	GLuint _verticesVAO = -1;

	bool _redraw = true;


	OutlineBoxComponent* _outlineBoxCom = nullptr;	//√Ë±ﬂ
};

