#include "RanderComponent.h"
#include "2d/Node.h"
#include "OutlineBoxComponent.h"
#include "AreaComponent.h"


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
	auto areaCom = _object->getComponent<AreaComponent>();
	if (!areaCom)
	{
		areaCom = _object->addComponent<AreaComponent>().get();
	}

	auto outlineCom = _object->getComponent<OutlineBoxComponent>();
	if (outlineCom)
	{
		setOutlineBoxComponent(_outlineBoxCom);
	}

	Node* node = (Node*)(_object);
	if (node)
	{
		switch (getType())
		{
		case COMPONENT_RANDER:
			node->setRanderComponent(this);
		default:
			break;
		} 
	}
}

void RanderComponent::doEnd()
{
	__super::doEnd();
	Node* node = (Node*)(_object);
	if (node)
	{
		switch (getType())
		{
		case COMPONENT_RANDER:
			node->setRanderComponent(nullptr);
		default:
			break;
		}
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

void RanderComponent::rander()
{
	if (_outlineBoxCom)
	{
		_outlineBoxCom->rander();
	}
}

void RanderComponent::draw()
{
	if (_outlineBoxCom)
	{
		_outlineBoxCom->draw();
	}
}

void RanderComponent::setOutlineBoxComponent(OutlineBoxComponent*com)
{
	_outlineBoxCom = com;
}
