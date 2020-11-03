#include "funkcje.h"
#include "struktury.h"
#include <vector>
#include <map>
#include <list>
#include <string>
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
				plik.get();	//	Pomija symbol oddzielaj�cy znaki od definicji (dla pliku wej�ciowego dowolny, domy�lnie (oraz w pliku wyj�ciowym) u�ywany jest przecinek)
				getline(plik, wartosc, ',');	//	Wczytuje warto�� znaku wczytanego w linijce wy�ej. Oddzielaj�c kod od nast�pnego znaku konieczne jest ju� u�ycie przecinka.
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
