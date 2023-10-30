#include <iostream>
#include "Graph.h"


Graph::Graph(size_t N, size_t M)
{
	this->N = N;
	this->M = M;
	this->V = N*M;
	this->adj_list = new std::list<iPair>[this->V];
}


void Graph::printNeigh(int u)
{
	for (std::list<iPair>::iterator it = this->adj_list[u].begin(); it != this->adj_list[u].end(); it++)
	{
		std::cout << "(" << it->first % this->M << ", " << it->first / this->M << ") " << this->adj_list[u].size() << " ";
	}
}


void Graph::addEdge(int u, int v, int w)
{
	this->adj_list[u].push_back(std::make_pair(v, w));
}


void Graph::removeEdge(int u, int v)
{
	if (this->adj_list[u].size() > 0)
	{
		std::list<iPair>::iterator it;

		for (it = this->adj_list[u].begin(); it != this->adj_list[u].end(); it++)
		{
			std::cout << it->first << std::endl;
			if (it->first == v)
				break;
		}

		this->adj_list[u].erase(it);
	}
}


void Graph::clear()
{
	delete[] this->adj_list;
	this->adj_list = new std::list<iPair>[this->V];
}


std::vector<int> Graph::Dijkstra(int src_x, int src_y, int dst_x, int dst_y)
{
	std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair> > minHeap;

	int src = this->M * src_y + src_x;
	int dst = this->M * dst_y + dst_x;

	std::vector<int> dist(this->V, INT32_MAX);  // Кратчайшие расстояния до каждой из вершин. Изначально равны бесконечности.
	std::vector<int> visited(this->V);          // Вектор, для каждой вершины хранящий предыдущую вершину на кратчайшем пути.

	minHeap.push(std::make_pair(0, src));       // Добавляем в кучу начальную вершину с расстоянием 0.
	dist[src] = 0;
	visited[src] = -1;

	while (!minHeap.empty())
	{
		// Достаем вершину кучи (вершину с минимальным расстоянием)
		int u = minHeap.top().second;
		minHeap.pop();

		// Если рассматриваемая вершина является конечной, то завершаем поиск
		if (u == dst)
			break;

		// Рассматриваем соседей вершины u
		for (std::list<iPair>::iterator it = this->adj_list[u].begin(); it != this->adj_list[u].end(); it++)
		{
			// Достаем идентификатор вершины v и вес ребра между u и v
			int v = it->first;
			int weight = it->second;

			// Если новое полученное расстояние ниже для рассматриваемой вершины, то это значит что нашелся новый кратчайший путь до нее.
			// Поэтому обновляем значения в таблице расстояний.
			if (dist[u] + weight < dist[v])
			{
				dist[v] = dist[u] + weight;                // Обновляем значение в таблице расстояний.
				visited[v] = u;                            // Ставим вершину u как предыдушую для вершины v.
				minHeap.push(std::make_pair(dist[v], v));  // Кладем вершину с новым кратчайшим путем в кучу.
			}
		}
	}

	// Возвращаем таблицу смежных вершин на кратчайшем пути.
	return visited;
}