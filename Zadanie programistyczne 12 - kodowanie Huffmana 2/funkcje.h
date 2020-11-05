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
bool odczytaj_zakodowane(const string& adres, vector<pair<char, string>>& kody, string& tekst);
wierzcholek zbuduj_drzewo(vector<wierzcholek>& wierzcholki);
void zakoduj(wierzcholek& w);
vector<pair<char, string>> stworz_pary(const wierzcholek& w);
void konwertuj(string& tekst, const vector<pair<char, string>>& kody, const bool& zakoduj);
void znak_na_kod(string& tekst, const string& co_zmienic, const string& na_co_zmienic);
void kod_na_znak(string& tekst, const vector<pair<char, string>>& kody);
void stworz_kod(wierzcholek* w, const string& kod);
bool sortuj_wierzcholki(const wierzcholek& a, const wierzcholek& b);
bool zapisz(const string& adres, string kod);
void polacz(const string& kod, const vector<pair<char, string>>& pary, string& str);
short logika_interakcji(int argc, char* argv[], string& adres_wejscia, string& adres_wyjscia, bool& wejscie, bool& wyjscie,
	bool& kodowanie, bool& dekodowanie);
bool algorytm_zakodowania(const string& adreswe, const string& adreswy);
bool algorytm_odkodowania(const string& adreswe, const string& adreswy);
#endif
