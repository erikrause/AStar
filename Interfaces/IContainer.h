#pragma once
#include "Node.h"

class IContainer
{
public:

	virtual void Push(Node*) = 0;
	virtual Node* Pop() = 0;
	virtual size_t Length() const = 0;

	//virtual& T operator[](size_t);// = 0;
};