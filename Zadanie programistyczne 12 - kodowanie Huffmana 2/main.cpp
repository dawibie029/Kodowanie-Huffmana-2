#include <iostream>
#include <list>
#include "funkcje.h"
#include "struktury.h"
using namespace std;
//  funkcja testowa, mia³a wypisaæ wartoœci tych wierzcho³ków
void wypisz(wierzcholek w) {
    if (w.lewy != nullptr) {    // rekurencja dzia³a, dopóki w zawiera wskaŸniki na inne wierzcho³ki
        wypisz(*w.lewy);
        wypisz(*w.prawy);
    }
    else {  //  elementy dolne maj¹ wskaŸnik o wartoœci nullptr, wiêc wypisywana jest wartoœæ i znak
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
