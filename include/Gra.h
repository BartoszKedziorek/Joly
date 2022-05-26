#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include"funkcje.h"
#include"Dijkstra.h"


struct klucz
{
	SDL_Texture* wyglad;
	SDL_Rect* wymiar;
};

struct postac
{
	SDL_Texture* wyglad;
	SDL_Rect* poz;
};

struct drzwi
{
	SDL_Texture* wyglady[2];
	SDL_Rect* poz;
};


class Gra{

	
public:
	Gra(const char* nazwa,int x,int y, bool fullscreen);
	~Gra();
	void czy_zniszcz_klucz(int ind, int ilos, postac* player,  klucz* klucze[],int zeg);
	void Zdarzenia();
	void czy_zatrzymac(bool& e);
	bool czy_w_trakcie_e();
	bool czy_w_trakcie_t();
	bool czy_w_trakcie_s();
	void render_e();
	void Upadate_e();
	void start_test();
	void Update_t();
	void render_t();
	void render_s();
	void start_s();
	void Update_s();
	void menu_events();
	void menu_update();
	void menu_render();
	bool menu_on();
	void inicjuj_pierwszenstwo();
	void readSpeed();
	klucz * generuj_klucz( klucz * wynik);
	SDL_Rect* generuj_rect(SDL_Rect* prost, int ph, int pw, int px, int py);
	postac* generuj_postac(const char* scierzka,int x, int y);
	drzwi* generuj_przycisk(const char* scierzka, const char* scierzka1, int x, int y);
	bool czy_zlapany(postac * gonaicy[], int ilosc, postac * gracz);
	void start_t();
	void start_e();
private:
	SDL_Renderer* renderer;
	SDL_Window* okno;
	bool menu_r;
	bool running_e;
	bool running_t;
	bool running_s;
};


