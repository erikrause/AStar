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
#include <fstream>
#include <string>

sf::RectangleShape g_rectangleOrigin;
Matrix* g_matrix;
float g_outlineThickness = 1;
float g_isStarted = false;
Vec2Int* g_startPos;
Vec2Int* g_endPos;
bool g_rightClickPressed = false;

sf::Color makeHeuristicColor(Node node)
{
	return sf::Color(0, node.Heuristic * 51, 0);
}

sf::Color makeWeightColor(Node node)
{
	return sf::Color(0, 0, (1 - node.GetWeight() / 15) * 255);
}

sf::RectangleShape configureShape(sf::Window& window, IGrid& grid)
{
	Vec2Float gridSize = Vec2Float(grid.GetSize().X, grid.GetSize().Y);
	Vec2Float windowSize = Vec2Float(window.getSize().x, window.getSize().y);
	Vec2Float rectangleSize = windowSize / gridSize;
	auto rectangleOrigin = sf::RectangleShape(sf::Vector2f(rectangleSize.X - g_outlineThickness, rectangleSize.Y - g_outlineThickness));
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
		else if (event.type == sf::Event::KeyPressed)
		{
			sf::Event::KeyEvent keyEvent = event.key;
			if (keyEvent.code == sf::Keyboard::Enter)
			{
				g_isStarted = true;
			}
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			sf::Event::MouseButtonEvent mouseBtnEvent = event.mouseButton;
			Vec2Float displayPos = Vec2Float(mouseBtnEvent.x, mouseBtnEvent.y);
			Vec2Float uvPos = displayPos / Vec2Float(window.getSize().x, window.getSize().y);
			Vec2Int pos = Vec2Int(uvPos.X * g_matrix->GetSize().X, uvPos.Y * g_matrix->GetSize().Y);

			if (mouseBtnEvent.button == sf::Mouse::Button::Left)
			{
				if (!g_startPos)
				{
					g_startPos = new Vec2Int(pos);
				}
				else if (!g_endPos)
				{
					g_endPos = new Vec2Int(pos);
				}
			}
			else if (mouseBtnEvent.button == sf::Mouse::Button::Right)
			{
				g_rightClickPressed = true;
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			auto e = event.mouseButton;
			if (e.button == sf::Mouse::Button::Right)
			{
				g_rightClickPressed = false;
			}
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			if (g_rightClickPressed)
			{
				auto mouseMovedEvent = event.mouseMove;
				Vec2Float displayPos = Vec2Float(mouseMovedEvent.x, mouseMovedEvent.y);
				Vec2Float uvPos = displayPos / Vec2Float(window.getSize().x, window.getSize().y);
				Vec2Int pos = Vec2Int(uvPos.X * g_matrix->GetSize().X, uvPos.Y * g_matrix->GetSize().Y);
				g_matrix->GetNode(pos)->SetWeight(DBL_MAX);
			}
		}
	}
}

//std::vector<double> readWeigths(std::string filename)
//{
//	std::ifstream inFile;
//	inFile.open(filename);
//
//	if (!inFile)
//	{
//		std::cerr << "Unable to load weights from file!" << std::endl;
//		exit(1);
//	}
//	else
//	{
//		char ch;
//		std::string fileContent;
//		while (inFile >> ch)
//		{
//			fileContent += ch;
//		}
//	}
//
//	return std::vector<double>();
//}

int main(int argc, char* argv[])
{
	// Grid initialization:
	Vec2Int size;
	if (argc > 1)
	{
		size.X = atoi(argv[1]);
		size.Y = atoi(argv[2]);
	}
	else
	{
		size = Vec2Int(120, 120);
	}

	g_matrix = new Matrix(size);//, 0.4);

	// Window setup:
	sf::RenderWindow window{ {800, 600}, "AStart algorithm" };
	window.setFramerateLimit(60);

	g_rectangleOrigin = configureShape(window, *g_matrix);

	// Show initial grid:
	while (!g_isStarted)
	{
		eventHandling(window);

		for (int j = 0; j < g_matrix->GetSize().Y; j++)
		{
			for (int i = 0; i < g_matrix->GetSize().X; i++)
			{
				Node* node = g_matrix->GetNode(Vec2Int(i, j));
				auto rectangle = sf::RectangleShape(g_rectangleOrigin);
				rectangle.setPosition(sf::Vector2f(i * (g_rectangleOrigin.getSize().x + g_outlineThickness), j * (g_rectangleOrigin.getSize().y + g_outlineThickness)));
				rectangle.setFillColor(makeWeightColor(*node));
				window.draw(rectangle);
			}
		}
		if (g_startPos)
		{
			auto rectangle = sf::RectangleShape(g_rectangleOrigin);
			rectangle.setPosition(sf::Vector2f(g_startPos->X * (g_rectangleOrigin.getSize().x + g_outlineThickness), g_startPos->Y * (g_rectangleOrigin.getSize().y + g_outlineThickness)));
			rectangle.setFillColor(sf::Color::White);
			window.draw(rectangle);
		}
		if (g_endPos)
		{
			auto rectangle = sf::RectangleShape(g_rectangleOrigin);
			rectangle.setPosition(sf::Vector2f(g_endPos->X * (g_rectangleOrigin.getSize().x + g_outlineThickness), g_endPos->Y * (g_rectangleOrigin.getSize().y + g_outlineThickness)));
			rectangle.setFillColor(sf::Color::White);
			window.draw(rectangle);
		}

		window.display();
	}

	// Finding path:
	BinaryHeapContainer container = BinaryHeapContainer();
	AStar aStar = AStar(*g_matrix, *g_startPos, *g_endPos, container);
	std::vector<Node*> path = aStar.GetPath();

	// Show path and opened nodes:
	while (window.isOpen())
	{
		eventHandling(window);

		for (int j = 0; j < g_matrix->GetSize().Y; j++)
		{
			for (int i = 0; i < g_matrix->GetSize().X; i++)
			{
				Node* node = g_matrix->GetNode(Vec2Int(i, j));
				if (node->IsVisited)
				{
					auto rectangle = sf::RectangleShape(g_rectangleOrigin);
					rectangle.setPosition(sf::Vector2f(i * (g_rectangleOrigin.getSize().x + g_outlineThickness), j * (g_rectangleOrigin.getSize().y + g_outlineThickness)));
					rectangle.setFillColor(makeHeuristicColor(*node));
					window.draw(rectangle);
				}
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

	delete g_matrix, g_startPos, g_endPos;

	return 0;
}