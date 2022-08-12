#pragma once
#include "Vec2Int.h"
#include <vector>
#include "Node.h"
#include "IGrid.h"
#include "VectorContainer.h"

class Matrix : public IGrid
{
public:

	Matrix(Vec2Int size);
	Matrix(Vec2Int size, float blockingFreq);
	Matrix(Vec2Int size, std::vector<double> weights);
	virtual ~Matrix();

	//void SetStart(Vec2Int point);
	//void SetEnd(Vec2Int point);
	//std::vector<Node> GetNodes();
	virtual Node* GetNode(Vec2Int pos) override;
	virtual Vec2Int GetSize() override;
	virtual unsigned char GetBlockingFreq() override;
	virtual std::vector<Node*> GetAdjacentNodes(Vec2Int pos) override;
	//virtual Node GetAdjacentWithMinimumCost(Vec2Int pos) override;

protected:

	std::vector<Node*> _nodes;
	Vec2Int _size;
	float _blockingFreq;
	std::vector<Vec2Int> _adjacentDirections = { Vec2Int(-1, 0), Vec2Int(0, 1), Vec2Int(1, 0), Vec2Int(0, -1) };
};