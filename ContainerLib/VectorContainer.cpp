#include "VectorContainer.h"

VectorContainer::VectorContainer()
{
}

inline void VectorContainer::Push(Node* element)
{
	_container.emplace_back(element);
}

Node* VectorContainer::Pop()
{
	Node* result = _container.back();
	_container.pop_back();
	return result;
}
