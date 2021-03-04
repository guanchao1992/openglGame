#pragma once
#include "Node.h"
#include "base/Vector3.h"


StatementNode(TextureNode)
class TextureNode :public Node
{
	StatementCreate(TextureNode)
public:
	~TextureNode();
public:
	void init();

	virtual void randerOne();
	virtual void onDraw();

public:
	static void initProgram();
	//void ensureCapcity(int count);
	
	void clearAllVertex();

	void addVertex(const Vector2&pos, const Vector2&texCoord);
	void setTextureID(GLint id);

public:
	static int g_vertexLocation;
	static int g_textCoordLocation;
	static int g_texture0Location;
private:

	GLuint _verticesVBO = -1;
	GLuint _verticesVAO = -1;
private:
	vector<Vector2> _vertexs;
	vector<Vector2> _texCoords;
	GLint _textureId;

};
