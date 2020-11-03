#ifndef STRUKTURY_H
#define STRUKTURY_H
struct wierzcholek {
	wierzcholek* lewy = nullptr; /**< wska�nik na wierzcholek lewy. Domy�lnie nullptr, poniewa� pocz�tkowe wierzcho�ki nigdzie nie wskazuj�.
								 * Dzi�ki zastosowaniu null, p�tla b�dzie mog�a przeszukiwa� wierzcholki wg��b, dop�ki nie natrafi na wska�nik o warto��i nullptr. */
	wierzcholek* prawy = nullptr; /**< wska�nik na wierzcholek prawy */
	unsigned long wartosc = 0; /**< warto�� danego wska�nika - ilo�� wyst�pie� danego znaku, lub suma wyst�pie� znak�w w wierzcholkach, na kt�re
							   * wskazuja wska�niki */
	char znak = 0;	/**< domy�lnie NULL, poniewa� tylko pocz�tkowe wierzcho�ki maj� zapisany znak.
					* Pozosta�e posiadaj� jedynie wska�niki do innych wierzcholkow */		
	bool has_parent = false;
};
#endif
