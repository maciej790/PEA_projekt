// tsp.cpp
#include "tsp.h"

int **graf; // Macierz sąsiedztwa grafu
int ***dp;  // Tablica dynamiczna dp
int n;      // Liczba wierzchołków

// Funkcja pomocnicza do znajdowania minimalnej wartości
int min(int a, int b)
{
    return (a < b) ? a : b;
}

// Funkcja rekurencyjna TSP
int tsp(int odwiedzone[], int pozycja, int liczbaOdwiedzonych)
{
    // Jeśli odwiedziliśmy wszystkie wierzchołki, wracamy do początkowego wierzchołka 0
    if (liczbaOdwiedzonych == n)
    {
        return graf[pozycja][0] > 0 ? graf[pozycja][0] : INT_MAX;
    }

    // Sprawdzamy, czy wynik został już obliczony
    if (dp[pozycja][0][liczbaOdwiedzonych] != -1)
    {
        return dp[pozycja][0][liczbaOdwiedzonych];
    }

    int minCost = INT_MAX;

    // Próbujemy przejść do każdego wierzchołka, który nie został jeszcze odwiedzony
    for (int next = 0; next < n; next++)
    {
        if (!odwiedzone[next] && graf[pozycja][next] > 0)
        {
            odwiedzone[next] = 1;                                         // Zaznaczamy wierzchołek next jako odwiedzony
            int tempCost = tsp(odwiedzone, next, liczbaOdwiedzonych + 1); // Rekurencyjne wywołanie TSP
            if (tempCost != INT_MAX)
            {
                minCost = min(minCost, graf[pozycja][next] + tempCost); // Minimalizujemy koszt
            }
            odwiedzone[next] = 0; // Cofamy zaznaczenie
        }
    }

    // Zapisujemy wynik do tablicy dp
    dp[pozycja][0][liczbaOdwiedzonych] = minCost;

    return minCost;
}
