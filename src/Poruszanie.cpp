#include"Poruszanie.h"



void inicjuj_macierz_R(int tab[144][144])
{
	for (int i = 0; i < 144; i++)
	{
		for (int j = 0;j<144;j++)
		{
			tab[i][j] = 1000;
		}

	}


}

void inicjuj_macierz_F(int tab_F[144][144],int tab_R[144][144])
{
	for (int k = 0; k < 144; k++)
	{
		for (int j = 0; j < 144; j++)
		{
			for (int i = 0; i < 144; i++)
			{
				if(tab_F[j][k]+tab_F[k][i]<tab_F[j][i])
				{
					tab_F[j][i] = tab_F[j][k] + tab_F[k][i];
					tab_R[j][i] = k;
				}
			}
		
		}

	}


}

void scierzka(int i, int j,int tab_R[144][144])
{

	//std::cout << tab_R[i][j] << std::endl;
	int k = tab_R[i][j];
	if (k != 1000)
	{
		scierzka(i, k,tab_R);
		std::cout << " " << k;
		scierzka(k, j,tab_R);
	}

}

void lewo(SDL_Rect* p,int zeg, int wol)
{
	p->x -= 1 * (zeg % wol / (wol-1));
}

void prawo(SDL_Rect* p, int zeg,int wol)
{
	p->x += 1 * (zeg % wol / (wol-1));
}

void dol(SDL_Rect* p, int zeg,int wol)
{
	p->y+= 1 * (zeg % wol  / (wol-1));
}

void gora(SDL_Rect* p, int zeg,int wol)
{
	p->y -= 1*(zeg%wol/(wol-1));
}

void czekaj(SDL_Rect* p, int zeg, int wol)
{
	
}

ftp ruch_ep(SDL_Rect* player, SDL_Rect* enemy, int tab[144][144],int &usun, bool pier[9][16])
{
	
	int xp = poz_sx(player->x), yp = poz_sy(player->y);
	int xe = poz_sx(enemy->x), ye = poz_sy(enemy->y);

	int pole_e = ye * 16 + xe;
	int pole_p = yp * 16 + xp;

	int do_pole = tab[pole_e][pole_p];

	if (pier[do_pole/16][do_pole%16] == 0)
	{
	pentla2:
		
		switch (do_pole - pole_e)
		{
		case 16: usun = do_pole; pier[do_pole / 16][do_pole % 16] = 1; return dol;  break;
		case -16:usun = do_pole; pier[do_pole / 16][do_pole % 16] = 1; return gora;  break;
		case 1: usun = do_pole; pier[do_pole / 16][do_pole % 16] = 1; return prawo;  break;
		case -1: usun = do_pole; pier[do_pole / 16][do_pole % 16] = 1; return lewo;  break;
		default: do_pole = pole_p; goto pentla2;
		}
	}
	else { usun = do_pole; pier[yp][xp] = 1; return czekaj; }
}

ftp ruch_e(SDL_Rect* player, SDL_Rect* enemy, int tab[144][144],int tabRW[144][144],int &zaj, bool pier[9][16])
{

	int xp = poz_sx(player->x), yp = poz_sy(player->y);
	int xe = poz_sx(enemy->x), ye = poz_sy(enemy->y);

	int pole_e = xe + ye * 16;
	int pole_p = xp + yp * 16;
	int do_pole = 0;
	
	
		do_pole = tab[pole_p][pole_e];
		
		if (do_pole != 1000)
		{
			while (tab[pole_e][do_pole] != 1000) { do_pole = tab[pole_e][do_pole];
			}
		}
		
		if (do_pole != zaj)
		{
		pentla:
			switch (do_pole - pole_e)
			{
			case 16:zaj = do_pole; pier[do_pole / 16][do_pole % 16] = 1; return dol;  break;
			case -16:zaj = do_pole; pier[do_pole / 16][do_pole % 16] = 1; return gora;   break;
			case 1:zaj = do_pole; pier[do_pole / 16][do_pole % 16] = 1; return prawo;   break;
			case -1:zaj = do_pole; pier[do_pole / 16][do_pole % 16] = 1; return lewo;  break;
			default: do_pole = pole_p; pier[do_pole / 16][do_pole % 16] = 1; goto pentla;
			}
		}
		else { return ruch_ep(player,enemy,tabRW,zaj,pier); }
	
}





void inicjuj_macierz_RW(int tab_RW[144][144])
{
for(int i=0;i<144;i++)
	for(int j=0;j<144;j++)
		if (tab_RW[j][i] != 1000)
		{
			for (int k = 0; k < 144; k++)
			{
				if (tab_RW[j][k] == 1000 && tab_RW[i][k]!=1000)
					tab_RW[j][k] = tab_RW[j][i];
			}

		}
}

void wypisz_RW(int i, int j, int tab_RW[144][144])
{
	int k = tab_RW[i][j];

	while (k != j)
	{
		std::cout << k << " ";
		k = tab_RW[k][j];
	}
	std::cout << std::endl;
}

