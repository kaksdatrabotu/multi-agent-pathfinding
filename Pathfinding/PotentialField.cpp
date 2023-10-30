#include <iostream.>
#include <vector>
#include "Common.h"
#include "PotentialField.h"


PotentialField::PotentialField(Grid* grid, std::vector<Agent*> agents, float collideRaduis, float speed)
{
	this->grid = grid;
	this->agents = agents;
}


void PotentialField::run()
{
	int processedAgents = 0;
	int iterationNum = 1;

	while (true)
	{
		for (std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); it++)
		{
			Agent* agent = *it;

			if (agent->currPos.x == agent->destPos.x && agent->currPos.y == agent->destPos.y)
			{
				processedAgents++;
				continue;
			}

			this->processAgent(agent);
		}

		//std::cout << "=== ÈÒÅÐÀÖÈß #" << iterationNum << " ===" << std::endl;

		for (std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); it++)
		{
			Agent* agent = *it;
			this->grid->moveAgent(agent);
		}
		
		//this->grid->print();
		this->grid->draw();
		iterationNum++;

		if (processedAgents == this->agents.size())
			break;
		else
			processedAgents = 0;
	}

	//std::cout << "ÈÒÎÃ" << std::endl;

	for (std::vector<Agent*>::iterator it = this->agents.begin(); it != this->agents.end(); it++)
	{
		Agent* agent = *it;
		this->grid->moveAgent(agent);
	}

	this->grid->draw();
	//this->grid->print();
}


void PotentialField::processAgent(Agent* agent)
{
	Vec2d vDirection = { agent->destPos.x - agent->currPos.x, agent->destPos.y - agent->currPos.y };
	Vec2d tempVec;


	if (agent->obstacles.size() > 0)
	{
		Vec2d resultVec = vDirection;
		float L = sqrt(resultVec.x * resultVec.x + resultVec.y * resultVec.y);

		if (L == 0)
		{
			normalizeVectorManhattan(resultVec);
		}
		else
		{
			resultVec.x /= L;
			resultVec.y /= L;
		}

		for (std::vector<Vec2d*>::iterator it = agent->obstacles.begin(); it != agent->obstacles.end(); it++)
		{
			Vec2d obstacleVec = **it;
			
			Vec2d distanceBetweenVec = { obstacleVec.x - agent->currPos.x, obstacleVec.y - agent->currPos.y };
			float distanceBetween = sqrt(distanceBetweenVec.x * distanceBetweenVec.x + distanceBetweenVec.y * distanceBetweenVec.y);

			if (distanceBetween <= this->collideRadius)
			{
				float repulsionForceMagnitude = 1 - distanceBetween;
				Vec2d repulsionForceVec = { agent->currPos.x - obstacleVec.x, agent->currPos.y - obstacleVec.y };
				float repulsionForceVecLen = sqrt(repulsionForceVec.x * repulsionForceVec.x + repulsionForceVec.y * repulsionForceVec.y) / repulsionForceMagnitude;


				if (repulsionForceVecLen == 0)
				{
					normalizeVectorManhattan(repulsionForceVec);
				}
				else
				{
					repulsionForceVec.x /= repulsionForceVecLen;
					repulsionForceVec.y /= repulsionForceVecLen;
				}

				resultVec.x += repulsionForceVec.x;
				resultVec.y += repulsionForceVec.y;
			}
		}

		tempVec.x = resultVec.x;
		tempVec.y = resultVec.y;
	}
	else
	{
		tempVec.x = vDirection.x;
		tempVec.y = vDirection.y;
	}

	normalizeVectorManhattan(tempVec);

	if (abs(tempVec.x) == 1 && abs(tempVec.y) == 1)
	{
		if (this->grid->getCellValue(agent->currPos.y + tempVec.y, agent->currPos.x) == 0)
			tempVec.x = 0;
		else if (this->grid->getCellValue(agent->currPos.y, agent->currPos.x + tempVec.x) == 0)
			tempVec.y = 0;
	}

	agent->prevPos.x = agent->currPos.x;
	agent->prevPos.y = agent->currPos.y;

	agent->currPos.x += tempVec.x;
	agent->currPos.y += tempVec.y;
}