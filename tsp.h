// tsp.h
#ifndef TSP_H
#define TSP_H

#include <climits> // Dla INT_MAX
#include <chrono>  // Dla pomiaru czasu
using namespace std;
using namespace std::chrono;

extern int **graf; // Macierz sąsiedztwa grafu
extern int ***dp;  // Tablica dynamiczna dp
extern int n;      // Liczba wierzchołków

// Funkcja pomocnicza do znajdowania minimalnej wartości
int min(int a, int b);

// Funkcja rekurencyjna TSP
int tsp(int odwiedzone[], int pozycja, int liczbaOdwiedzonych);

#endif // TSP_H
