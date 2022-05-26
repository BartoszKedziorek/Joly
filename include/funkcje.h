#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<cmath>


void ruch(SDL_Rect* p, bool tab[11][18], int spd, int zeg);

void inicjuj_przeszkody(bool tab[11][18]);
int poz_px(int x);
int poz_py(int y);

int poz_lx(int x);
int poz_ly(int y);

int poz_gx(int x);
int poz_gy(int y);

int poz_dx(int x);
int poz_dy(int y);

int poz_sx(int x);
int poz_sy(int y);

int pozycja_srodek(SDL_Rect* prost);

void pozycja(int x, int y);
