#include "funkcje.h"
#include "struktury.h"
#include <map>
#include <fstream>
#include <algorithm>

/**
	* Funkcja odczytuj¹ca z pliku tekst oraz konwertuj¹ca go na wektor wierzcho³ków zawieraj¹cych znak i liczbê jego wyst¹pieñ w tekœcie
	* Parametry przekazywane przez referencjê
	* @param adres - adres pliku tekstowego
	* @param wierzcholki - wektor wierzcho³ków
	* @param kod - niezmieniona zawartoœæ pliku tekstowego - domyœlnie tekst, który bêdzie kompresowany przez kodowanie Huffmana
	* @return true jeœli uda siê otworzyæ plik. W przypadku niepowodzenia wartoœæ false
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
	* Funkcja tworz¹ca drzewo binarne
	* Parametr przekazywany przez referencjê
	* @param wierzcholki - wektor wierzcho³ków utworzonych w funkcji odczytaj_odkodowane
	* @return pojedynczy wierzcho³ek, bêd¹cy szczytem drzewa binarnego. Zawiera adresy wierzcho³ków ni¿szych, 
	* które zawieraj¹ adresy jeszcze ni¿szych, a¿ do wierzcho³ków zawieraj¹cych pojedyncze znaki i adresy o wartoœci nullptr
*/
wierzcholek zbuduj_drzewo(vector<wierzcholek>& wierzcholki) {
	static wierzcholek w_pomocniczy;	//**< static, poniewa¿ ostatni obieg funkcji nie wkroczy do pêtli for; funkcja zwraca zmienn¹ zmodyfikowan¹ w przed-ostatnim obiegu */
	static int i = 0;
	static size_t wielkosc;
	if (i == 0) {
		wielkosc = wierzcholki.size();
		wierzcholki.resize(2 * wielkosc - 1);
	}
	i++;
	sort(wierzcholki.begin(), wierzcholki.end(), sortuj_wierzcholki); /** Sortuje wektor wed³ug warunków podanych w sortuj_wierzcholki */
	for (size_t i = 0; i < wierzcholki.size() - 2; i++) {	/** Pêtla zaczyna od dwóch pierwszych (dziêki sortowaniu najmniejszych) wektorów. 
															*   Pomija te, które by³y ju¿ u¿yte dziêki wartoœci ma_rodzica */
		if (!wierzcholki[i].ma_rodzica && !wierzcholki[i + 1].ma_rodzica) {
			
			w_pomocniczy.lewy = &wierzcholki[i];
			wierzcholki[i].b_lewy = true;
			w_pomocniczy.prawy = &wierzcholki[i + 1];
			wierzcholki[i + 1].b_lewy = false;
			w_pomocniczy.wartosc = wierzcholki[i].wartosc + wierzcholki[i + 1].wartosc;

			wierzcholki[i].ma_rodzica = true;
			wierzcholki[i + 1].ma_rodzica = true;

			w_pomocniczy.dzieci = wierzcholki[i].dzieci + wierzcholki[i + 1].dzieci + 1;	///< iloœæ pokoleñ = suma pokoleñ z ni¿szych + 1 nowe */

			wierzcholki[wielkosc++] = w_pomocniczy;
			zbuduj_drzewo(wierzcholki);
			break;
		}
	}
	return w_pomocniczy;
}
/**
	* Funkcja maj¹ca na celu wype³nienie zmiennej sk³adowej kod w wierzcho³kach. Wierzcho³ki, w których znak nie wynosi '\0' otrzymaj¹ pe³ny kod Huffmana dla danego znaku.
	* G³ównym zadaniem funkcji jest wywo³anie fukncji stworz_kod dla obu ga³êzi wychodz¹cych z wierzcho³ka szczytowego.
	* Parametr przekazywany przez referencjê.
	*@param w - wierzcho³ek bêd¹cy szczytem drzewa binarnego.
*/
void zakoduj(wierzcholek& w) {
	stworz_kod(w.lewy, "");
	stworz_kod(w.prawy, "");
}
vector<pair<char, string>> stworz_pary(wierzcholek w) {
	static int i = 0;
	static vector<pair<char, string>> wektor_pomocniczy;
	pair<char, string> para_pomocnicza;
	if (w.lewy != nullptr) {
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
	* Funkcja rekurencyjna, w której ma miejsce faktyczne generowanie kodu Huffmana. Wierzcho³ek z lewej otrzymuje 0, a z prawej 1, dopóki funkcja nie dotrze
	* do wierzcho³ka, którego wartoœæ zmiennej sk³adowej dzieci wynosi 0.
	* Parametr w przekazywany przez adres, kod_rodzica przekazywany przez referencjê.
	*param w - adres wierzcho³ka.
	*param kod_rodzica - kod, który ma wêzê³ wy¿szy. Dla wêz³ów górnych domyœlna wartoœæ to "".
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
void konwertuj(string& tekst, const vector<pair<char, string>>& kody) {
	for (const auto& a : kody) {
		string zmienna_pomocnicza (1, a.first);
		znak_na_kod(tekst, zmienna_pomocnicza, a.second);
	}
}
void znak_na_kod(std::string& tekst, const std::string& co_zmienic, const std::string& na_co_zmienic)
{
	size_t start_pos = 0;
	while ((start_pos = tekst.find(co_zmienic, start_pos)) != std::string::npos) {
		tekst.replace(start_pos, co_zmienic.length(), na_co_zmienic);
		start_pos += na_co_zmienic.length(); 
	}
}
/**
	* Funkcja sortuj¹ca wektor wierzcho³ków
	* Parametr przekazywany przez wartoœæ
	* @param a - wierzcho³ek a
	* @param b - wierzcho³ek b
	* @return true, je¿eli a ma mniejsz¹ wartoœæ od b. Wyj¹tkiem jest sytuacja, gdy wartoœæ wynosi 0.
	* Ka¿dy niepusty wierzcho³ek ma wartoœæ ró¿n¹ od 0. Obecnoœæ zera wynika z wartoœci domyœlnej wierzcho³ków niezdeklarowanych,
	* inicjowanych podczas wywo³ania funkcji vector::resize w zbuduj_drzewo.
*/
bool sortuj_wierzcholki(wierzcholek a, wierzcholek b) {
	if (a.wartosc != b.wartosc)
		if (a.wartosc == 0 || b.wartosc == 0)
			return a.wartosc > b.wartosc;
		else
			return a.wartosc < b.wartosc;
	else /** je¿eli jest taka sama wartoœæ, to w pierwszej kolejnoœci wybieramy wêzê³ z mniejsz¹ iloœci¹ dzieci*/
		return a.dzieci < b.dzieci;
}
