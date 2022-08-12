#pragma once

#include "IContainer.h"
#include <vector>

class BinaryHeapContainer : public IContainer
{
public:
	BinaryHeapContainer();

	virtual void Push(Node*) override;
	virtual Node* Pop() override;
	virtual size_t Length() const override { return _container.size(); }

protected:

	std::vector<Node*> _container;
};
