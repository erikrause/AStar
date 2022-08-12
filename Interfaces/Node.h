#pragma once
#include "Vec2Int.h"
#include <float.h>

class Node
{
public:

	Node(Vec2Int pos, double weight)
		:
		_pos(pos),
		_weight(weight)
	{};

	Vec2Int GetPos() { return _pos; }

	bool operator > (Node const& node) const
	{
		return Heuristic > node.Heuristic;
	}

	/// <summary>
	/// ��������� ��������� � ����.
	/// </summary>
	/// <returns></returns>
	double GetWeight() const { return _weight; }
	
	/// <summary>
	/// ����������� ��������� ��������� � ���� ����.
	/// </summary>
	double Cost = 0;

	/// <summary>
	/// ��� �� ���� �������.
	/// </summary>
	bool IsVisited = false;

	/// <summary>
	/// ������ ��������� (f(x) = g(x) + h(x)).
	/// </summary>
	double Heuristic = DBL_MAX;

	/// <summary>
	/// ����, � �������� ������. NULL ��� ���������� ��� ������������� ����.
	/// </summary>
	Node* Previous = NULL;


	static bool Comparator(const Node* max, const Node* min)
	{
		return (max->Heuristic > min->Heuristic);
	}


protected:

	Vec2Int _pos;
	double _weight;
};