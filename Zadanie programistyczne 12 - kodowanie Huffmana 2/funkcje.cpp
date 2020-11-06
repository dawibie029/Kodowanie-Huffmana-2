#include "funkcje.h"
#include "struktury.h"
#include <map>
#include <fstream>
#include <algorithm>


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

bool algorytm_zakodowania(const string& adreswe, const string& adreswy) {
	wierzcholek w;
	vector<wierzcholek> wierzcholki;
	string kod;
	odczytaj_odkodowane(adreswe, wierzcholki, kod);
	w = zbuduj_drzewo(wierzcholki);
	zakoduj(w);
	vector<pair<char, string>> wektor_par = stworz_pary(w);
	konwertuj(kod, wektor_par, true);
	string str;
	polacz(kod, wektor_par, str);
	return (zapisz(adreswy, str));	
}
bool algorytm_odkodowania(const string& adreswe, const string& adreswy) {
	string tekst;
	vector<pair<char, string>> kody;
	odczytaj_zakodowane(adreswe, kody, tekst);
	konwertuj(tekst, kody, false);
	zapisz(adreswy, tekst);
	return true;
}

bool odczytaj_zakodowane(const string& adres, vector<pair<char, string>>& kody, string& tekst) {
	ifstream plik(adres);
	if (plik) {
		getline(plik, tekst);
		while (!plik.eof()) {
			pair<char, string> p_pomocnicza;
			plik.get(p_pomocnicza.first);
			plik.get(); plik.get(); plik.get(); // pomijamy spacjê, myœlnik, spacjê
			getline(plik, p_pomocnicza.second);
			kody.push_back(p_pomocnicza);
		}
		return true;
	}
	else
		return false;
}

bool zapisz(const string& adres, string kod) {
	ofstream plik(adres);
	if (plik) {
		plik << kod;
		return true;
	}
	else
		return false;
}

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

void zakoduj(wierzcholek& w) {
	stworz_kod(w.lewy, "");
	stworz_kod(w.prawy, "");
}

vector<pair<char, string>> stworz_pary(const wierzcholek& w) {
	static vector<pair<char, string>> wektor_pomocniczy;
	pair<char, string> para_pomocnicza;
	if (w.lewy != nullptr) {	/** Sprawdzamy tylko lewy dla oszczêdnoœci czasu - wskaŸniki zawsze by³y zapisywane parami lewy-prawy, wiêc niemo¿liwe jest, aby
								* przy istnieniu jednego nie istnia³ drugi. Gdyby jednak tak siê zdarzy³o, b³¹d nast¹pi³ by ju¿ w funkcji zbuduj_drzewo */
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

void konwertuj(string& tekst, const vector<pair<char, string>>& kody, const bool& zakoduj) {
	if (zakoduj) {
		for (const auto& a : kody) {
			string zmienna_pomocnicza(1, a.first);
			znak_na_kod(tekst, zmienna_pomocnicza, a.second);
		}
	}
	else
		kod_na_znak(tekst, kody);

}

void znak_na_kod(string& tekst, const string& co_zmienic, const string& na_co_zmienic)
{
	size_t i = 0;
	while ((i = tekst.find(co_zmienic, i)) != std::string::npos) {
		tekst.replace(i, co_zmienic.length(), na_co_zmienic);
		i += na_co_zmienic.length(); 
	}
}

void kod_na_znak(string& tekst, const vector<pair<char, string>>& kody) {
	for (size_t i = 0; i < tekst.length(); i++) {
		for (auto a : kody) {
			int dlugosc = a.second.length();
			string str_pomocniczy = tekst.substr(i, dlugosc);
			if (str_pomocniczy == a.second) {
				string str_pomocniczy_2(1, a.first);
				tekst.replace(i, dlugosc, str_pomocniczy_2);
				break;
			}
		}
	}
}

bool sortuj_wierzcholki(const wierzcholek& a, const wierzcholek& b) {
	if (a.wartosc != b.wartosc)
		if (a.wartosc == 0 || b.wartosc == 0)
			return a.wartosc > b.wartosc;
		else
			return a.wartosc < b.wartosc;
	else /** je¿eli jest taka sama wartoœæ, to w pierwszej kolejnoœci wybieramy wêzê³ z mniejsz¹ iloœci¹ dzieci */
		return a.dzieci < b.dzieci;
}

void polacz(const string& kod, const vector<pair<char, string>>& pary, string& str) {
	str = kod;
	str += "\n";
	for (auto para : pary) {
		str.push_back(para.first);
		str += " - " + para.second + "\n";
	}
	
}

short logika_interakcji(int argc, char* argv[], string& adres_wejscia, string& adres_wyjscia, bool& wejscie, bool& wyjscie,
	bool& kodowanie, bool& dekodowanie) {
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
			adres_wejscia = argv[i + 1];
			for (int j = i + 2; strcmp(argv[j], "-i") != 0 && strcmp(argv[j], "-o") != 0
				&& strcmp(argv[j], "-c") != 0 && strcmp(argv[j], "-d") != 0; j++) {
				adres_wejscia += " ";
				adres_wejscia += argv[j];
			}
			wejscie = true;
		}
		else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
			adres_wyjscia = argv[i + 1];
			for (int j = i + 2; strcmp(argv[j], "-i") != 0 && strcmp(argv[j], "-o") != 0
				&& strcmp(argv[j], "-c") != 0 && strcmp(argv[j], "-d") != 0; j++) {
				adres_wyjscia += " ";
				adres_wyjscia += argv[j];
			}
			wyjscie = true;
		}
		else if (strcmp(argv[i], "-c") == 0) {
			kodowanie = true;
		}
		else if (strcmp(argv[i], "-d") == 0) {
			dekodowanie = true;
		}
	}
	return algorytm_kodowania_dekodowania(adres_wejscia, adres_wyjscia, wejscie, wyjscie, kodowanie, dekodowanie);
}


short algorytm_kodowania_dekodowania(const string& adreswe, const string& adreswy, 
	const bool& wejscie, const bool& wyjscie, const bool& kodowanie, const bool& dekodowanie) {

	if (wejscie && wyjscie) {
		if (kodowanie && !dekodowanie) {
			if (algorytm_zakodowania(adreswe, adreswy))
				return 1;
			else
				return -1;
		}
		else if (!kodowanie && dekodowanie){
			if (algorytm_odkodowania(adreswe, adreswy))
				return 2;
			else
				return -2;
		}
		else {

			return -3;
		}
	}
	else {
		return -4;
	}
}