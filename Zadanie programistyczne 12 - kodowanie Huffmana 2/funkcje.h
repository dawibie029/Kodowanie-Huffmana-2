#ifndef FUNKCJE_H
#define FUNKCJE_H
#include "struktury.h"
#include <list>
#include <string>
#include <vector>
#include <map>
using namespace std;
bool odczytaj_odkodowane(const string& adres, vector<wierzcholek>& wierzcholki, string& kod);
wierzcholek zbuduj_drzewo(vector<wierzcholek>& wierzcholki);
void zakoduj(wierzcholek& w);
void stworz_kod(wierzcholek* w, const string& kod);
bool sortuj_wierzcholki(wierzcholek a, wierzcholek b);
#endif
