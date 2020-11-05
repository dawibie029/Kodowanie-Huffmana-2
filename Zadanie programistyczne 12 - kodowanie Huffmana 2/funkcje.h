#ifndef FUNKCJE_H
#define FUNKCJE_H
#include "struktury.h"
#include <list>
#include <string>
#include <vector>
#include <map>
#include <utility>
using namespace std;
bool odczytaj_odkodowane(const string& adres, vector<wierzcholek>& wierzcholki, string& kod);
wierzcholek zbuduj_drzewo(vector<wierzcholek>& wierzcholki);
void zakoduj(wierzcholek& w);
vector<pair<char, string>> stworz_pary(wierzcholek w);
void konwertuj(string& tekst, const vector<pair<char, string>>& kody);
void znak_na_kod(std::string& tekst, const std::string& co_zmienic, const std::string& na_co_zmienic);
void stworz_kod(wierzcholek* w, const string& kod);
bool sortuj_wierzcholki(wierzcholek a, wierzcholek b);
#endif
