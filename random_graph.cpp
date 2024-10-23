// random_graph.cpp
#include <iostream>
#include <cstdlib> // dla rand() i srand()
#include <ctime>   // dla time()
#include "random_graph.h"

using namespace std;

int** losujGraf(int n) {
    // Alokacja pamięci dla macierzy sąsiedztwa
    int** graf = new int*[n];
    for (int i = 0; i < n; i++) {
        graf[i] = new int[n];
    }

    // Inicjalizacja macierzy sąsiedztwa
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graf[i][j] = 0; // Koszt przejścia do samego siebie = 0
            } else {
                // Losowanie krawędzi, każda krawędź zawsze istnieje
                int waga = rand() % 99 + 1; // Losowa waga od 1 do 99
                graf[i][j] = waga;
                graf[j][i] = waga; // Ustawienie krawędzi w drugą stronę, aby graf był nieskierowany
            }
        }
    }

    return graf;
}
