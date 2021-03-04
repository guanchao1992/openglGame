#include "VertexBuffers.hpp"
#include <memory>


TNVertex * getVectexBufferTN(int size)
{
	if (g_fdVectexsSize < size)
	{
		g_fdVectexsSize = size + 8;
		g_ptnVectexs.get_deleter();
		g_ptnVectexs = unique_ptr<TNVertex[]>(new TNVertex[g_fdVectexsSize]);
	}
	return g_ptnVectexs.get();
}





