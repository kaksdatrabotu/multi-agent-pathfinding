#include <iostream>
#include <vector>
#include "Grid.h"
#include "PotentialField.h"
#include "SFML/Graphics.hpp"


Grid::Grid(int N, int M, sf::RenderWindow* window)
{
	this->N = N;
	this->M = M;
	this->window = window;

	this->grid = new int*[N];

	for (int y = 0; y < N; y++)
	{
		this->grid[y] = new int[M];
		for (int x = 0; x < M; x++)
		{
			this->grid[y][x] = 0;
		}
	}

	this->shortestPathCnt = 0;
}


Grid::Grid(int N, int M, std::vector<Vec2d*>& obstacles, sf::RenderWindow* window)
{
	this->N = N;
	this->M = M;
	this->window = window;

	this->grid = new int*[N];

	for (int y = 0; y < N; y++)
	{
		this->grid[y] = new int[M];
		for (int x = 0; x < M; x++)
		{
			this->grid[y][x] = 0;
		}
	}

	this->addObstacles(obstacles);

	this->shortestPathCnt = 0;
}


void Grid::addObstacles(std::vector<Vec2d*>& obstacles)
{
	for (std::vector<Vec2d*>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
	{
		Vec2d* obstacle = *it;

		int x = obstacle->x;
		int y = obstacle->y;

		this->grid[y][x] = -1;
	}
}


void Grid::addShortestPath(std::vector<int>& visited, int dst_x, int dst_y)
{
	bool isNewPath = false;
	int shortestPathNum = this->shortestPathCnt + 1;
	int v = visited[dst_y * this->M + dst_x];

	if (this->grid[dst_y][dst_x] == 0 || isNewPath) {
		isNewPath = true;
		this->grid[dst_y][dst_x] = shortestPathNum;
	}

	while (v != -1)
	{
		if (this->grid[v / this->M][v % this->M] == 0 || isNewPath) {
			isNewPath = true;
			this->grid[v / this->M][v % this->M] = shortestPathNum;
		}
		v = visited[v];
	}

	if (isNewPath)
		this->shortestPathCnt = shortestPathNum;
}


void Grid::moveAgent(Agent* agent)
{
	int prevX = (int)floor(agent->prevPos.x);
	int prevY = (int)floor(agent->prevPos.y);
	int x = (int)floor(agent->currPos.x);
	int y = (int)floor(agent->currPos.y);

	//this->grid[prevY][prevX] = 0;
	this->grid[y][x] = agent->id;
}


int Grid::getCellValue(int y, int x)
{
	return this->grid[y][x];
}


void Grid::print()
{
	std::cout << "[X/Y]\t";

	for (int x = 0; x < this->M; x++)
	{
		std::cout << "[X-" << x << "]\t";
	}

	std::cout << std::endl << std::endl;

	for (int y = 0; y < this->N; y++)
	{
		std::cout << "[Y-" << y << "]\t";
		for (int x = 0; x < this->M; x++)
		{
			if (this->grid[y][x] == 0)
				std::cout << "[ ]\t";
			else
				std::cout << "[" << this->grid[y][x] << "]\t";
		}
		std::cout << std::endl << std::endl;
	}
}


void Grid::draw()
{
	this->window->clear();
	for (int y = 0; y < this->N; y++)
	{
		for (int x = 0; x < this->M; x++)
		{
			sf::RectangleShape* rect = new sf::RectangleShape();

			rect->setSize(sf::Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT));
			rect->setOutlineThickness(RECTANGLE_THICKNESS);
			rect->setOutlineColor(sf::Color::Blue);
			rect->setPosition(sf::Vector2f(x * RECTANGLE_WIDTH, y * RECTANGLE_HEIGHT));

			switch (this->grid[y][x])
			{
				case -1:
					rect->setFillColor(sf::Color(128, 128, 128));
					break;
				case 0:
					rect->setFillColor(sf::Color::Black);
					break;
				case 1:
					rect->setFillColor(sf::Color::Green);
					break;
				case 2:
					rect->setFillColor(sf::Color::Red);
					break;
				case 3:
					rect->setFillColor(sf::Color::Yellow);
					break;
			}

			this->window->draw(*rect);

		}
	}
	sf::sleep(sf::milliseconds(500));
	this->window->display();
}