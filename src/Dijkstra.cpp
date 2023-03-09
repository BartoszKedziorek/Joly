#include"Dijkstra.h"

void inicjuj_tab_scislosci(bool tab[144])
{
	for (int i = 0; i < 144; i++)
	{
		tab[i] = 0;
	}

	tab[128] = 1;
	tab[96] = 1;
	tab[112] = 1;
	tab[140] = 1;
	tab[141] = 1;
	tab[143] = 1;
	tab[127] = 1;
	tab[111] = 1;
	tab[95] = 1;
	tab[79] = 1;
	tab[63] = 1;
	tab[47] = 1;
	tab[31] = 1;
	tab[15] = 1;
	tab[124] = 1;


}

void oblicz_tablice(int pole_pocz,int n,int wez,krawedz drogi[], Lista_s<int> zwiazki)
{
	
	bool* odwiedzone;
	odwiedzone = new bool[n];
	for (int i = 0; i < n; i++)
		odwiedzone[i] = 0;

	STOS<bool>czasomierz(wez);
	for(int i=0;i<wez;i++)
		czasomierz.push(1);

	for (int i = 0; i < n; i++)
	{
		drogi[i].wierzcholek = i;
		drogi[i].dlugosc = 1000;
	}

	drogi[pole_pocz].dlugosc = 0;
	//to nie ma znaczenia. Deklarujê to dla ³adu
	drogi[pole_pocz].poprzedni = pole_pocz;

	int aktualny = pole_pocz;

	Kolejka_prio tura;
	bool* x;
	x = new bool;
	
	odwiedzone[pole_pocz] = 1;
	czasomierz.pop(*x);

	
	while (czasomierz.CZY_PELNY() != 2)
	{
		
		
		//system("pause");
				int i = 0;
				while (zwiazki.lista[aktualny][i] != 1000)
				{
					
						//dodanie do kolejki priorytetowej krawêdzi
						//u¿ywamy tutaj kolejki priorytetowej
						//poniewa¿ chcemy wiedzieæ jakimi krawêdziami mo¿emy
						//przejœæ z ju¿ odwiedzonych wierzcho³ków i która z tych krawêdzi jest najkrótsza
						krawedz* tmp;
						tmp = new krawedz;
						tmp->dlugosc = 1;
						tmp->poprzedni = aktualny;
						tmp->wierzcholek = zwiazki.lista[aktualny][i];
						tura.wstaw(*tmp);
						
						tmp = NULL;
						delete tmp;
						
					
					i++;
				}

				
			
				
				szukam_przejscia:
				krawedz * tmp;
				tmp = new krawedz;
				tura.daj(*tmp);
				aktualny = tmp->poprzedni;
			
			
				//sprawdzenie czy nowa droga przez tê krawêdŸ jest lepsza od drogi w talicy najlepszych oszacowañ
				if (drogi[tmp->poprzedni].dlugosc + tmp->dlugosc < drogi[tmp->wierzcholek].dlugosc)
				{
					drogi[tmp->wierzcholek].dlugosc = drogi[tmp->poprzedni].dlugosc + tmp->dlugosc;
					drogi[tmp->wierzcholek].poprzedni = aktualny;
				}
				else { goto szukam_przejscia; }
				
				/// udalo sie przypisac mniejsza wartosc!!!
				aktualny = tmp->wierzcholek;

				if (odwiedzone[aktualny] == 0) { czasomierz.pop(*x); odwiedzone[aktualny] = 1;  }
				
				
				
				tmp = NULL;
				delete tmp;

	}

}


void droga(krawedz drogi[], int pocz, int kon)
{
	
	if (drogi[kon].wierzcholek == pocz) { return; }
	else { droga(drogi, pocz, drogi[kon].poprzedni); }
	cout << drogi[kon].wierzcholek << " ";
	
}


int docelowy(krawedz drogi[], int pocz, int kon)
{
	if (pocz == drogi[kon].poprzedni) { return kon;}
	else { return docelowy(drogi, pocz, kon[drogi].poprzedni);}
}

void usun_droge(Lista_s<int> zwiazki,int i)
{
	
		int indeks = 0;

		while (zwiazki.lista[i][indeks] != 1000)
		{
			int indeks2 = 0;
			while (zwiazki.lista[zwiazki.lista[i][indeks]][indeks2 + 1] != 1000)
			{
				if (zwiazki.lista[zwiazki.lista[i][indeks]][indeks2] == i)
				{
					int tmp = zwiazki.lista[zwiazki.lista[i][indeks]][indeks2 + 1];
					zwiazki.lista[zwiazki.lista[i][indeks]][indeks2 + 1] = zwiazki.lista[zwiazki.lista[i][indeks]][indeks2];
					zwiazki.lista[zwiazki.lista[i][indeks]][indeks2] = tmp;
				}
				indeks2++;
			}
			zwiazki.lista[zwiazki.lista[i][indeks]][indeks2] = 1000;
			//	zwiazki.lista[i][indeks] = 1000;
			indeks++;
		}
	

}

int ile_zjad(int i, int poz, bool tab[144])
{
	
	int wynik=0;
	switch (i)
	{
	case 76:
	case 108:
	case 31:
	case 112:	wynik = 1; break;
	case 96:	 wynik = 2; break;
	case 80:	wynik = 3; break;
	case 124:	 wynik = 12; break;
	case 140:	wynik = 11; break;
	case 141:	wynik = 10; break;
	case 142:	 wynik = 9; break;
	case 143: wynik = 8; break;
	case 127: wynik =  7; break;
	case 111: wynik =  6; break;
	case 95: wynik = 5; break;
	case 79: wynik = 4; break;
	case 63: wynik = 3; break;
	case 47: wynik = 2; break;
	default:	wynik= tab[poz]; break;
	}
	wynik += 1;
	
	int suma = (abs((92 * tab[poz]) - wynik))+tab[poz] ;
	//std::cout << "wynik: " << wynik << "  suma:" << suma << endl;
	//std::cout << "suma:" << suma << endl;
	return suma;

}

void przywroc_droge(Lista_s<int> zwiazki, int i)
{
	int indeks = 0;

	while (zwiazki.lista[i][indeks] != 1000)
	{
		int indeks2 = 0;
		while(zwiazki.lista[zwiazki.lista[i][indeks]][indeks2] != 1000)
		{
			indeks2++;
		}

		zwiazki.lista[zwiazki.lista[i][indeks]][indeks2] = i;
		indeks++;
	}

}

funkcjaRuchu ruch_Djikstra(SDL_Rect* player, SDL_Rect* enemy, int &usun, Lista_s<int> zwiazki, int tabR[144][144], int tabRW[144][144],bool tab_s[144], bool pier[9][16])
{
	
	if (usun != 1000)
	{
		int pole_gracz = 0, pole_enemy = 0;
	//	std::cout << pole_enemy << endl;
		//obliczamy pole na których znajduj¹ siê gracz i przeciwnik
		pole_gracz = poz_sx(player->x) + poz_sy(player->y) * 16;
		pole_enemy = poz_sx(enemy->x) + poz_sy(enemy->y) * 16;

		int* wsk_na_usun;
		wsk_na_usun = zwiazki.lista[usun];
		
		krawedz drogi[144];
		//funkcja, która ma usun¹æ krawêdzie do wierzcho³ków blokowanych przez pierwszego ducha 
		usun_droge(zwiazki, usun);
		oblicz_tablice(pole_enemy, 144, 92 - ile_zjad(usun,pole_enemy,tab_s), drogi, zwiazki);	
		przywroc_droge(zwiazki, usun);
		
		//je¿eli istnieje droga do gracza
		if (drogi[pole_gracz].dlugosc != 1000)
		{
			int cel = docelowy(drogi, pole_enemy, pole_gracz);
			//cel to nie jest wierzcho³ek na którym jest gracz
			//jest to po prostu nastêpny wierzcho³ek do odwiedzenia
			usun = cel;
			switch (cel - pole_enemy)
			{
			case -1:pier[cel / 16][cel % 16 ] = 1; return lewo;
			case 1:pier[cel / 16][cel % 16 ] = 1; return prawo;
			case 16:pier[cel / 16][cel % 16 ] = 1; return dol;
			case -16:pier[cel / 16][cel % 16 ] = 1; return gora;
			}
		}
		else { return ruch_ep(player,enemy,tabRW,usun,pier); }
	}
	
}