#pragma once

#include "IGrid.h"
#include "Vec2Int.h"
#include "IPathFinder.h"

class AStar : public IPathFinder
{
public:

	AStar(IGrid& grid, Vec2Int startPos, Vec2Int endPos, IContainer& MinSearchContainer);

	IGrid& GetGrid();
	Vec2Int GetStartPos();
	Vec2Int GetEndPos();

	virtual std::vector<Node*> GetPath() override;
	virtual double CalculateHeuristic(Vec2Int const& a, Vec2Int const& b) const override;

protected:

	IGrid& _grid;
	Vec2Int _startPos;
	Vec2Int _endPos;
	//IContainer& _closed;
	IContainer& _opened;
};