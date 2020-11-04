#include "funkcje.h"
#include "struktury.h"
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;

bool odczytaj_odkodowane(const string& adres, vector<wierzcholek>& wierzcholki, string& kod) {
	std::ifstream plik(adres);
	if (plik) {
		map<char, int> ilosc_znakow;
		while (!plik.eof()) {
			char znak;
			plik.get(znak);
			ilosc_znakow[znak]++;
		}
		for (auto a : ilosc_znakow) {
			wierzcholek w_pomocniczy;
			w_pomocniczy.znak = a.first;
			w_pomocniczy.wartosc = a.second;
			wierzcholki.push_back(w_pomocniczy);
		}		
		return true;
	}
	else
		return false;
}
wierzcholek zbuduj_drzewo(vector<wierzcholek>& wierzcholki) {
	wierzcholek w_pomocniczy;
	sort(wierzcholki.begin(), wierzcholki.end(), sortuj_wierzcholki);
	if (!wierzcholki[0].ma_rodzica && !wierzcholki[1].ma_rodzica) {		
		w_pomocniczy.lewy = &wierzcholki[0];
		w_pomocniczy.prawy = &wierzcholki[1];
		w_pomocniczy.wartosc = wierzcholki[0].wartosc + wierzcholki[1].wartosc;
		wierzcholki[0].ma_rodzica = true;
		wierzcholki[1].ma_rodzica = true;
		w_pomocniczy.dzieci++;
		const wierzcholek w_pomocniczy2 = w_pomocniczy;
		wierzcholki.push_back(w_pomocniczy2);
		if (wierzcholki[0].lewy == nullptr) {
			wierzcholki[wierzcholki.size() - 1].lewy->lewy = nullptr;
			wierzcholki[wierzcholki.size() - 1].lewy->prawy = nullptr;
		}
		if (wierzcholki[1].lewy == nullptr) {
			wierzcholki[wierzcholki.size() - 1].prawy->lewy = nullptr;
			wierzcholki[wierzcholki.size() - 1].prawy->prawy = nullptr;
		}
		zbuduj_drzewo(wierzcholki);
	}
	return w_pomocniczy;
}
bool sortuj_wierzcholki(wierzcholek a, wierzcholek b) {
	if (a.wartosc != b.wartosc)
		return a.wartosc < b.wartosc;
	else /** je¿eli jest taka sama wartoœæ, to w pierwszej kolejnoœci wybieramy wêzê³ z mniejsz¹ iloœci¹ dzieci*/
		return a.dzieci < b.dzieci;
}
