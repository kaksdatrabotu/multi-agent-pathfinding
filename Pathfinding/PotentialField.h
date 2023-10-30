#pragma once
#include <vector>
#include "Grid.h"
#include "Common.h"


class PotentialField
{
private:
	Grid* grid;
	std::vector<Agent*> agents;
	
	const int collideRadius = 1;
public:
	PotentialField(Grid* grid, std::vector<Agent*> agents, float collideRadius, float speed);

	void run();

	void processAgent(Agent* agent);
};