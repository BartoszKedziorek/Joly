#include"kolejka_prio.h"

Kolejka_prio::Kolejka_prio()
{
	ostatni = 0;
	krawedz h;
	h.dlugosc = 0;
	h.poprzedni = 0;
	h.wierzcholek = 0;
	sterta.push_back(h);
	
}

Kolejka_prio::~Kolejka_prio()
{
	;
}

void Kolejka_prio::do_gory()
{
	int i = ostatni;
	while (i != 1)
	{
		
	
		if(sterta[i/2].dlugosc<sterta[i].dlugosc)
		{break;}
		else
		{
			krawedz tmp = sterta[i];
			sterta[i] = sterta[i / 2];
			sterta[i / 2] = tmp;
			i /= 2;
		}
	}
}

void Kolejka_prio::wstaw(krawedz a)
{
	//std::cout << "ostatni: " << ostatni << std::endl;
	//std::cout << "krawedz a.wierzcholek=" << a.wierzcholek << std::endl;
	sterta.push_back(a);
	//std::cout <<"wstawiono:"<<sterta[ostatni+1].wierzcholek << std::endl;
	ostatni++;
	do_gory();
}

void Kolejka_prio :: na_dol()
{
	int i = 1;
	while(1)
	{
		int p = i * 2;
		if(p>ostatni)
		{break;}
		if(p+1<=ostatni)
		{
			if (sterta[p].dlugosc > sterta[p + 1].dlugosc) { p++; };
		}
		if(sterta[i].dlugosc<=sterta[p].dlugosc)
		{break;}
		krawedz tmp = sterta[i];
		sterta[i] = sterta[p];
		sterta[p] = tmp;
		i = p;
	}

}

void Kolejka_prio::daj(krawedz& a)
{

	a = sterta[1];	
	sterta[1] = sterta[ostatni--];
	sterta.resize(ostatni+1);
	na_dol();
}

void Kolejka_prio::wyswietl()
{
	for (int i = 1; i <=ostatni; i++)
	{
		std::cout << sterta[i].dlugosc << " ";
	}

}

void Kolejka_prio::wyswietl_porzpedniki()
{
	for (int i = 1; i <= ostatni; i++)
		std::cout << sterta[i].poprzedni << " ";
	std::cout << std::endl;

}

void Kolejka_prio::wyswietl_wierzcholki()
{
	for (int i = 1; i <= ostatni; i++)
		std::cout << sterta[i].wierzcholek << " ";
	std::cout << std::endl;
}