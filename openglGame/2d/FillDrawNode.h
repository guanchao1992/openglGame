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

	void addVertex(const Vector2&pos, const Vector4&color = Vector4(1, 1, 1, 1));
	void addVertex(float x, float y, const Vector4&color = Vector4(1, 1, 1, 1));
	void addVertexs(const Vector2*poss, int size, const Vector4&color, GLenum drawType);
	//标记一个绘制节点,并指定绘制方式，将addVertex添加的节点绘制成图像
	void signDraw(GLenum drawType);
private:
	static GLint g_vertexLocation;
	static GLint g_colorLocation;
	static GLint g_makeColorLocation;

	GLuint _verticesVBO = -1;
	GLuint _verticesVAO = -1;

	GLuint _verticesColorVBO;
	GLuint _verticesColorVAO;
private:
	vector<Vector2> _vertexs;
	vector<Vector4> _colors;
	
	vector<pair<int, GLenum>> _signs;

};
