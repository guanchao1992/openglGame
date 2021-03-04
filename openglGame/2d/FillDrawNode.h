#pragma once
#include "Node.h"
#include "base/Vector3.h"


StatementNode(FillDrawNode)
class FillDrawNode :public Node
{
	StatementCreate(FillDrawNode)
public:
	~FillDrawNode();
public:
	void init();

	virtual void randerOne();
	virtual void onDraw();

public:
	static void initProgram();
	
	void clearAllVertex();

	void addVertex(const Vector2&pos);
private:
	static GLint g_vertexLocation;
	static GLint g_colorLocation;

	GLuint _verticesVBO = -1;
	GLuint _verticesVAO = -1;

	GLuint _verticesColorVBO;
	GLuint _verticesColorVAO;
private:

	vector<Vector2> _vertexs;

};
