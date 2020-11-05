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
	* Funkcja odczytuj�ca z pliku tekst oraz konwertuj�ca go na wektor wierzcho�k�w zawieraj�cych znak i liczb� jego wyst�pie� w tek�cie
	* Parametry przekazywane przez referencj�
	* @param adres - adres pliku tekstowego
	* @param wierzcholki - wektor wierzcho�k�w
	* @param kod - niezmieniona zawarto�� pliku tekstowego - domy�lnie tekst, kt�ry b�dzie kompresowany przez kodowanie Huffmana
	* @return true je�li uda si� otworzy� plik. W przypadku niepowodzenia warto�� false
*/
bool odczytaj_odkodowane(const string& adres, vector<wierzcholek>& wierzcholki, string& kod);


/**
	* Funkcja odczytuj�ca z pliku zakodowany tekst oraz oraz wektor par zawieraj�cy znaki i odpowiadaj�ce im kody
	* Parametry przekazywane przez referencj�
	* @param adres - adres pliku tekstowego
	* @param kody - wektor par zawieraj�cy znaki i odpowiadaj�ce im kody
	* @param kod - zakodowany tekst
	* @return true je�li uda si� otworzy� plik. W przypadku niepowodzenia warto�� false
*/
bool odczytaj_zakodowane(const string& adres, vector<pair<char, string>>& kody, string& tekst);


/**
	* Funkcja tworz�ca drzewo binarne
	* Parametr przekazywany przez referencj�
	* @param wierzcholki - wektor wierzcho�k�w utworzonych w funkcji odczytaj_odkodowane
	* @return pojedynczy wierzcho�ek, b�d�cy szczytem drzewa binarnego. Zawiera adresy wierzcho�k�w ni�szych,
	* kt�re zawieraj� adresy jeszcze ni�szych, a� do wierzcho�k�w zawieraj�cych pojedyncze znaki i adresy o warto�ci nullptr
*/
wierzcholek zbuduj_drzewo(vector<wierzcholek>& wierzcholki);


/**
	* Funkcja maj�ca na celu wype�nienie zmiennej sk�adowej kod w wierzcho�kach. Wierzcho�ki, w kt�rych znak nie wynosi '\0' otrzymaj� pe�ny kod Huffmana dla danego znaku.
	* G��wnym zadaniem funkcji jest wywo�anie fukncji stworz_kod dla obu ga��zi wychodz�cych z wierzcho�ka szczytowego.
	* Parametr przekazywany przez referencj�.
	*@param w - wierzcho�ek b�d�cy szczytem drzewa binarnego.
*/
void zakoduj(wierzcholek& w);


/**
	* Funkcja rekurencyjna maj�ca na celu stworzenie wektora par zawieraj�cych znak i przypisany mu kod Huffmana
	* Parametr przekazywany przez referencj�
	*@param w - wierzcho�ek b�d�cy szczytem drzewa binarnego
*/
vector<pair<char, string>> stworz_pary(const wierzcholek& w);


/**
	* Funkcja maj�ca na celu przekonwertowanie oryginalnego tekstu na odpowiadaj�cy mu kod Huffmana
	* Parametry przekazywany przez referencj�
	* @param tekst - oryginalny tekst
	* @param kody - wektor par zawieraj�cy znaki oraz odpowiadaj�ce im kody
*/
void konwertuj(string& tekst, const vector<pair<char, string>>& kody, const bool& zakoduj);


/**
	* Funkcja zamieniaj�ca poszczeg�lne znaki na odpowiadaj�ce im kody
	* @param tekst - oryginalny tekst
	* @param co_zmienic - �a�cuch znak�w (lub char przekonwertowany na string) kt�ry ma by� podmieniony
	* @param na_co_zmienic - �a�cuch znak�w (lub char przekonwertowany na string) na kt�ry podmieniony ma by� co_zmienic
*/
void znak_na_kod(string& tekst, const string& co_zmienic, const string& na_co_zmienic);


/**
	* Funkcja zamieniaj�ca poszczeg�lne kody na odpowiadaj�ce im znaki. Dzia�a d�u�ej ni� funkcja znak_na_kod ze wzgl�du bezpiecze�stwa -
	* funkcja znak_na_kod z podmienionymi parametrami mog�a np. z kodu 1100 wyci�gn�� kod 10 (za��my, �e 'a') daj�c 1a0, po czym wy�wietla�a b��d
	* nie mog�c znale�� odpowiednik�w kodu 1 oraz 0, kt�re oczywi�cie nie istnia�y. Funkcja kod_na_znak sprawdza znaki po kolei zapobiegaj�c takiej sytuacji.
	* @param tekst - zakodowany tekst.
	* @param kody - wektor par zawieraj�cych znaki i odpowiadaj�ce im kody.
*/
void kod_na_znak(string& tekst, const vector<pair<char, string>>& kody);


/**
	* Funkcja rekurencyjna, w kt�rej ma miejsce faktyczne generowanie kodu Huffmana. Wierzcho�ek z lewej otrzymuje 0, a z prawej 1, dop�ki funkcja nie dotrze
	* do wierzcho�ka, kt�rego warto�� zmiennej sk�adowej dzieci wynosi 0.
	* Parametr w przekazywany przez adres, kod_rodzica przekazywany przez referencj�.
	*param w - adres wierzcho�ka.
	*param kod_rodzica - kod, kt�ry ma w�z� wy�szy. Dla w�z��w g�rnych domy�lna warto�� to "".
*/
void stworz_kod(wierzcholek* w, const string& kod);


/**
	* Funkcja sortuj�ca wektor wierzcho�k�w
	* Parametr przekazywany przez warto��
	* @param a - wierzcho�ek a
	* @param b - wierzcho�ek b
	* @return true, je�eli a ma mniejsz� warto�� od b. Wyj�tkiem jest sytuacja, gdy warto�� wynosi 0.
	* Ka�dy niepusty wierzcho�ek ma warto�� r�n� od 0. Obecno�� zera wynika z warto�ci domy�lnej wierzcho�k�w niezdeklarowanych,
	* inicjowanych podczas wywo�ania funkcji vector::resize w zbuduj_drzewo.
*/
bool sortuj_wierzcholki(const wierzcholek& a, const wierzcholek& b);


/**
	* Funkcja maj�ca na celu zapisa� tekst do pliku.
	* @param adres - adres pliku
	* @param kod - tekst, kt�ry zostanie zapisany w pliku
	* @return true, je�li uda si� otworzy� plik. W przypadku niepowodzenia false.
*/
bool zapisz(const string& adres, string kod);


/**
	* Funkcja ��cz�ca zakodowany tekst, oraz wektor zawieraj�cy znaki i odpowiadaj�ce im warto�ci w jedn� zmienn� tekstow�.
	* Parametry przekazywane przez referencje.
	* @param kod - zakodowany tekst.
	* @param pary - wektor znak�w i warto�ci.
	* @param str jedna zmienna zawieraj�ca tekst oraz wypisane pary.
*/
void polacz(const string& kod, const vector<pair<char, string>>& pary, string& str);


/**
	* Funkcja b�d�ca baz� funkcji widoku interakcja. Analizuje wprowadzone dane i po�redniczy pomi�dzy widokiem a modelem
	* wywo�uj�c funkcj� algorytm_kodowania_dekodowania.
	* @param argc - ilo�� element�w tablicy argv.
	* @param argv - tablica zawieraj�ca dane wprowadzone w wierszu polece�.
	* @param adres_wejscia - adres pliku wejsciowego
	* @param adres_wyjscia - adres pliku wyjsciowego
	* @param wejscie - przyjmie warto�� true, je�eli wprowadzono plik wej�ciowy.
	* @param wyjscie - przyjmie warto�� true, je�eli wprowadzono plik wej�ciowy.
	* @param kodowanie - przyjmie warto�� true, je�eli wprowadzono argument "-c".
	* @param dekodowanie - przyjmie warto�� true, je�eli wprowadzono argument "-d".
	* @return zwraca liczb� naturaln� z przedzia�u domkni�tego od -4 do 1, wy��czaj�c zero
	* kody oznaczaj� odpowiednio:
	* -4 : brak pliku wej�cia/wyj�cia (skutkuje odpowiednim komunikatem w funkcji interakcja i zwr�ceniem przez ni� warto�ci false).
	* -3 : wprowadzono argument "-c" i "-d" jednocze�nie (skutkuje odpowiednim komunikatem w funkcji interakcja i zwr�ceniem przez ni� warto�ci false).
	* -2 : odpowiednie argumenty, ale b��d funkcji dekoduj�cej (jak wy�ej)
	* -1 : odpowiednie argumenty, ale b��d funkcji dekoduj�cej (jak wy�ej)
	*  1 : funkcja dekoduj�ca zwr�ci�a true. (skutkuje odpowiednim komunikatem w funkcji interakcja i zwr�ceniem przez ni� warto�ci true).
	*  2 : funkcja koduj�ca zwr�ci�a true. (skutkuje odpowiednim komunikatem w funkcji interakcja i zwr�ceniem przez ni� warto�ci true).
*/
short logika_interakcji(int argc, char* argv[], string& adres_wejscia, string& adres_wyjscia, bool& wejscie, bool& wyjscie,
	bool& kodowanie, bool& dekodowanie);


/**
	* Funkcja, kt�ra wywo�uje kolejno odpowiednie funkcje w celu przeprowadzenia kodowania Huffmana.
	* @param adreswe - adres pliku wej�ciowego.
	* @param adreswy - adres pliku wyj�ciowego.
	* @return zwraca true, je�eli uda si� zapisa� kod w odpowiednim pliku. W przeciwnym wypadku false.
*/
bool algorytm_zakodowania(const string& adreswe, const string& adreswy);


/**
	* Funkcja, kt�ra wywo�uje kolejno odpowiednie funkcje w celu odkodowania zakodowanego tekstu.
	* @param adreswe - adres pliku wej�ciowego.
	* @param adreswy - adres pliku wyj�ciowego.
	* @return zwraca true, je�eli uda si� zapisa� odkodowany tekst. W przeciwnym wypadku false.
*/
bool algorytm_odkodowania(const string& adreswe, const string& adreswy);


/**
	* Funkcja, kt�ra analizuje wprowadzone dane i na ich podstawie wywo�uje kolejne funkcje i zwraca warto�� wed�ug odpowiedniego kodu
	* @param adreswe - adres pliku wejsciowego
	* @param adreswy - adres pliku wyjsciowego
	* @param wejscie - przyjmie warto�� true, je�eli wprowadzono plik wej�ciowy.
	* @param wyjscie - przyjmie warto�� true, je�eli wprowadzono plik wej�ciowy.
	* @param kodowanie - przyjmie warto�� true, je�eli wprowadzono argument "-c".
	* @param dekodowanie - przyjmie warto�� true, je�eli wprowadzono argument "-d".
	* @return zwraca warto�� wed�ug kodu zdefiniowanego przy funkcji logika_interakcji
*/
short algorytm_kodowania_dekodowania(const string& adreswe, const string& adreswy,
	const bool& wejscie, const bool& wyjscie, const bool& kodowanie, const bool& dekodowanie);
#endif
