#pragma once

//纯的
struct Vertex
{
	float vertexs[4];
};

//TextureNode的顶点信息
struct TNVertex
{
	float vertexs[4];
	float texCoord[2];
};

// FillDrawNode的顶点信息
struct FDVertex 
{
	float vertexs[4];
	float colors[4];
};

template <typename T>
static unique_ptr<T[]>g_ptnVectexs(new T[64]);

template <typename T>
static size_t g_fdVectexsSize = 64;

template <typename T>
T * getVectexBuffer(int size)
{
	if (g_fdVectexsSize<T> < size)
	{
		g_fdVectexsSize<T> = size + 8;
		g_ptnVectexs<T>.get_deleter();
		g_ptnVectexs<T> = unique_ptr<T[]>(new T[g_fdVectexsSize<T>]);
	}
	return g_ptnVectexs<T>.get();
}


