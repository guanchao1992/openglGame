#pragma once
#include "DrawRanderComponent.h"
#include "Base/Size.h"
#include "Base/Vector4.h"


//debug π”√
class OutlineBoxComponent :public Component
{
public:
	~OutlineBoxComponent();
public:
	virtual ComponentType getType() { return ComponentType::COMPONENT_OUTLINE; }
	virtual void doBegin();
	virtual void doEnd(); 

	virtual void update();
	virtual void rander();
	virtual void draw();

	inline void setColor(const Vector4& color) { _color = color; }
	inline void setColor(float r, float g, float b, float l) { _color.setVector(r, g, b, l); }
	inline void reDraw() { _redraw = true; }
private:
	GLint _vertexLocation = -1;
	GLint _colorLocation = -1;
	GLint _makeColorLocation = -1;
	GLint _projectMatrix;

	GLint _program = -1;
	GLuint _verticesVBO = -1;
	GLuint _verticesVAO = -1;

	Vector4 _color = { 1, 0, 0, 0.8 };
	bool _redraw = true;
};
