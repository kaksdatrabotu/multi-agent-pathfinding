#pragma once
#include <vector>


#define RESOLUTION_WIDTH 600
#define RESOLUTION_HEIGHT 600

#define RECTANGLE_WIDTH RESOLUTION_WIDTH / 10
#define RECTANGLE_HEIGHT RESOLUTION_HEIGHT / 10
#define RECTANGLE_THICKNESS 3


struct Vec2d
{
	float x;
	float y;
};


struct Agent
{
	int id;
	Vec2d prevPos;
	Vec2d currPos;
	Vec2d destPos;
	std::vector<Vec2d*> obstacles;
	std::vector<Vec2d> path;
};


void normalizeVectorManhattan(Vec2d& v);