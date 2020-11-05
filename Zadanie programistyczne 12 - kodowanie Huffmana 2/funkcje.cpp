#include "funkcje.h"
#include "struktury.h"
#include <map>
#include <fstream>
#include <algorithm>

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
	* Funkcja maj�ca na celu zapisa� tekst do pliku.
	* @param adres - adres pliku
	* @param kod - tekst, kt�ry zostanie zapisany w pliku
	* @return true, je�li uda si� otworzy� plik. W przypadku niepowodzenia false.
*/
bool zapisz(const string& adres, string kod) {
	ofstream plik(adres);
	if (plik) {
		plik << kod;
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
			wierzcholki[i].b_lewy = true;
			w_pomocniczy.prawy = &wierzcholki[i + 1];
			wierzcholki[i + 1].b_lewy = false;
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
	* Funkcja maj�ca na celu wype�nienie zmiennej sk�adowej kod w wierzcho�kach. Wierzcho�ki, w kt�rych znak nie wynosi '\0' otrzymaj� pe�ny kod Huffmana dla danego znaku.
	* G��wnym zadaniem funkcji jest wywo�anie fukncji stworz_kod dla obu ga��zi wychodz�cych z wierzcho�ka szczytowego.
	* Parametr przekazywany przez referencj�.
	*@param w - wierzcho�ek b�d�cy szczytem drzewa binarnego.
*/
void zakoduj(wierzcholek& w) {
	stworz_kod(w.lewy, "");
	stworz_kod(w.prawy, "");
}
/**
	* Funkcja rekurencyjna maj�ca na celu stworzenie wektora par zawieraj�cych znak i przypisany mu kod Huffmana
	* Parametr przekazywany przez referencj�
	*@param w - wierzcho�ek b�d�cy szczytem drzewa binarnego
*/
vector<pair<char, string>> stworz_pary(const wierzcholek& w) {
	static vector<pair<char, string>> wektor_pomocniczy;
	pair<char, string> para_pomocnicza;
	if (w.lewy != nullptr) {	/** Sprawdzamy tylko lewy dla oszcz�dno�ci czasu - wska�niki zawsze by�y zapisywane parami lewy-prawy, wi�c niemo�liwe jest, aby
								* przy istnieniu jednego nie istnia� drugi. Gdyby jednak tak si� zdarzy�o, b��d nast�pi� by ju� w funkcji zbuduj_drzewo */
		stworz_pary(*w.lewy);
		stworz_pary(*w.prawy);
	}
	else {
		para_pomocnicza.first = w.znak;
		para_pomocnicza.second = w.kod;
		wektor_pomocniczy.push_back(para_pomocnicza);
	}
	return wektor_pomocniczy;
}
/**
	* Funkcja rekurencyjna, w kt�rej ma miejsce faktyczne generowanie kodu Huffmana. Wierzcho�ek z lewej otrzymuje 0, a z prawej 1, dop�ki funkcja nie dotrze
	* do wierzcho�ka, kt�rego warto�� zmiennej sk�adowej dzieci wynosi 0.
	* Parametr w przekazywany przez adres, kod_rodzica przekazywany przez referencj�.
	*param w - adres wierzcho�ka.
	*param kod_rodzica - kod, kt�ry ma w�z� wy�szy. Dla w�z��w g�rnych domy�lna warto�� to "".
*/
void stworz_kod(wierzcholek *w, const string& kod_rodzica) {
	if ((*w).ma_rodzica) {
		if ((*w).b_lewy) {
			(*w).kod = kod_rodzica + "0";
		}
		else {
			(*w).kod = kod_rodzica + "1";
		}
		if ((*w).dzieci > 0) {
			stworz_kod((*w).prawy, (*w).kod);
			stworz_kod((*w).lewy, (*w).kod);
		}
	}
}
/**
	* Funkcja maj�ca na celu przekonwertowanie oryginalnego tekstu na odpowiadaj�cy mu kod Huffmana
	* Parametry przekazywany przez referencj�
	* @param tekst - oryginalny tekst
	* @param kody - wektor par zawieraj�cy znaki oraz odpowiadaj�ce im kody
*/
void konwertuj(string& tekst, const vector<pair<char, string>>& kody) {
	for (const auto& a : kody) {
		string zmienna_pomocnicza (1, a.first);
		znak_na_kod(tekst, zmienna_pomocnicza, a.second);
	}
}
/**
	* Funkcja zamieniaj�ca poszczeg�lne znaki na odpowiadaj�ce im kody
	* @param tekst - oryginalny tekst
	* @param co_zmienic - �a�cuch znak�w (lub char przekonwertowany na string) kt�ry ma by� podmieniony
	* @param na_co_zmienic - �a�cuch znak�w (lub char przekonwertowany na string) na kt�ry podmieniony ma by� co_zmienic
*/
void znak_na_kod(string& tekst, const string& co_zmienic, const string& na_co_zmienic)
{
	size_t i = 0;
	while ((i = tekst.find(co_zmienic, i)) != std::string::npos) {
		tekst.replace(i, co_zmienic.length(), na_co_zmienic);
		i += na_co_zmienic.length(); 
	}
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
	else /** je�eli jest taka sama warto��, to w pierwszej kolejno�ci wybieramy w�z� z mniejsz� ilo�ci� dzieci */
		return a.dzieci < b.dzieci;
}
/**
	* Funkcja ��cz�ca zakodowany tekst, oraz wektor zawieraj�cy znaki i odpowiadaj�ce im warto�ci w jedn� zmienn� tekstow�.
	* Parametry przekazywane przez referencje.
	* @param kod - zakodowany tekst.
	* @param pary - wektor znak�w i warto�ci.
	* @return jedna zmienna zawieraj�ca tekst oraz wypisane pary.
*/
/*string polacz(const string& kod, const vector<pair<char, string>>& pary, string& str) {
	string zmienna_pomocnicza;
	zmienna_pomocnicza = kod;
	zmienna_pomocnicza += "\n";
	for (auto para : pary) {
		zmienna_pomocnicza += para.first + " - ";
		zmienna_pomocnicza += para.second + "\n";
	}
	return zmienna_pomocnicza;
}*/
void polacz(const string& kod, const vector<pair<char, string>>& pary, string& str) {
	str = kod;
	str += "\n";
	for (auto para : pary) {
		str += para.first + " - ";
		str += para.second + "\n";
	}
	
}