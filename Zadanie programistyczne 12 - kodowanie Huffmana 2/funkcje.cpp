#include "funkcje.h"
#include "struktury.h"
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;

/**
	* Funkcja odczytuj�ca z pliku tekst oraz konwertuj�ca go na wektor wierzcho�k�w zawieraj�cych znak i liczb� jego wyst�pie� w tek�cie
	* Parametry przekazywane przez referencj�
	* @param adres - adres pliku tekstowego
	* @param wierzcholki - wektor wierzcho�k�w
	* @param kod - niezmieniona zawarto�� pliku tekstowego - domy�lnie tekst, kt�ry b�dzie kompresowany przez kodowanie Huffmana
	* @return true je�li uda si� otworzy� plik. W przypadku niepowodzenia warto�� false
*/
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
	* Funkcja tworz�ca drzewo binarne
	* Parametr przekazywany przez referencj�
	* @param wierzcholki - wektor wierzcho�k�w utworzonych w funkcji odczytaj_odkodowane
	* @return pojedynczy wierzcho�ek, b�d�cy szczytem drzewa binarnego. Zawiera adresy wierzcho�k�w ni�szych, 
	* kt�re zawieraj� adresy jeszcze ni�szych, a� do wierzcho�k�w zawieraj�cych pojedyncze znaki i adresy o warto�ci nullptr
*/
wierzcholek zbuduj_drzewo(vector<wierzcholek>& wierzcholki) {
	static wierzcholek w_pomocniczy;	//**< static, poniewa� ostatni obieg funkcji nie wkroczy do p�tli for; funkcja zwraca zmienn� zmodyfikowan� w przed-ostatnim obiegu */
	static int i = 0;
	static size_t wielkosc;
	if (i == 0) {
		wielkosc = wierzcholki.size();
		wierzcholki.resize(2 * wielkosc - 1);
	}
	i++;
	sort(wierzcholki.begin(), wierzcholki.end(), sortuj_wierzcholki); /** Sortuje wektor wed�ug warunk�w podanych w sortuj_wierzcholki */
	for (size_t i = 0; i < wierzcholki.size() - 2; i++) {	/** P�tla zaczyna od dw�ch pierwszych (dzi�ki sortowaniu najmniejszych) wektor�w. 
															*   Pomija te, kt�re by�y ju� u�yte dzi�ki warto�ci ma_rodzica */
		if (!wierzcholki[i].ma_rodzica && !wierzcholki[i + 1].ma_rodzica) {
			
			w_pomocniczy.lewy = &wierzcholki[i];
			w_pomocniczy.prawy = &wierzcholki[i + 1];
			w_pomocniczy.wartosc = wierzcholki[i].wartosc + wierzcholki[i + 1].wartosc;

			wierzcholki[i].ma_rodzica = true;
			wierzcholki[i + 1].ma_rodzica = true;

			w_pomocniczy.dzieci = wierzcholki[i].dzieci + wierzcholki[i + 1].dzieci + 1;	///< ilo�� pokole� = suma pokole� z ni�szych + 1 nowe */

			wierzcholki[wielkosc++] = w_pomocniczy;
			zbuduj_drzewo(wierzcholki);
			break;
		}
	}
	return w_pomocniczy;
}
/**
	* Funkcja sortuj�ca wektor wierzcho�k�w
	* Parametr przekazywany przez warto��
	* @param a - wierzcho�ek a
	* @param b - wierzcho�ek b
	* @return true, je�eli a ma mniejsz� warto�� od b. Wyj�tkiem jest sytuacja, gdy warto�� wynosi 0.
	* Ka�dy niepusty wierzcho�ek ma warto�� r�n� od 0. Obecno�� zera wynika z warto�ci domy�lnej wierzcho�k�w niezdeklarowanych,
	* inicjowanych podczas wywo�ania funkcji vector::resize w zbuduj_drzewo.
*/
bool sortuj_wierzcholki(wierzcholek a, wierzcholek b) {
	if (a.wartosc != b.wartosc)
		if (a.wartosc == 0 || b.wartosc == 0)
			return a.wartosc > b.wartosc;
		else
			return a.wartosc < b.wartosc;
	else /** je�eli jest taka sama warto��, to w pierwszej kolejno�ci wybieramy w�z� z mniejsz� ilo�ci� dzieci*/
		return a.dzieci < b.dzieci;
}
