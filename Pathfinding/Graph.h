#pragma once
#include <vector>
#include <queue>
#include <list>


// Пара целых чисел
typedef std::pair<int, int> iPair;


class Graph
{
private:
	size_t N, M, V;              // Кол-во ребер
	std::list<iPair>* adj_list;  // Список смежностей
public:
	Graph(size_t N, size_t M);

	// Добавление двунаправленного ребра между вершинами u и v с весом w
	void addEdge(int u, int v, int w);

	void removeEdge(int u, int v);

	void clear();

	void printNeigh(int u);

	// Алгоритм A*
	std::vector<int> Dijkstra(int src_x, int src_y, int dst_x, int dst_y);
};