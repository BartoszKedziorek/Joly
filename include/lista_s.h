#pragma
#include<iostream>
#include<fstream>
using namespace std;

template <typename t> class Lista_s
{
	int n;
	
	public:
		t** lista;
		Lista_s(int ile);
		void wczytaj(std::fstream&plik);
		void wyswietl();
		~Lista_s();
		
};

template<typename t>
inline void Lista_s<t>::wyswietl()
{
	for (int i = 0; i < n; i++)
	{
		std::cout << i << ". ";
		int j = 0;
		while (lista[i][j] != 1000) { std::cout << lista[i][j] << " "; j++;}
			cout << std::endl;
	}

}

template <typename t>
inline void Lista_s<t>::wczytaj(std::fstream&plik)
{
	for (int i = 0; i < n; i++)
	{
		int przyleg = 0;
		plik >> przyleg;
		lista[i] = new t[przyleg];
		int j;
		for ( j = 0; j < przyleg; j++)
		{
			plik >> lista[i][j];
		}
		lista[i][j] = 1000;
	}
}


template<typename t>
inline Lista_s<t>::Lista_s(int ile)
{
	lista = new t * [ile];
	n = ile;
}


template<typename t>
inline Lista_s<t>::~Lista_s()
{
	lista = NULL;
	delete lista;
//	std::cout << "lista zniszczona!!!!" << std::endl;
}

