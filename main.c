#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "naglowek.h"

//podaj rząd pochodnej
int rzad_pochodnej = 2;

int main()
{
    //wskaznik PoczatekWyrazenia to odpowiednik wskaznika glowny z Prata str 570 ... przechowuje informacje o "poczatku" rownania
    struct ElementSumy elem_sumy_poczatek_wyrazenia;
    elem_sumy_poczatek_wyrazenia.licznik_ = 1;
    elem_sumy_poczatek_wyrazenia.mianownik_ = 1;
    elem_sumy_poczatek_wyrazenia.p_tensor_= NULL;
    elem_sumy_poczatek_wyrazenia.p_next_element_sumy_ = NULL;

    //dodanie obiektu DDD(n)
    struct ElementSumy *p_elem_sumy_DD = DodajElementSumy(&elem_sumy_poczatek_wyrazenia);
    p_elem_sumy_DD->licznik_ = -1;
    p_elem_sumy_DD->mianownik_ = 2;
    p_elem_sumy_DD->p_tensor_ = NULL;
    p_elem_sumy_DD->p_next_element_sumy_ = NULL;

    struct Tensor *p_elem_tensora_DD = DodajTensorDoElementSumy(p_elem_sumy_DD);

    p_elem_tensora_DD->p_nazwa_tensora_ = "DDD";
    struct Indeks *p_elem_indeksu_DDD = DodajIndeksDoTensora(p_elem_tensora_DD);

    //*********************************************
    //*********************************************
    //Podaj wartosc n okreslajaca rzad pochodnej np. n=3 to rownanie ma postac D(3)*D(2)*D(1)*funk(11)*funk(11)
    (*p_elem_indeksu_DDD).wartosc_indeksu_ = rzad_pochodnej;

    //*********************************************
    //*********************************************

    //dodanie obiektu funk(11)
    struct Tensor *p_elem_tens_funk_1 = DodajTensorDoTensora(p_elem_tensora_DD);
    p_elem_tens_funk_1->p_nazwa_tensora_ = "funk";
    struct Indeks *pElemIndeksuFun1 = DodajIndeksDoTensora(p_elem_tens_funk_1);
    (*pElemIndeksuFun1).wartosc_indeksu_ = 0;
    //(*pElemIndeksuFun1).WartoscIndeksu=NULL;
    //doddanie obiektu funk(11)
    struct Tensor *p_elem_tens_funk_2 = DodajTensorDoTensora(p_elem_tens_funk_1);
    p_elem_tens_funk_2->p_nazwa_tensora_ = "funk";
    struct Indeks *pElemIndeksuFun2 = DodajIndeksDoTensora(p_elem_tens_funk_2);
    (*pElemIndeksuFun2).wartosc_indeksu_ = 0;

    //zamiana np. DDD(3) na DD(3)*DD(2)*DD(1)
    ZamienDDDnaIloczynDD(p_elem_sumy_DD);

    //wykonanie pochodnych DD(i) w calym rowaniu
    while (ZnajdzPochodne(&elem_sumy_poczatek_wyrazenia))
    {
        PochRaz2((&elem_sumy_poczatek_wyrazenia));
    };

    //printf("Rownanie \n\n         \
            -1/2*D(%d)*...*D(1)*funk(11)*funk(11)\n\n         \
            po wykonaniu jawnie pochodnych D(i) ma postac:\n\n",wartosciIndeksuDDD);

    //wyswietlenie rownania mozna odkomentowac zeby zobaczyc szybkie dzialanie programu
    // bez bardzo dlugiegowyswietlania wyniku dla duzych pochodnych

    WyswietlCaleRownanie(&elem_sumy_poczatek_wyrazenia);

    printf("\n\nLiczba elementow rownania to: ");
    //wyswietlenie liczby elementow po wykonaniu pochodnych
    WyswietlLiczbeElementowRownania(&elem_sumy_poczatek_wyrazenia);

    printf("\n");

    return 0;
}

