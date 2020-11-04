#include <iostream>
#include <list>
#include "funkcje.h"
#include "struktury.h"
#include "funkcje_widok.h"
using namespace std;
/*
void wypisz(wierzcholek w) {
    if (w.lewy != nullptr) {    
        wypisz(*w.lewy);
        wypisz(*w.prawy);
    }
    else {  
        cout << w.wartosc << " - " << w.znak << endl;
    }
}*/

int main(int argc, char* argv[]) {
    string adreswe, adreswy;
    interakcja(argc, argv, adreswe, adreswy);
    wierzcholek w;
    w.znak = 'w';
    vector<wierzcholek> wierzcholki;
    string kod;
    odczytaj_odkodowane("C:\\Users\\Dawid\\Desktop\\New Text Document.txt", wierzcholki, kod);
    w = zbuduj_drzewo(wierzcholki);
    //wypisz(w);
    cout << endl;
}
