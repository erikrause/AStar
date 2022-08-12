#include "AStar.h"

AStar::AStar(IGrid& grid, Vec2Int startPos, Vec2Int endPos, IContainer& MinSearchContainer)
    :
    _grid(grid),
    _startPos(startPos),
    _endPos(endPos),
    _opened(MinSearchContainer)
{
    //_closed = TContainer();
    _opened.Push(_grid.GetNode(_startPos));
    Node* test1 = _grid.GetNode(_startPos);
    test1->IsVisited = true;
    Node* test2 = _grid.GetNode(_startPos);

    while (_opened.Length() != 0)
    {
        Node* current = _opened.Pop();
        //_closed.Push(current);

        if (current->GetPos() == _endPos)
            break;

        std::vector<Node*> adjacentNodes = _grid.GetAdjacentNodes(current->GetPos());

        for (Node* adjacentNode : adjacentNodes)
        {
            double adjacentNodeNewCost = current->Cost + adjacentNode->GetWeight();   //CalculateHeuristic(current.GetPos(), _endPos);

            if (!adjacentNode->IsVisited || adjacentNodeNewCost < adjacentNode->Cost)
            {
                adjacentNode->Heuristic = adjacentNodeNewCost + CalculateHeuristic(adjacentNode->GetPos(), _endPos);
                adjacentNode->IsVisited = true;
                adjacentNode->Previous = current;
                _opened.Push(adjacentNode);
            }
        }
    }
}

IGrid& AStar::GetGrid()
{
    return _grid;
}

Vec2Int AStar::GetStartPos()
{
    return _startPos;
}

Vec2Int AStar::GetEndPos()
{
    return _endPos;
}

std::vector<Node*> AStar::GetPath()
{
    Node* startNode = _grid.GetNode(GetStartPos());
    Node* endNode = _grid.GetNode(GetEndPos());
    Node* tempNode = endNode;
    std::vector<Node*> path;
    path.push_back(endNode);

    while (tempNode != startNode)
    {
        path.push_back(tempNode->Previous);
        tempNode = tempNode->Previous;
    }
    
    return path;
}

double AStar::CalculateHeuristic(Vec2Int const& a, Vec2Int const& b) const
{
    return abs(a.X - b.X) + abs(a.Y - b.Y);  // Манхэттен
}
