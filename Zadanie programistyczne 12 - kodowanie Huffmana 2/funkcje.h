#ifndef FUNKCJE_H
#define FUNKCJE_H
#include "struktury.h"
#include <list>
#include <string>
#include <vector>
#include <map>
#include <utility>
using namespace std;


/**
	* Funkcja odczytuj¹ca z pliku tekst oraz konwertuj¹ca go na wektor wierzcho³ków zawieraj¹cych znak i liczbê jego wyst¹pieñ w tekœcie
	* Parametry przekazywane przez referencjê
	* @param adres - adres pliku tekstowego
	* @param wierzcholki - wektor wierzcho³ków
	* @param kod - niezmieniona zawartoœæ pliku tekstowego - domyœlnie tekst, który bêdzie kompresowany przez kodowanie Huffmana
	* @return true jeœli uda siê otworzyæ plik. W przypadku niepowodzenia wartoœæ false
*/
bool odczytaj_odkodowane(const string& adres, vector<wierzcholek>& wierzcholki, string& kod);


/**
	* Funkcja odczytuj¹ca z pliku zakodowany tekst oraz oraz wektor par zawieraj¹cy znaki i odpowiadaj¹ce im kody
	* Parametry przekazywane przez referencjê
	* @param adres - adres pliku tekstowego
	* @param kody - wektor par zawieraj¹cy znaki i odpowiadaj¹ce im kody
	* @param kod - zakodowany tekst
	* @return true jeœli uda siê otworzyæ plik. W przypadku niepowodzenia wartoœæ false
*/
bool odczytaj_zakodowane(const string& adres, vector<pair<char, string>>& kody, string& tekst);


/**
	* Funkcja tworz¹ca drzewo binarne
	* Parametr przekazywany przez referencjê
	* @param wierzcholki - wektor wierzcho³ków utworzonych w funkcji odczytaj_odkodowane
	* @return pojedynczy wierzcho³ek, bêd¹cy szczytem drzewa binarnego. Zawiera adresy wierzcho³ków ni¿szych,
	* które zawieraj¹ adresy jeszcze ni¿szych, a¿ do wierzcho³ków zawieraj¹cych pojedyncze znaki i adresy o wartoœci nullptr
*/
wierzcholek zbuduj_drzewo(vector<wierzcholek>& wierzcholki);


/**
	* Funkcja maj¹ca na celu wype³nienie zmiennej sk³adowej kod w wierzcho³kach. Wierzcho³ki, w których znak nie wynosi '\0' otrzymaj¹ pe³ny kod Huffmana dla danego znaku.
	* G³ównym zadaniem funkcji jest wywo³anie fukncji stworz_kod dla obu ga³êzi wychodz¹cych z wierzcho³ka szczytowego.
	* Parametr przekazywany przez referencjê.
	*@param w - wierzcho³ek bêd¹cy szczytem drzewa binarnego.
*/
void zakoduj(wierzcholek& w);


/**
	* Funkcja rekurencyjna maj¹ca na celu stworzenie wektora par zawieraj¹cych znak i przypisany mu kod Huffmana
	* Parametr przekazywany przez referencjê
	*@param w - wierzcho³ek bêd¹cy szczytem drzewa binarnego
*/
vector<pair<char, string>> stworz_pary(const wierzcholek& w);


/**
	* Funkcja maj¹ca na celu przekonwertowanie oryginalnego tekstu na odpowiadaj¹cy mu kod Huffmana
	* Parametry przekazywany przez referencjê
	* @param tekst - oryginalny tekst
	* @param kody - wektor par zawieraj¹cy znaki oraz odpowiadaj¹ce im kody
*/
void konwertuj(string& tekst, const vector<pair<char, string>>& kody, const bool& zakoduj);


/**
	* Funkcja zamieniaj¹ca poszczególne znaki na odpowiadaj¹ce im kody
	* @param tekst - oryginalny tekst
	* @param co_zmienic - ³añcuch znaków (lub char przekonwertowany na string) który ma byæ podmieniony
	* @param na_co_zmienic - ³añcuch znaków (lub char przekonwertowany na string) na który podmieniony ma byæ co_zmienic
*/
void znak_na_kod(string& tekst, const string& co_zmienic, const string& na_co_zmienic);


/**
	* Funkcja zamieniaj¹ca poszczególne kody na odpowiadaj¹ce im znaki. Dzia³a d³u¿ej ni¿ funkcja znak_na_kod ze wzglêdu bezpieczeñstwa -
	* funkcja znak_na_kod z podmienionymi parametrami mog³a np. z kodu 1100 wyci¹gn¹æ kod 10 (za³ó¿my, ¿e 'a') daj¹c 1a0, po czym wyœwietla³a b³¹d
	* nie mog¹c znaleŸæ odpowiedników kodu 1 oraz 0, które oczywiœcie nie istnia³y. Funkcja kod_na_znak sprawdza znaki po kolei zapobiegaj¹c takiej sytuacji.
	* @param tekst - zakodowany tekst.
	* @param kody - wektor par zawieraj¹cych znaki i odpowiadaj¹ce im kody.
*/
void kod_na_znak(string& tekst, const vector<pair<char, string>>& kody);


/**
	* Funkcja rekurencyjna, w której ma miejsce faktyczne generowanie kodu Huffmana. Wierzcho³ek z lewej otrzymuje 0, a z prawej 1, dopóki funkcja nie dotrze
	* do wierzcho³ka, którego wartoœæ zmiennej sk³adowej dzieci wynosi 0.
	* Parametr w przekazywany przez adres, kod_rodzica przekazywany przez referencjê.
	*param w - adres wierzcho³ka.
	*param kod_rodzica - kod, który ma wêzê³ wy¿szy. Dla wêz³ów górnych domyœlna wartoœæ to "".
*/
void stworz_kod(wierzcholek* w, const string& kod);


/**
	* Funkcja sortuj¹ca wektor wierzcho³ków
	* Parametr przekazywany przez wartoœæ
	* @param a - wierzcho³ek a
	* @param b - wierzcho³ek b
	* @return true, je¿eli a ma mniejsz¹ wartoœæ od b. Wyj¹tkiem jest sytuacja, gdy wartoœæ wynosi 0.
	* Ka¿dy niepusty wierzcho³ek ma wartoœæ ró¿n¹ od 0. Obecnoœæ zera wynika z wartoœci domyœlnej wierzcho³ków niezdeklarowanych,
	* inicjowanych podczas wywo³ania funkcji vector::resize w zbuduj_drzewo.
*/
bool sortuj_wierzcholki(const wierzcholek& a, const wierzcholek& b);


/**
	* Funkcja maj¹ca na celu zapisaæ tekst do pliku.
	* @param adres - adres pliku
	* @param kod - tekst, który zostanie zapisany w pliku
	* @return true, jeœli uda siê otworzyæ plik. W przypadku niepowodzenia false.
*/
bool zapisz(const string& adres, string kod);


/**
	* Funkcja ³¹cz¹ca zakodowany tekst, oraz wektor zawieraj¹cy znaki i odpowiadaj¹ce im wartoœci w jedn¹ zmienn¹ tekstow¹.
	* Parametry przekazywane przez referencje.
	* @param kod - zakodowany tekst.
	* @param pary - wektor znaków i wartoœci.
	* @param str jedna zmienna zawieraj¹ca tekst oraz wypisane pary.
*/
void polacz(const string& kod, const vector<pair<char, string>>& pary, string& str);


/**
	* Funkcja bêd¹ca baz¹ funkcji widoku interakcja. Analizuje wprowadzone dane i poœredniczy pomiêdzy widokiem a modelem
	* wywo³uj¹c funkcjê algorytm_kodowania_dekodowania.
	* @param argc - iloœæ elementów tablicy argv.
	* @param argv - tablica zawieraj¹ca dane wprowadzone w wierszu poleceñ.
	* @param adres_wejscia - adres pliku wejsciowego
	* @param adres_wyjscia - adres pliku wyjsciowego
	* @param wejscie - przyjmie wartoœæ true, je¿eli wprowadzono plik wejœciowy.
	* @param wyjscie - przyjmie wartoœæ true, je¿eli wprowadzono plik wejœciowy.
	* @param kodowanie - przyjmie wartoœæ true, je¿eli wprowadzono argument "-c".
	* @param dekodowanie - przyjmie wartoœæ true, je¿eli wprowadzono argument "-d".
	* @return zwraca liczbê naturaln¹ z przedzia³u domkniêtego od -4 do 1, wy³¹czaj¹c zero
	* kody oznaczaj¹ odpowiednio:
	* -4 : brak pliku wejœcia/wyjœcia (skutkuje odpowiednim komunikatem w funkcji interakcja i zwróceniem przez ni¹ wartoœci false).
	* -3 : wprowadzono argument "-c" i "-d" jednoczeœnie (skutkuje odpowiednim komunikatem w funkcji interakcja i zwróceniem przez ni¹ wartoœci false).
	* -2 : odpowiednie argumenty, ale b³¹d funkcji dekoduj¹cej (jak wy¿ej)
	* -1 : odpowiednie argumenty, ale b³¹d funkcji dekoduj¹cej (jak wy¿ej)
	*  1 : funkcja dekoduj¹ca zwróci³a true. (skutkuje odpowiednim komunikatem w funkcji interakcja i zwróceniem przez ni¹ wartoœci true).
	*  2 : funkcja koduj¹ca zwróci³a true. (skutkuje odpowiednim komunikatem w funkcji interakcja i zwróceniem przez ni¹ wartoœci true).
*/
short logika_interakcji(int argc, char* argv[], string& adres_wejscia, string& adres_wyjscia, bool& wejscie, bool& wyjscie,
	bool& kodowanie, bool& dekodowanie);


/**
	* Funkcja, która wywo³uje kolejno odpowiednie funkcje w celu przeprowadzenia kodowania Huffmana.
	* @param adreswe - adres pliku wejœciowego.
	* @param adreswy - adres pliku wyjœciowego.
	* @return zwraca true, je¿eli uda siê zapisaæ kod w odpowiednim pliku. W przeciwnym wypadku false.
*/
bool algorytm_zakodowania(const string& adreswe, const string& adreswy);


/**
	* Funkcja, która wywo³uje kolejno odpowiednie funkcje w celu odkodowania zakodowanego tekstu.
	* @param adreswe - adres pliku wejœciowego.
	* @param adreswy - adres pliku wyjœciowego.
	* @return zwraca true, je¿eli uda siê zapisaæ odkodowany tekst. W przeciwnym wypadku false.
*/
bool algorytm_odkodowania(const string& adreswe, const string& adreswy);


/**
	* Funkcja, która analizuje wprowadzone dane i na ich podstawie wywo³uje kolejne funkcje i zwraca wartoœæ wed³ug odpowiedniego kodu
	* @param adreswe - adres pliku wejsciowego
	* @param adreswy - adres pliku wyjsciowego
	* @param wejscie - przyjmie wartoœæ true, je¿eli wprowadzono plik wejœciowy.
	* @param wyjscie - przyjmie wartoœæ true, je¿eli wprowadzono plik wejœciowy.
	* @param kodowanie - przyjmie wartoœæ true, je¿eli wprowadzono argument "-c".
	* @param dekodowanie - przyjmie wartoœæ true, je¿eli wprowadzono argument "-d".
	* @return zwraca wartoœæ wed³ug kodu zdefiniowanego przy funkcji logika_interakcji
*/
short algorytm_kodowania_dekodowania(const string& adreswe, const string& adreswy,
	const bool& wejscie, const bool& wyjscie, const bool& kodowanie, const bool& dekodowanie);
#endif
