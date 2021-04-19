#include "RanderComponent.h"
#include "2d/Node.h"


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
	Node* node = (Node*)(_object);
	if (node)
	{
		node->setRanderComponent(this);
	}
}

void RanderComponent::doEnd()
{
	__super::doEnd();
	Node* node = (Node*)(_object);
	if (node)
	{
		node->setRanderComponent(nullptr);
	}
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
