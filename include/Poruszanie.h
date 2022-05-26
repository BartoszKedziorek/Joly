#include<iostream>
#include<SDL.h>
#include"funkcje.h"

typedef void (*ftp)(SDL_Rect* p, int zeg, int wol);

void inicjuj_macierz_R(int tab[144][144]);

void inicjuj_macierz_F(int tab_F[144][144],int tab_R[144][144]);

void inicjuj_macierz_RW(int tab_RW[144][144]);


void wypisz_RW(int i, int j, int tab_RW[144][144]);
void scierzka(int i, int j,int tab_R[144][144]);
void lewo(SDL_Rect*p,int zeg,int spd);
void prawo(SDL_Rect*p,int zeg,int spd);
void dol(SDL_Rect* p,int zeg,int spd);
void gora(SDL_Rect* p,int zeg,int spd );
void czekaj(SDL_Rect* p ,int zeg, int spd);

ftp ruch_e(SDL_Rect* player, SDL_Rect* enemy, int tab[144][144], int tabRW[144][144],int &zaj, bool pier[9][16]);
ftp ruch_ep(SDL_Rect* player, SDL_Rect* enemy, int tab[144][144],int &usun, bool pier[9][16]);