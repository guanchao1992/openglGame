#include "RanderComponent.h"


RanderComponent::~RanderComponent()
{
	if (_verticesVBO != -1)
	{
		glDeleteBuffers(1, &_verticesVBO);
		_verticesVBO = -1;
	}

	if (_verticesVAO != -1)
	{
		glDeleteVertexArrays(1, &_verticesVAO);
		_verticesVAO = -1;
	}
}

void RanderComponent::doBegin()
{
	__super::doBegin();
}


void RanderComponent::genBuffer()
{
	if (_verticesVBO == -1)
	{
		glGenBuffers(1, &_verticesVBO);
	}
	if (_verticesVAO == -1)
	{
		// Create the VAO for the program.
		glGenVertexArrays(1, &_verticesVAO);
	}
}
