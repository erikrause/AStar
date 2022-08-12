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
	/// Стоимость попадания в узел.
	/// </summary>
	/// <returns></returns>
	double GetWeight() const { return _weight; }
	
	/// <summary>
	/// Затраченная стоимость попадания в этот узел.
	/// </summary>
	double Cost = 0;

	/// <summary>
	/// Был ли узел посещен.
	/// </summary>
	bool IsVisited = false;

	/// <summary>
	/// Полная эвристика (f(x) = g(x) + h(x)).
	/// </summary>
	double Heuristic = DBL_MAX;

	/// <summary>
	/// Узел, с которого пришли. NULL Для стартового или непосещенного узла.
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