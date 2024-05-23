#include "Graph.h"

Graph::Graph(int vertices) : V(vertices) {
    initializeMatrix();
    initializeList();
}

void Graph::initializeMatrix() {
    adjMatrix.resize(V, std::vector<int>(V, std::numeric_limits<int>::max()));
    for (int i = 0; i < V; ++i) {
        adjMatrix[i][i] = 0;
    }
}

void Graph::initializeList() {
    adjList.resize(V);
}

void Graph::addEdge(int src, int dest, int weight) {
    adjMatrix[src][dest] = weight;
    adjList[src].push_back({dest, weight});
}

void Graph::generateRandomGraph(int vertices, int density) {
    V = vertices;
    initializeMatrix();
    initializeList();
    int edges = (density * vertices * (vertices - 1)) / 100;
    srand(time(0));
    for (int i = 0; i < edges; ++i) {
        int src = rand() % vertices;
        int dest = rand() % vertices;
        int weight = rand() % 100 + 1;
        addEdge(src, dest, weight);
    }
}

void Graph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file.\n";
        return;
    }
    int edges;
    file >> edges >> V;
    initializeMatrix();
    initializeList();
    int src, dest, weight;
    while (file >> src >> dest >> weight) {
        addEdge(src, dest, weight);
    }
    file.close();
}

void Graph::displayMatrix() {
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (adjMatrix[i][j] == std::numeric_limits<int>::max()) {
                std::cout << "INF ";
            } else {
                std::cout << adjMatrix[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
}

void Graph::displayList() {
    for (int i = 0; i < V; ++i) {
        std::cout << i << ": ";
        for (const auto& edge : adjList[i]) {
            std::cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        std::cout << "\n";
    }
}

void Graph::dijkstraMatrix(int start, int end) {
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<bool> sptSet(V, false);
    dist[start] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        for (int i = 0; i < V; ++i) {
            if (!sptSet[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (dist[u] == std::numeric_limits<int>::max()) break;

        sptSet[u] = true;

        for (int v = 0; v < V; ++v) {
            if (!sptSet[v] && adjMatrix[u][v] != std::numeric_limits<int>::max() && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
            }
        }
    }

    if (dist[end] != std::numeric_limits<int>::max()) {
        std::cout << "Shortest path from " << start << " to " << end << " is " << dist[end] << "\n";
    } else {
        std::cout << "There is no path from " << start << " to " << end << "\n";
    }
}

void Graph::dijkstraList(int start, int end) {
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == end) break;

        for (const auto& neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[end] != std::numeric_limits<int>::max()) {
        std::cout << "Shortest path from " << start << " to " << end << " is " << dist[end] << "\n";
    } else {
        std::cout << "There is no path from " << start << " to " << end << "\n";
    }
}
