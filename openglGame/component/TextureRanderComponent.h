#pragma once
#include "RanderComponent.h"
#include <vector>
#include "Base/Vector2.h"
#include "Base/Size.h"

using namespace std;

class TextureRanderComponent : public RanderComponent
{
	static string getComponentName() { return "TextureRanderComponent"; }

	virtual void doBegin();
	virtual void doEnd();
	virtual void update();

	virtual void rander();
	virtual void draw();

public:
	void setSize(const Size& size);
	void setTextureID(GLint id);

private:
	int _vertexLocation;
	int _textCoordLocation;
	int _texture0Location;
	int _makeColorLocation;

private:
	vector<Vector2> _vertexs;
	vector<Vector2> _texCoords;
	GLint _textureId;
	Size _size;
};

