#include "funkcje.h"
#include "struktury.h"
#include <map>
#include <fstream>
using namespace std;
/*bool odczytaj_zakodowane(const std::string& adres, std::map<char, std::string>& mapa_wartosci, std::string& kod) {
	std::ifstream plik(adres);
	if (plik) {
		getline(plik, kod, ';');
			while (!plik.eof()) {
				char znak;
				std::string wartosc;
				plik.get(znak);	//*Pobiera znak
				plik.get();	//	Pomija symbol oddzielaj¹cy znaki od definicji (dla pliku wejœciowego dowolny, domyœlnie (oraz w pliku wyjœciowym) u¿ywany jest przecinek)
				getline(plik, wartosc, ',');	//	Wczytuje wartoœæ znaku wczytanego w linijce wy¿ej. Oddzielaj¹c kod od nastêpnego znaku konieczne jest ju¿ u¿ycie przecinka.
				mapa_wartosci[znak] = wartosc;
			}
		return true;
	}
	else
		return false;
}*/
bool odczytaj_odkodowane(const string& adres, list<wierzcholek>& wierzcholki, string& kod) {
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
wierzcholek zbuduj_drzewo(list<wierzcholek>& wierzcholki) {
	wierzcholek w_pomocniczy;
	for (auto a : wierzcholki) {
		if (a.has_parent == false) {
			wierzcholki.sort([](wierzcholek a, wierzcholek b) {return a.wartosc < b.wartosc; });
			w_pomocniczy.lewy = &a;
			w_pomocniczy.prawy = &a + 1;
			//a.has_parent = true;	ZROBIC ZEBY DZIALALO
			//*(&a + 1).has_parent = true;
			wierzcholki.push_back(w_pomocniczy);
			zbuduj_drzewo(wierzcholki);
		}
		else
			break;
	}
	return w_pomocniczy;
}
