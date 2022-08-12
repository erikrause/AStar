#include "Matrix.h"
#include <time.h>
#include <iostream>

Matrix::Matrix(Vec2Int size, unsigned char blockingFreq)
	:
	_size(size),
	_blockingFreq(blockingFreq)
{
	// = std::vector<Node>(size.X * size.Y, std::allocator<Node>());

	std::srand(std::time(nullptr));

	for (int j = 0; j < _size.Y; j++)
	{
		for (int i = 0; i < _size.X; j++)
		{
			int randomPercent = std::rand() / (RAND_MAX + 1u);	// число от 0 до 100.
			bool isBlocked = round((double)(randomPercent - blockingFreq) / 100);
			double weight = isBlocked ? DBL_MAX : 0;
			//_nodes[i + j * size.X] = (Node(Vec2Int(i, j), isBlocked));
			_nodes.push_back(new Node(Vec2Int(i, j), weight));
		}
	}
}

Matrix::Matrix(Vec2Int size, std::vector<double> weights)
	:
	_size(size),
	_blockingFreq(0)
{
	for (int j = 0; j < _size.Y; j++)
	{
		for (int i = 0; i < _size.X; i++)
		{
			_nodes.push_back(new Node(Vec2Int(i, j), weights[i + j * size.X]));//(std::make_unique<Node>(new Node(Vec2Int(i, j), weights[i + j * size.X])));
		}
	}
}

Matrix::~Matrix()
{
	_nodes.clear();
}

Node* Matrix::GetNode(Vec2Int pos)
{
	return _nodes[pos.X + _size.X * pos.Y];
}

Vec2Int Matrix::GetSize()
{
	return _size;
}

unsigned char Matrix::GetBlockingFreq()
{
	return _blockingFreq;
}

//Node Matrix::GetAdjacentWithMinimumCost(Vec2Int pos)
//{
//	IContainer<Node>& nodes = GetAdjacentNodes(pos);
//
//	
//	for (Node node : nodes)
//	{
//		nodes
//	}
//	return Node();
//}

std::vector<Node*> Matrix::GetAdjacentNodes(Vec2Int pos)
{
	std::vector<Node*> result;

	for (Vec2Int direction : _adjacentDirections)
	{
		Vec2Int newPos = pos + direction;

		if (newPos.X > -1 && newPos.Y > -1 &&
			newPos.X < _size.X && newPos.Y < _size.Y)
		{
			Node* adjacentNode = GetNode(newPos);

			result.push_back(adjacentNode);
		}
	}

	return result;
}