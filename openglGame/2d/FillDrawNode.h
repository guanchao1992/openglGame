#pragma once
#include "Node.h"
#include "Base/Vector3.h"


typedef struct FillDrawVertex__
{
	GLfloat vertexs[4];
	GLfloat colors[4];
} FDVertex;


StatementNode(FillDrawNode)
class FillDrawNode :public Node
{
	StatementCreate(FillDrawNode)
public:
	~FillDrawNode();
public:
	void init();

	virtual void rander();
	virtual void draw(const GLfloat *parentTransform);

public:
	static void initFillDrawProgram();
	//void ensureCapcity(int count);
	
	void clearAllVertex();

	void addVertex(const Vector2&pos);
	void enforceVertex();//使顶点生效，顶点发生变化后需要调用该函数
private:

	static GLint g_vertexLocation;
	static GLint g_colorLocation;
	//static GLfloat *_buffer;

	GLuint _verticesVBO = -1;
	GLuint _verticesVAO = -1;

	GLuint _verticesColorVBO;
	GLuint _verticesColorVAO;
private:

	vector<Vector2> _vertexs;
};
