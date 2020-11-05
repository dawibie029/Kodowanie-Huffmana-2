#include <iostream>
#include <list>
#include "funkcje.h"
#include "struktury.h"
#include "funkcje_widok.h"
using namespace std;

void wypisz(wierzcholek w) {
    if (w.lewy != nullptr) {    
        wypisz(*w.lewy);
        wypisz(*w.prawy);
    }
    else {  
        cout << "\"" << w.znak << "\" - " << w.kod << endl;
    }
}

int main(int argc, char* argv[]) {
    string adreswe, adreswy;
    if (interakcja(argc, argv, adreswe, adreswy)) {
        if (algorytm_zakodowania(adreswe, adreswy)) {
            cout << "Sukces!" << endl;
        }
        else
            cout << "Niepowodzenie! " << endl;
       /* wierzcholek w;
        w.znak = 'w';
        vector<wierzcholek> wierzcholki;
        string kod;
        odczytaj_odkodowane(adreswe, wierzcholki, kod);
        w = zbuduj_drzewo(wierzcholki);
        zakoduj(w);
        vector<pair<char, string>> xD = stworz_pary(w);
        for (auto a : xD) {
            cout << "\"" << a.first << "\" - " << a.second << endl;
        }
        cout << endl;
        konwertuj(kod, xD);
        cout << kod << endl;
        string str;
        polacz(kod, xD, str);
        zapisz(adreswy, str);
        cout << "Done!" << endl;*/
    }
    else return 0;
}
