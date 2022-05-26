#include"include/Gra.h"
#include <SDL.h>
#include"include/Poruszanie.h"
#include<Windows.h>

Gra * Giera;

int main(int argc, char* args[])
{

    /*
    inicjuj_macierz_RW(macierz_RWa);
   // wypisz_RW(0,143,macierz_RWa);
    std::cout << std::endl;*/
  //  wypisz_RW(0, 136, macierz_RWa);
  
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    const int fps = 60;
    const int op = 1000 / fps;

    Uint8 poczatek;
    int koniec;
    Giera = new Gra("Joly",1910,1000,1);
  
    menu:
    while (Giera->menu_on())
    {
        Giera->menu_events();
        Giera->menu_update();
        Giera->menu_render();
    }
 
    while (Giera->czy_w_trakcie_e())
    {
        poczatek = SDL_GetTicks();
        Giera->Zdarzenia();
        Giera->Upadate_e();
        Giera->render_e();
        koniec = SDL_GetTicks() - poczatek;

        if (koniec < op)
        {
            SDL_Delay(op - koniec);
        }
    }

    while (Giera->czy_w_trakcie_t())
    {
        poczatek = SDL_GetTicks();
        Giera->Zdarzenia();
        Giera->Update_t();    
        Giera->render_t();
        koniec = SDL_GetTicks() - poczatek;

        if (koniec < op)
        {
            SDL_Delay(op - koniec);

        }
    }

    while (Giera->czy_w_trakcie_s())
    {
        poczatek = SDL_GetTicks();
        Giera->Zdarzenia();
        Giera->Update_s();
        Giera->render_s();
        koniec = SDL_GetTicks() - poczatek;

        if (koniec < op)
        {
            SDL_Delay(op - koniec);

        }
    }

    if (Giera->menu_on() == true) { goto menu; }
 /*
    system("pause");
    SYSTEMTIME pocz,kon;
    GetSystemTime(&pocz);
 
    fstream dane;
    dane.open("macierze/dane_do_listyDJ.txt", ios::in);
    Lista_s<int> proba_lista(144);
    proba_lista.wczytaj(dane);
    krawedz drogi[144];
    int usun = 101;
    usun_droge(proba_lista, usun);
    proba_lista.wyswietl();
    int szuk = 128;
    oblicz_tablice(szuk, 144,92-ile_zjad(usun),drogi, proba_lista);
    std::cout << "obliczono" << endl;
    
    for (int i = 0; i < 144; i++)
    {
        if (proba_lista.lista[i][0] != 1000 && i != szuk)
        {
            cout << i << ". ";
            droga(drogi, szuk, i);
            std::cout << endl;
        }
    }
    
    GetSystemTime(&kon);
  
   // cout<<docelowy(drogi, 6, 20)<<endl;
    cout << "czas w mlsec: " << kon.wMilliseconds - pocz.wMilliseconds << endl;
    
    */
   /* int tab[3][4]
    {
        1,2,3,4,
        3,78,5,2,
        4,5,3,2
    };

    int* wsk;
    wsk = tab[1];
    wsk++;
    cout << *wsk << endl;
    */
    return 0;
}