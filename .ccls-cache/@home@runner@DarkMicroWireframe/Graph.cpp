#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

// Struktura grafu
struct Graph {
  int V;
  std::vector<std::vector<int>> adjMatrix;
  std::vector<std::vector<std::pair<int, int>>> adjList;

  // Konstruktor
  Graph(int vertices) : V(vertices) {
    initializeMatrix();
    initializeList();
  }

  // Inicjalizacja macierzy sąsiedztwa
  void initializeMatrix() {
    adjMatrix.resize(V, std::vector<int>(V, std::numeric_limits<int>::max()));
    for (int i = 0; i < V; ++i) {
      adjMatrix[i][i] = 0;
    }
  }

  // Inicjalizacja listy sąsiedztwa
  void initializeList() { adjList.resize(V); }

  // Dodawanie krawędzi do grafu (macierz)
  void addEdgeMatrix(int src, int dest, int weight) {
    adjMatrix[src][dest] = weight;
  }

  // Dodawanie krawędzi do grafu (lista)
  void addEdgeList(int src, int dest, int weight) {
    adjList[src].push_back({dest, weight});
  }

  // Generowanie losowego grafu o zadanej gęstości
  void generateRandomGraph(int density) {
    int edges = (density * V * (V - 1)) / 200; // Obliczenie liczby krawędzi
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < edges; ++i) {
      int src = i % V;        // Losowe źródło
      int dest = (i + 1) % V; // Losowy cel
      int weight = dis(gen);  // Losowa waga (od 1 do 100)
      addEdgeMatrix(src, dest, weight);
      addEdgeList(src, dest, weight);
    }
  }

  // Algorytm Dijkstry dla reprezentacji macierzowej
  void dijkstraMatrix(int start, int end) {
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

      if (dist[u] == std::numeric_limits<int>::max())
        break;

      sptSet[u] = true;

      for (int v = 0; v < V; ++v) {
        if (!sptSet[v] && adjMatrix[u][v] != std::numeric_limits<int>::max() &&
            dist[u] + adjMatrix[u][v] < dist[v]) {
          dist[v] = dist[u] + adjMatrix[u][v];
        }
      }
    }

    // Wynik algorytmu
    if (dist[end] != std::numeric_limits<int>::max()) {
      std::cout << "Najkrótsza ścieżka od " << start << " do " << end
                << " wynosi " << dist[end] << "\n";
    } else {
      std::cout << "Brak ścieżki od " << start << " do " << end << "\n";
    }
  }

  // Algorytm Dijkstry dla reprezentacji listowej
  void dijkstraList(int start, int end) {
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;

    pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();

      if (u == end)
        break;

      for (const auto &neighbor : adjList[u]) {
        int v = neighbor.first;
        int weight = neighbor.second;

        if (dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
          pq.push({dist[v], v});
        }
      }
    }

    // Wynik algorytmu
    if (dist[end] != std::numeric_limits<int>::max()) {
      std::cout << "Najkrótsza ścieżka od " << start << " do " << end
                << " wynosi " << dist[end] << "\n";
    } else {
      std::cout << "Brak ścieżki od " << start << " do " << end << "\n";
    }
  }
};

int main() {
  // Parametry do badań
  std::vector<int> liczbaWierzcholkow = {20, 50, 100, 200,
                                         500}; // 5 różnych liczb wierzchołków
  std::vector<double> gestosc = {
      0.25, 0.5, 0.75};     // Gęstości grafu: ok. 25%, ok. 50%, ok. 75%
  int liczbaInstancji = 20; // Minimalna liczba instancji

  // Pętle do przeprowadzenia badań
  for (auto wierzcholki : liczbaWierzcholkow) {
    for (auto dens : gestosc) {
      double sumaCzasowMacierz = 0.0;
      double sumaCzasowLista = 0.0;

      for (int i = 0; i < liczbaInstancji; ++i) {
        Graph graf(wierzcholki);
        graf.generateRandomGraph(static_cast<int>(dens * 100));

        // Pomiar czasu dla reprezentacji macierzowej
        auto start_time = std::chrono::high_resolution_clock::now();
        graf.dijkstraMatrix(0, wierzcholki - 1);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;
        sumaCzasowMacierz += elapsed.count();

        // Pomiar czasu dla reprezentacji listowej
        start_time = std::chrono::high_resolution_clock::now();
        graf.dijkstraList(0, wierzcholki - 1);
        end_time = std::chrono::high_resolution_clock::now();
        elapsed = end_time - start_time;
        sumaCzasowLista += elapsed.count();
      }

      // Obliczenie średniego czasu wykonania dla każdej reprezentacji
      double sredniCzasMacierz = sumaCzasowMacierz / liczbaInstancji;
      double sredniCzasLista = sumaCzasowLista / liczbaInstancji;

      // Wyświetlenie wyników
      std::cout << "Badania dla " << wierzcholki << " wierzcholkow, gestosc "
                << (dens * 100) << "%:\n";
      std::cout << "Sredni czas wykonania (macierzowa): " << std::fixed
                << std::setprecision(6) << sredniCzasMacierz << " sekund\n";
      std::cout << "Sredni czas wykonania (listowa): " << std::fixed
                << std::setprecision(6) << sredniCzasLista << " sekund\n\n";
    }
  }

  return 0;
}
