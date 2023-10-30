#include <iostream>
#include <chrono>
#include <vector>
#include "Graph.h"
#include "Grid.h"
#include "PotentialField.h"
#include "SFML/Graphics.hpp"


/*
 N = 10; M = 10; K = 18;


 AgentOne:
     start = 0 0
     end = 5 5

 AgentTwo:
     start = 6 0
     end = 4 4

 AgentThree:
     start = 1 2
     end = 8 1

 K:
 2 2
 3 2
 4 2
 2 3
 3 3
 4 3
 7 3
 8 3
 7 4
 8 4
 0 9
 1 6
 2 6
 3 9
 6 8
 7 9
 8 9
 9 9
 */


void Dijkstra(sf::RenderWindow* window, Grid* grid)
{
    std::chrono::time_point<std::chrono::system_clock> clockStart, clockEnd;

    int N, M, K;
    int agentOneStartX, agentOneStartY, agentOneFinishX, agentOneFinishY;
    int agentTwoStartX, agentTwoStartY, agentTwoFinishX, agentTwoFinishY;
    int agentThreeStartX, agentThreeStartY, agentThreeFinishX, agentThreeFinishY;

    //std::cout << "N: ";
    //std::cin >> N;

    //std::cout << "M: ";
    //std::cin >> M;

    N = 10;
    M = 10;

    std::cout << "K: ";
    std::cin >> K;

    std::cout << "Введите координаты стартовой и конечной позиций первого агента в виде Xstart Ystart Xend Yend: ";
    std::cin >> agentOneStartX >> agentOneStartY >> agentOneFinishX >> agentOneFinishY;

    std::cout << "Введите координаты стартовой и конечной позиций второго агента в виде Xstart Ystart Xend Yend: ";
    std::cin >> agentTwoStartX >> agentTwoStartY >> agentTwoFinishX >> agentTwoFinishY;

    std::cout << "Введите координаты стартовой и конечной позиций третьего агента в виде Xstart Ystart Xend Yend: ";
    std::cin >> agentThreeStartX >> agentThreeStartY >> agentThreeFinishX >> agentThreeFinishY;


    std::vector<Vec2d*> obstacles;

    for (int i = 0; i < K; i++)
    {
        int obstacleX, obstacleY;
        Vec2d* obstacleVec = new Vec2d;

        std::cout << "Введите координаты преграды в виде X Y: ";
        std::cin >> obstacleX >> obstacleY;

        obstacleVec->x = obstacleX; obstacleVec->y = obstacleY;

        obstacles.push_back(obstacleVec);
    }

    Graph g(N, M);
    //Grid grid(N, M, obstacles, window);
    grid->addObstacles(obstacles);


    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            if (grid->getCellValue(y, x) == 0)
            {
                if (y - 1 >= 0 && grid->getCellValue(y - 1, x) == 0)
                    g.addEdge(y * M + x, (y - 1) * M + x, 1);
                if (y + 1 < N && grid->getCellValue(y + 1, x) == 0)
                    g.addEdge(y * M + x, (y + 1) * M + x, 1);
                if (x - 1 >= 0 && grid->getCellValue(y, x - 1) == 0)
                    g.addEdge(y * M + x, y * M + (x - 1), 1);
                if (x + 1 < M && grid->getCellValue(y, x + 1) == 0)
                    g.addEdge(y * M + x, y * M + (x + 1), 1);
            }
        }
    }


    clockStart = std::chrono::system_clock::now();


    std::vector<int> visited = g.Dijkstra(agentOneStartX, agentOneStartY, agentOneFinishX, agentOneFinishY);
    grid->addShortestPath(visited, agentOneFinishX, agentOneFinishY);
    
    
    g.clear();


    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            if (grid->getCellValue(y, x) == 0)
            {
                if (y - 1 >= 0 && grid->getCellValue(y - 1, x) == 0)
                    g.addEdge(y * M + x, (y - 1) * M + x, 1);
                if (y + 1 < N && grid->getCellValue(y + 1, x) == 0)
                    g.addEdge(y * M + x, (y + 1) * M + x, 1);
                if (x - 1 >= 0 && grid->getCellValue(y, x - 1) == 0)
                    g.addEdge(y * M + x, y * M + (x - 1), 1);
                if (x + 1 < M && grid->getCellValue(y, x + 1) == 0)
                    g.addEdge(y * M + x, y * M + (x + 1), 1);
            }
        }
    }

    visited = g.Dijkstra(agentTwoStartX, agentTwoStartY, agentTwoFinishX, agentTwoFinishY);
    grid->addShortestPath(visited, agentTwoFinishX, agentTwoFinishY);


    g.clear();


    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            if (grid->getCellValue(y, x) == 0)
            {
                if (y - 1 >= 0 && grid->getCellValue(y - 1, x) == 0)
                    g.addEdge(y * M + x, (y - 1) * M + x, 1);
                if (y + 1 < N && grid->getCellValue(y + 1, x) == 0)
                    g.addEdge(y * M + x, (y + 1) * M + x, 1);
                if (x - 1 >= 0 && grid->getCellValue(y, x - 1) == 0)
                    g.addEdge(y * M + x, y * M + (x - 1), 1);
                if (x + 1 < M && grid->getCellValue(y, x + 1) == 0)
                    g.addEdge(y * M + x, y * M + (x + 1), 1);
            }
        }
    }

    visited = g.Dijkstra(agentThreeStartX, agentThreeStartY, agentThreeFinishX, agentThreeFinishY);
    grid->addShortestPath(visited, agentThreeFinishX, agentThreeFinishY);


    clockEnd = std::chrono::system_clock::now();


    std::chrono::duration<double> elapsedSeconds = clockEnd - clockStart;


    //grid->print();
    grid->draw();

    std::cout << "Время выполнения: " << elapsedSeconds.count() << " сек." << std::endl;
}


void PotField(sf::RenderWindow* window, Grid* grid)
{
    std::chrono::time_point<std::chrono::system_clock> clockStart, clockEnd;

    int N, M, K;
    int agentOneStartX, agentOneStartY, agentOneFinishX, agentOneFinishY;
    int agentTwoStartX, agentTwoStartY, agentTwoFinishX, agentTwoFinishY;
    int agentThreeStartX, agentThreeStartY, agentThreeFinishX, agentThreeFinishY;


    //std::cout << "N: ";
    //std::cin >> N;

    //std::cout << "M: ";
    //std::cin >> M;

    N = 10;
    M = 10;

    std::cout << "K: ";
    std::cin >> K;

    std::cout << "Введите координаты стартовой и конечной позиций первого агента в виде Xstart Ystart Xend Yend: ";
    std::cin >> agentOneStartX >> agentOneStartY >> agentOneFinishX >> agentOneFinishY;

    std::cout << "Введите координаты стартовой и конечной позиций второго агента в виде Xstart Ystart Xend Yend: ";
    std::cin >> agentTwoStartX >> agentTwoStartY >> agentTwoFinishX >> agentTwoFinishY;

    std::cout << "Введите координаты стартовой и конечной позиций третьего агента в виде Xstart Ystart Xend Yend: ";
    std::cin >> agentThreeStartX >> agentThreeStartY >> agentThreeFinishX >> agentThreeFinishY;


    std::vector<Vec2d*> obstacles;

    for (int i = 0; i < K; i++)
    {
        int obstacleX, obstacleY;
        Vec2d* obstacleVec = new Vec2d;

        std::cout << "Введите координаты преграды в виде X Y: ";
        std::cin >> obstacleX >> obstacleY;

        obstacleVec->x = obstacleX; obstacleVec->y = obstacleY;

        obstacles.push_back(obstacleVec);
    }

    //Grid grid(N, M, obstacles, window);
    grid->addObstacles(obstacles);

    std::vector<Agent*> agents;

    Agent* agentOne = new Agent;
    agentOne->id = 1;
    agentOne->prevPos.x = agentOneStartX; agentOne->prevPos.y = agentOneStartY;
    agentOne->currPos.x = agentOneStartX; agentOne->currPos.y = agentOneStartY;
    agentOne->destPos.x = agentOneFinishX; agentOne->destPos.y = agentOneFinishY;
    
    Agent* agentTwo = new Agent;
    agentTwo->id = 2;
    agentTwo->prevPos.x = agentTwoStartX; agentTwo->prevPos.y = agentTwoStartY;
    agentTwo->currPos.x = agentTwoStartX; agentTwo->currPos.y = agentTwoStartY;
    agentTwo->destPos.x = agentTwoFinishX; agentTwo->destPos.y = agentTwoFinishY;

    Agent* agentThree = new Agent;
    agentThree->id = 3;
    agentThree->prevPos.x = agentThreeStartX; agentThree->prevPos.y = agentThreeStartY;
    agentThree->currPos.x = agentThreeStartX; agentThree->currPos.y = agentThreeStartY;
    agentThree->destPos.x = agentThreeFinishX; agentThree->destPos.y = agentThreeFinishY;


    for (std::vector<Vec2d*>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
    {
        agentOne->obstacles.push_back(*it);
        agentTwo->obstacles.push_back(*it);
        agentThree->obstacles.push_back(*it);
    }

    agentOne->obstacles.push_back(&agentTwo->currPos);
    agentOne->obstacles.push_back(&agentThree->currPos);

    agentTwo->obstacles.push_back(&agentOne->currPos);
    agentTwo->obstacles.push_back(&agentThree->currPos);

    agentThree->obstacles.push_back(&agentOne->currPos);
    agentThree->obstacles.push_back(&agentTwo->currPos);


    agents.push_back(agentOne);
    agents.push_back(agentTwo);
    agents.push_back(agentThree);


    std::cout << "ИСХОДНОЕ СОСТОЯНИЕ" << std::endl;

    grid->moveAgent(agentOne);
    grid->moveAgent(agentTwo);
    grid->moveAgent(agentThree);
    grid->print();


    clockStart = std::chrono::system_clock::now();

    PotentialField field(grid, agents, 1, 1);

    clockEnd = std::chrono::system_clock::now();


    std::chrono::duration<double> elapsedSeconds = clockEnd - clockStart;


    field.run();

    std::cout << "Время выполнения: " << elapsedSeconds.count() << " сек." << std::endl;
}


int main()
{
    setlocale(LC_CTYPE, "Russian");

    int option;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(RESOLUTION_WIDTH, RESOLUTION_HEIGHT), "Pathfinding");
    Grid* grid = new Grid(10, 10, window);

    std::cout << "Дейкстра - 1\nПотенциальные поля - 2" << std::endl;
    std::cin >> option;

    while (option != 1 && option != 2)
    {
        std::cout << "Дейкстра - 1\nПотенциальные поля - 2" << std::endl;
        std::cin >> option;
    }

    if (option == 1)
        Dijkstra(window, grid);
    else
        PotField(window, grid);

    while (window->isOpen()) {
        sf::Event event;

        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
            }
        }

        grid->draw();
    };

    return 0;
}
