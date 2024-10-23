#include <iostream>
#include <climits> // Dla stałej INT_MAX
using namespace std;

int **graf; // Macierz sąsiedztwa grafu
int ***dp;  // Tablica dynamiczna dp
int n; // Liczba wierzchołków

// Funkcja pomocnicza do znajdowania minimalnej wartości
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Funkcja rekurencyjna TSP
int tsp(int odwiedzone[], int pozycja, int liczbaOdwiedzonych) {
    // Jeśli odwiedziliśmy wszystkie wierzchołki, wracamy do początkowego wierzchołka 0
    if (liczbaOdwiedzonych == n) {
        // Sprawdzamy, czy istnieje połączenie powrotne do wierzchołka startowego (0)
        return graf[pozycja][0] > 0 ? graf[pozycja][0] : INT_MAX;
    }

    // Sprawdzamy, czy wynik został już obliczony
    if (dp[pozycja][0][liczbaOdwiedzonych] != -1) {
        return dp[pozycja][0][liczbaOdwiedzonych];
    }

    int minCost = INT_MAX;

    // Próbujemy przejść do każdego wierzchołka, który nie został jeszcze odwiedzony
    for (int next = 0; next < n; next++) {
        if (!odwiedzone[next] && graf[pozycja][next] > 0) { // Sprawdzamy, czy wierzchołek next nie został odwiedzony
            odwiedzone[next] = 1; // Zaznaczamy wierzchołek next jako odwiedzony
            int tempCost = tsp(odwiedzone, next, liczbaOdwiedzonych + 1); // Rekurencyjne wywołanie TSP dla nowego wierzchołka
            if (tempCost != INT_MAX) {
                minCost = min(minCost, graf[pozycja][next] + tempCost); // Minimalizujemy koszt
            }
            odwiedzone[next] = 0; // Cofamy zaznaczenie
        }
    }

    // Zapisujemy wynik do tablicy dp
    dp[pozycja][0][liczbaOdwiedzonych] = minCost;

    return minCost;
}

int main() {
    // Wczytujemy liczbę wierzchołków
    cout << "Podaj liczbe wierzcholkow (n): ";
    cin >> n;

    // Alokacja pamięci dla macierzy sąsiedztwa grafu
    graf = new int*[n];
    for (int i = 0; i < n; i++) {
        graf[i] = new int[n];
    }

    // Wczytujemy macierz sąsiedztwa (koszty przejścia między wierzchołkami)
    cout << "Podaj macierz grafu (" << n << "x" << n << "): " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graf[i][j];
        }
    }

    // Alokacja pamięci dla tablicy dp
    dp = new int**[n];
    for (int i = 0; i < n; i++) {
        dp[i] = new int*[n];
        for (int j = 0; j < n; j++) {
            dp[i][j] = new int[n + 1];
            for (int k = 0; k <= n; k++) {
                dp[i][j][k] = -1; // Inicjalizacja wartości dp jako nieobliczonych
            }
        }
    }

    // Dynamiczna alokacja dla tablicy odwiedzone
    int* odwiedzone = new int[n](); // Alokujemy tablicę i inicjalizujemy ją zerami
    odwiedzone[0] = 1; // Zaczynamy od wierzchołka 0, więc jest odwiedzony

    // Uruchamiamy algorytm dla wierzchołka początkowego 0
    int wynik = tsp(odwiedzone, 0, 1); // Startujemy od wierzchołka 0 z jednym odwiedzonym wierzchołkiem

    // Wyświetlamy wynik
    if (wynik == INT_MAX) {
        cout << "Nie ma mozliwej trasy obejmujacej wszystkie wierzcholki." << endl;
    } else {
        cout << "Minimalny koszt trasy: " << wynik << endl;
    }

    // Zwalnianie dynamicznie zaalokowanej pamięci
    for (int i = 0; i < n; i++) {
        delete[] graf[i];
    }
    delete[] graf;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            delete[] dp[i][j];
        }
        delete[] dp[i];
    }
    delete[] dp;

    delete[] odwiedzone; // Zwolnienie tablicy odwiedzone

    return 0;
}
