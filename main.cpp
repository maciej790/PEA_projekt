#include <iostream>
#include <cstdlib> // dla rand() i srand()
#include <ctime>   // dla time()
#include <climits> // dla INT_MAX
#include <fstream> // Dla operacji na plikach
#include <chrono>  // dla pomiaru czasu

using namespace std;
using namespace std::chrono;

// Zmienne globalne
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

// Funkcja do losowania grafu
int **losujGraf(int n)
{
    // Alokacja pamięci dla macierzy sąsiedztwa
    int **graf = new int *[n];
    for (int i = 0; i < n; i++)
    {
        graf[i] = new int[n];
    }

    // Inicjalizacja macierzy sąsiedztwa
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                graf[i][j] = 0; // Koszt przejścia do samego siebie = 0
            }
            else
            {
                // Losowanie krawędzi, każda krawędź zawsze istnieje
                int waga = rand() % 99 + 1; // Losowa waga od 1 do 99
                graf[i][j] = waga;
                graf[j][i] = waga; // Ustawienie krawędzi w drugą stronę, aby graf był nieskierowany
            }
        }
    }

    return graf;
}

// Funkcja do zwalniania pamięci dla grafu, dp i odwiedzonych
void zwolnijPamiec(int **graf, int ***dp, int *odwiedzone, int n)
{
    // Zwalnianie pamięci dla grafu
    for (int i = 0; i < n; i++)
    {
        delete[] graf[i];
    }
    delete[] graf;

    // Zwalnianie pamięci dla dp
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            delete[] dp[i][j];
        }
        delete[] dp[i];
    }
    delete[] dp;

    // Zwalnianie pamięci dla odwiedzonych
    delete[] odwiedzone;
}

// Funkcja do testowania algorytmu dla losowych instancji grafów
void dlaLosowychInstancji()
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

            // Pomiar czasu rozpoczęcia algorytmu
            auto start = high_resolution_clock::now();

            // Uruchamiamy algorytm dla wierzchołka początkowego 0
            int wynik = tsp(odwiedzone, 0, 1); // Startujemy od wierzchołka 0 z jednym odwiedzonym wierzchołkiem

            // Pomiar czasu zakończenia algorytmu
            auto stop = high_resolution_clock::now();

            // Obliczenie czasu wykonania algorytmu
            auto duration = duration_cast<milliseconds>(stop - start);
            czasCalkowity = czasCalkowity + duration.count();

            // Zwalnianie dynamicznie zaalokowanej pamięci
            zwolnijPamiec(graf, dp, odwiedzone, n);
        }

        cout << "Czas średni dla n: " << n << " to: " << czasCalkowity / 10 << " ms" << endl;
    }
}

// Funkcja do wczytywania grafu z pliku
int **wczytajGrafZPliku(const string &nazwaPliku, int &n)
{
    ifstream plik(nazwaPliku, ios::in);

    if (!plik.is_open())
    {
        cerr << "Blad: Nie udalo sie otworzyc pliku " << nazwaPliku << endl;
        return nullptr;
    }

    // Odczyt liczby wierzchołków
    plik >> n;

    // Alokacja pamięci dla macierzy sąsiedztwa
    int **graf = new int *[n];
    for (int i = 0; i < n; i++)
    {
        graf[i] = new int[n];
    }

    // Wczytywanie macierzy sąsiedztwa z pliku
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            plik >> graf[i][j];
        }
    }

    plik.close();
    return graf;
}

// Funkcja do testowania algorytmu dla grafu wczytanego z pliku
void dlaGrafuZPliku()
{
    graf = wczytajGrafZPliku("graf.txt", n);

    if (graf == nullptr)
    {
        return;
    }

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

    int *odwiedzone = new int[n](); // Alokujemy tablicę i inicjalizujemy ją zerami
    odwiedzone[0] = 1;              // Zaczynamy od wierzchołka 0, więc jest odwiedzony

    // Uruchamiamy algorytm dla wierzchołka początkowego 0
    int wynik = tsp(odwiedzone, 0, 1); // Startujemy od wierzchołka 0 z jednym odwiedzonym wierzchołkiem

    cout << "Minimalny koszt dla grafu z pliku: " << wynik << endl;

    // Zwalnianie dynamicznie zaalokowanej pamięci
    zwolnijPamiec(graf, dp, odwiedzone, n);
}

int main()
{

    int wybor;
    while (wybor != 3)
    {
        cout << "1. Pomiar srednich czasow dla losowych instancji" << endl;
        cout << "2. Wczytanie grafu z pliku i sprawdzenie poprawnosci programu" << endl;
        cout << "3. Wyjscie" << endl;

        cin >> wybor;

        switch (wybor)
        {
        case 1:
            dlaLosowychInstancji();
            break;

        case 2:
            dlaGrafuZPliku();
            break;

        case 3:
            return 0;
            break;

        default:
            break;
        }
    }

    return 0;
}
