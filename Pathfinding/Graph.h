#pragma once
#include <vector>
#include <queue>
#include <list>


// ���� ����� �����
typedef std::pair<int, int> iPair;


class Graph
{
private:
	size_t N, M, V;              // ���-�� �����
	std::list<iPair>* adj_list;  // ������ ����������
public:
	Graph(size_t N, size_t M);

	// ���������� ���������������� ����� ����� ��������� u � v � ����� w
	void addEdge(int u, int v, int w);

	void removeEdge(int u, int v);

	void clear();

	void printNeigh(int u);

	// �������� A*
	std::vector<int> Dijkstra(int src_x, int src_y, int dst_x, int dst_y);
};