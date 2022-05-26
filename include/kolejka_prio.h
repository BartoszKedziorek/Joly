#pragma
#include<vector>
#include<iostream>
struct krawedz
{
	int wierzcholek;
	int poprzedni;
	int dlugosc;
};

class Kolejka_prio
{
	int ostatni;
	std::vector<krawedz> sterta;

public:
	Kolejka_prio();
	void wstaw(krawedz a);
	void daj(krawedz &a);
	void do_gory();
	void wyswietl();
	void wyswietl_porzpedniki();
	void wyswietl_wierzcholki();
	void na_dol();
	~Kolejka_prio();
};
