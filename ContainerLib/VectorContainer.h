#pragma once

#include "IContainer.h"
#include <vector>
#include "Node.h"

class VectorContainer : public IContainer
{
public:

	VectorContainer();

	virtual void Push(Node*) override;
	virtual Node* Pop() override;
	virtual size_t Length() const override { return _container.size(); }

protected:

	std::vector<Node*> _container;
};
