#include "Graph.h"
#include <chrono>

void menu() {
    std::cout << "Menu:\n";
    std::cout << "1. Wczytaj z pliku\n";
    std::cout << "2. Wygeneruj graf losowo\n";
    std::cout << "3. Wyświetl graf (macierzowo/listowo)\n";
    std::cout << "4. Algorytm Dijkstry (macierzowo/listowo)\n";
    std::cout << "5. Wyjdź\n";
}

int main() {
    Graph graph(0);
    int choice;

    do {
        menu();
        std::cout << "Wybierz opcję: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string filename;
                std::cout << "Podaj nazwę pliku: ";
                std::cin >> filename;
                graph.loadFromFile(filename);
                break;
            }
            case 2: {
                int vertices, density;
                std::cout << "Podaj liczbę wierzchołków: ";
                std::cin >> vertices;
                std::cout << "Podaj gęstość grafu (w %): ";
                std::cin >> density;
                graph.generateRandomGraph(vertices, density);
                break;
            }
            case 3: {
                std::cout << "Wybierz reprezentację (1 - macierzowa, 2 - listowa): ";
                int repChoice;
                std::cin >> repChoice;
                if (repChoice == 1) {
                    graph.displayMatrix();
                } else {
                    graph.displayList();
                }
                break;
            }
            case 4: {
                int start, end;
                std::cout << "Podaj wierzchołek początkowy: ";
                std::cin >> start;
                std::cout << "Podaj wierzchołek końcowy: ";
                std::cin >> end;

                std::cout << "Wybierz reprezentację (1 - macierzowa, 2 - listowa): ";
                int repChoice;
                std::cin >> repChoice;

                if (repChoice == 1) {
                    auto start_time = std::chrono::high_resolution_clock::now();
                    graph.dijkstraMatrix(start, end);
                    auto end_time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> elapsed = end_time - start_time;
                    std::cout << "Czas wykonania (macierzowa): " << elapsed.count() << " sekund\n";
                } else {
                    auto start_time = std::chrono::high_resolution_clock::now();
                    graph.dijkstraList(start, end);
                    auto end_time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> elapsed = end_time - start_time;
                    std::cout << "Czas wykonania (listowa): " << elapsed.count() << " sekund\n";
                }
                break;
            }
            case 5:
                std::cout << "Zamykanie programu.\n";
                break;
            default:
                std::cout << "Nieprawidłowa opcja. Spróbuj ponownie.\n";
        }
    } while (choice != 5);

    return 0;
}
