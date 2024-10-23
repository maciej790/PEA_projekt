// main.cpp
#include <iostream>
#include "tsp.h"
#include "random_graph.h"
#include <iostream>
#include <cstdlib> // dla rand() i srand()
#include <ctime>   // dla time()

using namespace std;

int main()
{

    srand(time(0));

    int rozmiary[5] = {50, 100, 200, 500, 600};

    for (int rozmiar = 0; rozmiar < 5; rozmiar++)
    {
        float czasCalkowity = 0;

        for (int pomiar = 0; pomiar < 10; pomiar++)
        {
            // Losowanie grafu
            n = rozmiary[rozmiar];
            graf = losujGraf(n);
            dp = new int **[n];
            for (int i = 0; i < n; i++)
            {
                dp[i] = new int *[n];
                for (int j = 0; j < n; j++)
                {
                    dp[i][j] = new int[n + 1];
                    for (int k = 0; k <= n; k++)
                    {
                        dp[i][j][k] = -1; // Inicjalizacja wartości dp jako nieobliczonych
                    }
                }
            }

            // Dynamiczna alokacja dla tablicy odwiedzone
            int *odwiedzone = new int[n](); // Alokujemy tablicę i inicjalizujemy ją zerami
            odwiedzone[0] = 1;              // Zaczynamy od wierzchołka 0, więc jest odwiedzony
            // cout << "TSP dla grafu o rozmiarze " << n << ": " << endl;
            //  Pomiar czasu rozpoczęcia algorytmu
            auto start = high_resolution_clock::now();

            // Uruchamiamy algorytm dla wierzchołka początkowego 0
            int wynik = tsp(odwiedzone, 0, 1); // Startujemy od wierzchołka 0 z jednym odwiedzonym wierzchołkiem

            // Pomiar czasu zakończenia algorytmu
            auto stop = high_resolution_clock::now();

            // Obliczenie czasu wykonania algorytmu
            auto duration = duration_cast<milliseconds>(stop - start);
            czasCalkowity = czasCalkowity + duration.count();

            // Wyświetlamy wynik
            // if (wynik == INT_MAX)
            // {
            //     cout << "    Nie ma mozliwej trasy obejmujacej wszystkie wierzcholki." << endl;
            // }
            // else
            // {
            //     cout << "    Minimalny koszt trasy: " << wynik << endl;
            // }

            // Wyświetlenie czasu wykonania algorytmu
            // cout << "Czas wykonania algorytmu: " << duration.count() << " ms" << endl;

            // Zwalnianie dynamicznie zaalokowanej pamięci
            for (int i = 0; i < n; i++)
            {
                delete[] graf[i];
            }
            delete[] graf;

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    delete[] dp[i][j];
                }
                delete[] dp[i];
            }
            delete[] dp;

            delete[] odwiedzone; // Zwolnienie tablicy odwiedzone
        }

        cout << "Czas średni dla n: " << n << " to: " << czasCalkowity / 10 << " ms" << endl;
    }

    return 0;
}
