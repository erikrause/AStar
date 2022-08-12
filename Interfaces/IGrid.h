#pragma once

#include "Vec2Int.h"
#include <vector>
#include "Node.h"
#include "IContainer.h"

class IGrid
{
public:

	virtual ~IGrid() {};
	virtual Node* GetNode(Vec2Int pos) = 0;
	virtual Vec2Int GetSize() = 0;

	/// <summary>
	/// Возвращает частоту заблокированных узлов от 0 до 100.
	/// </summary>
	virtual unsigned char GetBlockingFreq() = 0;

	/// <summary>
	/// Поулчить соседние незаблокированные узлы.
	/// </summary>
	/// <param name="pos">Начальная позиция.</param>
	/// <returns>Массив соседних незаблокированнных узлов.</returns>
	virtual std::vector<Node*> GetAdjacentNodes(Vec2Int pos) = 0;

	//virtual Node GetAdjacentWithMinimumCost(Vec2Int pos) = 0;
};