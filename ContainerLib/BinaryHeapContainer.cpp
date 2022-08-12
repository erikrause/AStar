#include "BinaryHeapContainer.h"
#include <algorithm>
#include "Node.h"

BinaryHeapContainer::BinaryHeapContainer()
{

}


void BinaryHeapContainer::Push(Node* element)
{
	_container.emplace_back(element);
	push_heap(_container.begin(), _container.end(), Node::Comparator);
}

Node* BinaryHeapContainer::Pop()
{
	pop_heap(_container.begin(), _container.end(), Node::Comparator);
	Node* result = _container.back();
	_container.pop_back();
	return result;
}
