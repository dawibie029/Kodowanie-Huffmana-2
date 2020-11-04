#ifndef STRUKTURY_H
#define STRUKTURY_H
struct wierzcholek {

	wierzcholek* lewy = nullptr; /**< wskaŸnik na wierzcholek lewy. Domyœlnie nullptr, poniewa¿ pocz¹tkowe wierzcho³ki nigdzie nie wskazuj¹.
								 * Dziêki zastosowaniu null, pêtla bêdzie mog³a przeszukiwaæ wierzcholki wg³¹b, dopóki nie natrafi na wskaŸnik o wartoœæi nullptr. */
	wierzcholek* prawy = nullptr; /**< wskaŸnik na wierzcholek prawy */

	unsigned long wartosc = 0; /**< wartoœæ danego wskaŸnika - iloœæ wyst¹pieñ danego znaku, lub suma wyst¹pieñ znaków w wierzcholkach, na które
							   * wskazuj¹ wskaŸniki */
	char znak = 0;	/**< domyœlnie NULL, poniewa¿ tylko pocz¹tkowe wierzcho³ki maj¹ zapisany znak.
					* Pozosta³e posiadaj¹ jedynie wskaŸniki do innych wierzcholkow */
	bool ma_rodzica = false;

	unsigned short dzieci = 0;	/**< liczba pokoleñ (czyli liczba ga³êzi od wierzcho³ka do wierzcho³ków pocz¹tkowych) */
};
#endif
