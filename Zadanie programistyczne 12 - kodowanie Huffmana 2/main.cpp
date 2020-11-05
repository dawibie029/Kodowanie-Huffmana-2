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
    /*if (interakcja(argc, argv, adreswe, adreswy)) {
        if (algorytm_zakodowania(adreswe, adreswy)) {
            cout << "Sukces!" << endl;
        }
        else
            cout << "Niepowodzenie! " << endl;
    }
    else return 0;*/
    algorytm_zakodowania("C:\\Users\\Dawid\\Desktop\\testXDDD.txt", "C:\\Users\\Dawid\\Desktop\\New Text Document2.txt");
    algorytm_odkodowania("C:\\Users\\Dawid\\Desktop\\New Text Document2.txt", "C:\\Users\\Dawid\\Desktop\\testXDDD2.txt");
}
