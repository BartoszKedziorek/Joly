#include"funkcje.h"
#include<SDL.h>
#include<SDL_image.h>

bool przeszkody[11][18]{ 0 };

int kierunki[4]
{
	SDL_SCANCODE_LEFT,
	SDL_SCANCODE_RIGHT,
	SDL_SCANCODE_UP,
	SDL_SCANCODE_DOWN
};

void inicjuj_przeszkody(bool tab[11][18])
{
	for (int i = 1; i < 10; i++)
	{
		tab[i][0] = 1;
		tab[i][17] = 1;
	}

	for (int j = 0; j < 18; j++)
	{
		tab[0][j] = 1;
		tab[10][j] = 1;
	}

	tab[2][2] = 1;
	tab[3][2] = 1;
	tab[2][4] = 1;
	tab[3][4] = 1;
	tab[3][6] = 1;
	tab[2][6] = 1;
	tab[1][8] = 1;
	tab[2][8] = 1;
	tab[3][8] = 1;
	tab[1][9] = 1;
	tab[3][10] = 1;
	tab[2][11] = 1;
	tab[2][13] = 1;
	tab[1][15] = 1;
	tab[2][15] = 1;
	tab[3][15] = 1;
	tab[4][12] = 1;
	tab[4][14] = 1;
	tab[4][15] = 1;
	tab[5][2] = 1;
	tab[5][3] = 1;
	tab[5][4] = 1;
	tab[5][5] = 1;
	tab[5][7] = 1;
	tab[5][9] = 1;
	tab[5][10] = 1;
	tab[5][12] = 1;
	tab[5][15] = 1;
	tab[6][7] = 1;
	tab[6][9] = 1;
	tab[6][10] = 1;
	tab[6][12] = 1;
	tab[6][14] = 1;
	tab[6][15] = 1;
	tab[7][2] = 1;
	tab[7][4] = 1;
	tab[7][5] = 1;
	tab[7][7] = 1;
	tab[7][15] = 1;
	tab[8][2] = 1;
	tab[8][4] = 1;
	tab[8][5] = 1;
	tab[8][7] = 1;
	tab[8][8] = 1;
	tab[8][10] = 1;
	tab[8][11] = 1;
	tab[8][14] = 1;
	tab[8][15] = 1;
	tab[9][2] = 1;
	tab[9][10] = 1;
	tab[9][11] = 1;
	tab[9][12] = 1;
}

int poz_gx(int x) { return (x + 60) / 120; }
int poz_gy(int y) { return (y-1) / 120; }

int poz_lx(int x) { return (x-1) / 120; }
int poz_ly(int y) { return (y + 60) / 120; }

int poz_px(int x) { return (x + 121) / 120; }
int poz_py(int y) { return (y + 60) / 120; }


int poz_dx(int x) { return (x + 60) / 120; }
int poz_dy(int y) { return (y + 121) / 120; }

int poz_sx(int x) { return (x + 60) / 120; }
int poz_sy(int y) { return (y + 60) / 120; }

int poz_pgrx(int x) { return (x + 119) / 120; }
int poz_pgry(int y) { return y / 120; }

int poz_ldrx(int x) { return x / 120;}
int poz_ldry(int y) { return (y + 119) / 120;}

int poz_pdrx(int x) { return (x + 119) / 120; }
int poz_pdry(int y) { return (y + 119) / 120; }

int poz_lgrx(int x) { return x/120; }
int poz_lgry(int y) { return y/120; }

int pozycja_srodek(SDL_Rect* prost)
{
	return (prost->x + 60) / 120 + (prost->y + 60) / 120 * 16;
}


void ruch(SDL_Rect* p,  bool tab[11][18],int spd,int zeg)
{
	/*std::cout << "prawy gorny:" << std::endl;
	std::cout << poz_pgrx(p->x) << " " << poz_pgry(p->y) << std::endl;
	std::cout << "lewy gorny:" << std::endl;
	std::cout << poz_lgrx(p->x) << " " << poz_lgry(p->y) << std::endl;*/
//	if(1 * fabs(tab[p->y + 2][p->x + 1] - 1) * fabs(tab[poz_pgry(p->y) + 2][poz_pgrx(p->x) + 1] - 1)>1)std::cout <<p->y + 2<<" "<<p->x + 1<< " " << poz_pgry(p->y) + 2<<" "<<poz_pgrx(p->x) + 1 << std::endl;
	//if (zeg < 0) { std::cout << zeg << std::endl; }
	const Uint8* klawisze = SDL_GetKeyboardState(NULL);
	p->x -= (zeg % spd)/  (spd - 1)  * klawisze[kierunki[0]] * (fabs(tab[poz_pgry(p->y)+1][poz_pgrx(p->x)]-1) * fabs(tab[poz_pdry(p->y) + 1][poz_pdrx(p->x)]-1));//lewyo
	p->x += (zeg % spd) / (spd - 1) * klawisze[kierunki[1]] * fabs(tab[poz_ldry(p->y)+1][poz_ldrx(p->x)+2]-1) * fabs(tab[(p->y)/120+1][(p->x)/120+2]-1);//prawo
	p->y += (zeg % spd) / (spd - 1) * klawisze[kierunki[3]] * fabs(tab[(p->y)/120+2][(p->x/120)+1]-1)* fabs(tab[poz_pgry(p->y) +2][poz_pgrx(p->x)+1] - 1);//dol
	p->y -= (zeg % spd) / (spd - 1) * klawisze[kierunki[2]] * fabs(tab[poz_pdry(p->y) ][poz_pdrx(p->x)+1] - 1)* fabs(tab[poz_ldry(p->y)][poz_ldrx(p->x)+1] - 1);///gora
	//	delete klawisze;

}

void pozycja(int x, int y) {	std::cout << "x: " << int((x + 119) / 120) << " y:" << int((y + 119) / 120) << std::endl;}


