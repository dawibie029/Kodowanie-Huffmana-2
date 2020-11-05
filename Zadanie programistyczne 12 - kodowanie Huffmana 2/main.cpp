#include <iostream>
#include <list>
#include "funkcje.h"
#include "struktury.h"
#include "funkcje_widok.h"
using namespace std;

int main(int argc, char* argv[]) {
    string adreswe, adreswy;
    if (interakcja(argc, argv, adreswe, adreswy)) {
        return 0;
    }
    else return -1;
}
