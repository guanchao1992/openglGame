#pragma once
#include "RanderComponent.h"
#include <memory>
#include "base/Size.h"
#include "base/Vector2.h"
#include "base/Vector3.h"
#include <vector>
#include "base/Shader.h"
#include "base/Vector4.h"

using namespace std;

class DrawRanderComponent : public RanderComponent
{
public:
	static string getComponentName() { return "DrawRanderComponent"; }

	virtual void doBegin();
	virtual void doEnd();
	virtual void update();

	virtual void rander();
	virtual void draw();

public:

	void clearAllVertex();
	void addVertex(const Vector2&pos, const Vector4&color = Vector4(1, 1, 1, 1));
	void addVertex(float x, float y, const Vector4&color = Vector4(1, 1, 1, 1));
	void addVertexs(const Vector2*poss, int size, const Vector4&color, GLenum drawType);
	//标记一个绘制节点,并指定绘制方式，将addVertex添加的节点绘制成图像
	void signDraw(GLenum drawType);
private:
	GLint _vertexLocation = -1;
	GLint _colorLocation = -1;
	GLint _makeColorLocation = -1;

	GLint _projectMatrix;

	vector<Vector2> _vertexs;
	vector<Vector4> _colors;
	
	int _last_sign = 0;
	vector<pair<GLenum, pair<int, int>>> _signs; //pair<绘制方式,pair<顶点起点index，顶点数量>>

};

