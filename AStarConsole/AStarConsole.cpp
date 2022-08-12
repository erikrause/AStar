#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "AStar.h"
#include <BinaryHeapContainer.h>
#include <Matrix.h>
#include "SFML/graphics.hpp"
#include "Vec2Float.h"
#include "Node.h"

sf::RectangleShape g_rectangleOrigin;
Matrix* g_matrix;
float g_outlineThickness = 5;

#define m DBL_MAX
std::vector<double> g_weights = std::vector<double>{ 0,0,0,0,0,0,0,0,
													 0,0,0,0,0,0,0,0,
													 0,0,0,m,m,m,0,0,
													 0,0,0,0,0,m,0,0,
													 0,0,0,0,0,m,0,0,
													 0,0,m,m,m,m,0,0,
													 0,0,0,0,0,0,0,0 };
#undef m

sf::Color makeColor(Node node)
{
	return sf::Color(0, node.Heuristic * 51, 0);
}

sf::RectangleShape configureShape(sf::Window& window, IGrid& grid)
{
	Vec2Float gridSize = Vec2Float(grid.GetSize().X, grid.GetSize().Y);
	Vec2Float windowSize = Vec2Float(window.getSize().x, window.getSize().y);
	Vec2Float rectangleSize = windowSize / gridSize;
	auto rectangleOrigin = sf::RectangleShape(sf::Vector2f(rectangleSize.X, rectangleSize.Y));
	rectangleOrigin.setOutlineThickness(g_outlineThickness);
	rectangleOrigin.setOutlineColor(sf::Color::Black);

	return rectangleOrigin;
}

void eventHandling(sf::Window& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::Resized)
		{
			//g_rectangleOrigin = configureShape(window, *g_matrix);
		}
	}
}

int main()
{
	Vec2Int size = Vec2Int(8, 7);
	Vec2Int startPos = Vec2Int(2, 4);
	Vec2Int endPos = Vec2Int(6, 4);
	g_matrix = new Matrix(size, g_weights);
	BinaryHeapContainer container = BinaryHeapContainer();
	AStar aStar = AStar(*g_matrix, startPos, endPos, container);
	std::vector<Node*> path = aStar.GetPath();

	sf::RenderWindow window{ {800, 600}, "AStart algorithm" };
	window.setFramerateLimit(60);

	g_rectangleOrigin = configureShape(window, *g_matrix);

	while (window.isOpen())
	{
		eventHandling(window);

		for (int j = 0; j < g_matrix->GetSize().Y; j++)
		{
			for (int i = 0; i < g_matrix->GetSize().X; i++)
			{
				Node* node = g_matrix->GetNode(Vec2Int(i, j));
				auto rectangle = sf::RectangleShape(g_rectangleOrigin);
				rectangle.setPosition(sf::Vector2f(i * (g_rectangleOrigin.getSize().x + g_outlineThickness), j * (g_rectangleOrigin.getSize().y + g_outlineThickness)));
				rectangle.setFillColor(makeColor(*node));
				window.draw(rectangle);
			}
		}

		for (Node* node : path)
		{
			auto rectangle = sf::RectangleShape(g_rectangleOrigin);
			rectangle.setPosition(sf::Vector2f(node->GetPos().X * (g_rectangleOrigin.getSize().x + g_outlineThickness), node->GetPos().Y * (g_rectangleOrigin.getSize().y + g_outlineThickness)));
			rectangle.setFillColor(sf::Color::Red);
			window.draw(rectangle);
		}

		//auto rectangle = sf::RectangleShape(sf::Vector2f(750, 550));
		//rectangle.setFillColor(sf::Color::Green);
		
		//window.clear();
		
		window.display();
	}

	delete g_matrix;

	return 0;
}