#pragma once

#include "IGrid.h"
#include "Vec2Int.h"
#include <vector>

typedef double (*heuristic)(Vec2Int const& a, Vec2Int const& b);

class IPathFinder
{
public:

	virtual std::vector<Node*> GetPath() = 0;
	virtual double CalculateHeuristic(Vec2Int const& a, Vec2Int const& b) const = 0;
};