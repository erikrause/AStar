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
	/// ���������� ������� ��������������� ����� �� 0 �� 100.
	/// </summary>
	virtual unsigned char GetBlockingFreq() = 0;

	/// <summary>
	/// �������� �������� ����������������� ����.
	/// </summary>
	/// <param name="pos">��������� �������.</param>
	/// <returns>������ �������� ������������������ �����.</returns>
	virtual std::vector<Node*> GetAdjacentNodes(Vec2Int pos) = 0;

	//virtual Node GetAdjacentWithMinimumCost(Vec2Int pos) = 0;
};