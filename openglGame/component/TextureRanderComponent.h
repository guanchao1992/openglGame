#pragma once
#include "RanderComponent.h"
#include <vector>
#include "Base/Vector2.h"
#include "Base/Size.h"

using namespace std;

class TextureRanderComponent : public RanderComponent
{
	virtual const char* getName() { return "TextureRanderComponent"; }

	virtual void doBegin();
	virtual void doEnd();
	virtual void update();

	virtual void rander();
	virtual void draw();

public:
	void setTextureID(GLint id);

private:
	int _vertexLocation;
	int _textCoordLocation;
	int _texture0Location;
	int _makeColorLocation;

private:
	GLint _textureId;
};

