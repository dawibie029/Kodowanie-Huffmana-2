#include <iostream>
#include <list>
#include "funkcje.h"
#include "struktury.h"
using namespace std;
//  funkcja testowa, mia�a wypisa� warto�ci tych wierzcho�k�w
void wypisz(wierzcholek w) {
    if (w.lewy != nullptr) {    // rekurencja dzia�a, dop�ki w zawiera wska�niki na inne wierzcho�ki
        wypisz(*w.lewy);
        wypisz(*w.prawy);
    }
    else {  //  elementy dolne maj� wska�nik o warto�ci nullptr, wi�c wypisywana jest warto�� i znak
        cout << w.wartosc << " - " << w.znak << endl;
    }
}
int main()
{
    wierzcholek w;
    w.znak = 'w';
    vector<wierzcholek> wierzcholki;
    string kod;
    odczytaj_odkodowane("C:\\Users\\Dawid\\Desktop\\New Text Document.txt", wierzcholki, kod);
    w = zbuduj_drzewo(wierzcholki);
    wypisz(w);
    cout << endl;
}
