#ifndef GRAPH_H
#define GRAPH_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <sstream>
#include <vector>

struct Edge {
  int src, dest, weight;
};

class Graph {
public:
  Graph(int vertices);
  void addEdge(int src, int dest, int weight);
  void generateRandomGraph(int vertices, int density);
  void loadFromFile(const std::string &filename);
  void displayMatrix();
  void displayList();
  void dijkstraMatrix(int start, int end);
  void dijkstraList(int start, int end);

private:
  int V;
  std::vector<std::vector<int>> adjMatrix;
  std::vector<std::list<std::pair<int, int>>> adjList;
  void initializeMatrix();
  void initializeList();
};

#endif