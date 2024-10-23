#ifndef GRAF_H
#define GRAF_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <sstream>
#include <vector>

// Struktura reprezentująca krawędź grafu
struct Krawedz {
  int poczatek, koniec, waga;
};

// Klasa reprezentująca graf
class Graf {
public:
  Graf(int wierzcholki);
  void dodajKrawedz(int poczatek, int koniec, int waga);
  void generujLosowyGraf(int wierzcholki, int gestosc);
  void wczytajZPliku(const std::string &nazwaPliku);
  void wyswietlMacierz();
  void wyswietlListe();
  void dijkstraMacierz(int poczatek, int koniec);
  void dijkstraLista(int poczatek, int koniec);

private:
  int liczbaWierzcholkow;                          // Liczba wierzchołków
  std::vector<std::vector<int>> macierzSasiedztwa; // Macierz sąsiedztwa
  std::vector<std::list<std::pair<int, int>>>
      listaSasiedztwa; // Lista sąsiedztwa
  void inicjalizujMacierz();
  void inicjalizujListe();
};

#endif // GRAF_H
