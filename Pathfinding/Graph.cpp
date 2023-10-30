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

	std::vector<int> dist(this->V, INT32_MAX);  // ���������� ���������� �� ������ �� ������. ���������� ����� �������������.
	std::vector<int> visited(this->V);          // ������, ��� ������ ������� �������� ���������� ������� �� ���������� ����.

	minHeap.push(std::make_pair(0, src));       // ��������� � ���� ��������� ������� � ����������� 0.
	dist[src] = 0;
	visited[src] = -1;

	while (!minHeap.empty())
	{
		// ������� ������� ���� (������� � ����������� �����������)
		int u = minHeap.top().second;
		minHeap.pop();

		// ���� ��������������� ������� �������� ��������, �� ��������� �����
		if (u == dst)
			break;

		// ������������� ������� ������� u
		for (std::list<iPair>::iterator it = this->adj_list[u].begin(); it != this->adj_list[u].end(); it++)
		{
			// ������� ������������� ������� v � ��� ����� ����� u � v
			int v = it->first;
			int weight = it->second;

			// ���� ����� ���������� ���������� ���� ��� ��������������� �������, �� ��� ������ ��� ������� ����� ���������� ���� �� ���.
			// ������� ��������� �������� � ������� ����������.
			if (dist[u] + weight < dist[v])
			{
				dist[v] = dist[u] + weight;                // ��������� �������� � ������� ����������.
				visited[v] = u;                            // ������ ������� u ��� ���������� ��� ������� v.
				minHeap.push(std::make_pair(dist[v], v));  // ������ ������� � ����� ���������� ����� � ����.
			}
		}
	}

	// ���������� ������� ������� ������ �� ���������� ����.
	return visited;
}