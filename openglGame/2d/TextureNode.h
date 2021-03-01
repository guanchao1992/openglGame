#pragma once
#include "Node.h"
#include "base/Vector3.h"


typedef struct TextureNodeVertex__
{
	TextureNodeVertex__() {}
	TextureNodeVertex__(TextureNodeVertex__&tn) {
		memcpy((void*)this, &tn, sizeof(TextureNodeVertex__));
	}
	TextureNodeVertex__(const Vector2&pos, const Vector2&texCoord)
	{
		vertexs[0] = pos._x;
		vertexs[1] = pos._y;
		vertexs[2] = 0.0f;
		vertexs[3] = 1.0f;
		this->texCoord[0] = texCoord._x;
		this->texCoord[1] = texCoord._y;
	}

	bool operator==(const TextureNodeVertex__& tn) const
	{
		memcpy((void*)this, &tn, sizeof(TextureNodeVertex__));
	}
	GLfloat vertexs[4];
	GLfloat texCoord[2];
	
} TNVertex;


StatementNode(TextureNode)
class TextureNode :public Node
{
	StatementCreate(TextureNode)
public:
	~TextureNode();
public:
	void init();

	virtual void randerOne();
	virtual void draw(const GLfloat *parentTransform);

public:
	static void initProgram();
	//void ensureCapcity(int count);
	
	void clearAllVertex();

	void addVertex(const Vector2&pos, const Vector2&texCoord);
	void enforceVertex();//使顶点生效，顶点发生变化后需要调用该函数
	void setTextureID(GLint id);
private:

	static GLint g_vertexLocation;
	static GLint g_textCoordLocation;

	static GLint g_texture0Location;

	GLuint _verticesVBO = -1;
	GLuint _verticesVAO = -1;
private:
	vector<Vector2> _vertexs;
	vector<Vector2> _texCoords;
	GLint _textureId;
};
