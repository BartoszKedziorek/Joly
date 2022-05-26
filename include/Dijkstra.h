#include<iostream>
#include"kolejka_prio.h"
#include"lista_s.h"
#include"Stos.h"
#include<Windows.h>
#include"Poruszanie.h"
#include<cmath>

void oblicz_tablice(int pole_pocz, int n, int wez, krawedz drogi[], Lista_s<int> zwiazki);
void droga(krawedz drogi[], int pocz, int kon);
int docelowy(krawedz drogi[], int pocz, int kon);
void usun_droge(Lista_s<int> zwiazki,int i);
void inicjuj_tab_scislosci(bool tab[144]);
int ile_zjad(int i,int poz, bool tab[144]);
void przywroc_droge(Lista_s<int> zwiazki, int i);
ftp ruch_Djikstra(SDL_Rect* player, SDL_Rect* enemy, int &usun, Lista_s<int> zwiazki, int tabR[144][144], int tabRW[144][144],bool tab_s[144],bool pier[9][16]);

