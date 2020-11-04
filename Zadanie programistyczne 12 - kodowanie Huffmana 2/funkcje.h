#ifndef FUNKCJE_H
#define FUNKCJE_H
#include "struktury.h"
#include <list>
#include <string>
#include <vector>
using namespace std;
bool odczytaj_odkodowane(const string& adres, vector<wierzcholek>& wierzcholki, string& kod);
wierzcholek zbuduj_drzewo(vector<wierzcholek>& wierzcholki);
bool sortuj_wierzcholki(wierzcholek a, wierzcholek b);
#endif
