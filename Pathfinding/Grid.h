#pragma once
#include <vector>
#include "Common.h"
#include "SFML/Graphics.hpp"


class Grid
{
private:
	int N;
	int M;
	int** grid;
	int shortestPathCnt;
	sf::RenderWindow* window;
public:
	Grid(int N, int M, sf::RenderWindow* window);

	Grid(int N, int M, std::vector<Vec2d*>& obstacles, sf::RenderWindow* window);

	void addObstacles(std::vector<Vec2d*>& obstacles);

	void addShortestPath(std::vector<int>& visited, int dst_x, int dst_y);

	void moveAgent(Agent* agent);

	int getCellValue(int y, int x);

	void print();

	void draw();
};