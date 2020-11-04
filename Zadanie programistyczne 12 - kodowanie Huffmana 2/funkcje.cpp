#include "funkcje.h"
#include "struktury.h"
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;

bool odczytaj_odkodowane(const string& adres, vector<wierzcholek>& wierzcholki, string& kod) {
	std::ifstream plik(adres);
	if (plik) {
		getline(plik, kod);
		plik.clear();
		plik.seekg(0);
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
/**


*/
wierzcholek zbuduj_drzewo(vector<wierzcholek>& wierzcholki) {
	static wierzcholek w_pomocniczy;
	static int i = 0;
	static long wielkosc;
	if (i == 0) {
		wielkosc = wierzcholki.size();
		wierzcholki.resize(2 * wielkosc - 1);
	}
	i++;
	sort(wierzcholki.begin(), wierzcholki.end(), sortuj_wierzcholki);
	for (int i = 0; i < wierzcholki.size() - 2; i++) {
		if (!wierzcholki[i].ma_rodzica && !wierzcholki[i + 1].ma_rodzica) {
			w_pomocniczy.lewy = &wierzcholki[i];
			w_pomocniczy.prawy = &wierzcholki[i + 1];
			w_pomocniczy.wartosc = wierzcholki[i].wartosc + wierzcholki[i + 1].wartosc;
			wierzcholki[i].ma_rodzica = true;
			wierzcholki[i + 1].ma_rodzica = true;		
			w_pomocniczy.dzieci = wierzcholki[i].dzieci + wierzcholki[i + 1].dzieci;
			if (wierzcholki[i].dzieci == 0)
				w_pomocniczy.dzieci++;
			if (wierzcholki[i + 1].dzieci == 0)
				w_pomocniczy.dzieci++;
			wierzcholki[wielkosc++] = w_pomocniczy;
			zbuduj_drzewo(wierzcholki);
			break;
		}
	}
	return w_pomocniczy;
}
bool sortuj_wierzcholki(wierzcholek a, wierzcholek b) {
	if (a.wartosc != b.wartosc)
		if (a.wartosc == 0 || b.wartosc == 0)
			return a.wartosc > b.wartosc;
		else
			return a.wartosc < b.wartosc;
	else /** je¿eli jest taka sama wartoœæ, to w pierwszej kolejnoœci wybieramy wêzê³ z mniejsz¹ iloœci¹ dzieci*/
		return a.dzieci < b.dzieci;
}
