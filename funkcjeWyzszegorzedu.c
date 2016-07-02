#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "naglowek.h"

//funkcja zamienia DDD(5) na DD(5)*DD(4)*DD(3)*DD(2)*DD(1)
void ZamienDDDnaIloczynDD(struct ElementSumy *p_egz_elementu_sumy )
{
    static int licznik=1;
    
    if ( strcmp(p_egz_elementu_sumy->p_tensor_->p_nazwa_tensora_,"DDD") == 0 && p_egz_elementu_sumy->p_tensor_->p_indeks_->wartosc_indeksu_>1)
    {
        int kopia_indeksu = p_egz_elementu_sumy->p_tensor_->p_indeks_->wartosc_indeksu_;
        p_egz_elementu_sumy->p_tensor_->p_indeks_->wartosc_indeksu_ = kopia_indeksu-1;
        struct Tensor *p_egz_dodany_tensor = DodajTensorDoTensora(p_egz_elementu_sumy->p_tensor_);
        p_egz_dodany_tensor->p_nazwa_tensora_="DD";
        struct Indeks *p_egz_indeksu = DodajIndeksDoTensora((p_egz_dodany_tensor));
        p_egz_indeksu->wartosc_indeksu_ = licznik++;
        ZamienDDDnaIloczynDD(p_egz_elementu_sumy);
    }
    else
    {
        p_egz_elementu_sumy->p_tensor_->p_nazwa_tensora_ = "DD";
        p_egz_elementu_sumy->p_tensor_->p_indeks_->wartosc_indeksu_ = licznik;
    }
}

//Pochodne

//funkcja ktora wykonuje na calym rownaniu pochodna ... na kazdym elemencie sumy tylko raz ... nie wykonuje wszystkich pochodnych do konca
void PochRaz2(struct ElementSumy *p_poczatek_wyrazenia)
{

    struct ElementSumy *p_kopia_elem_sumy = p_poczatek_wyrazenia->p_next_element_sumy_;

    while(p_kopia_elem_sumy != NULL)
    {
        if (ZnajdzTenZaElemSum(p_kopia_elem_sumy,"DD") != NULL && p_kopia_elem_sumy->p_tensor_ != NULL && ZnajdzTenZaTenRozny(p_kopia_elem_sumy->p_tensor_,"DD") != NULL)
        {
            struct DwaWskDoTensora p_wskaz_po_DD = KopiujWyrPomiedzyTens(p_kopia_elem_sumy->p_tensor_->p_next_tensor_,p_kopia_elem_sumy->p_tensor_->p_next_tensor_);
            struct DwaWskDoTensora p_wskaz_do_DD = KopiujWyrPomiedzyTens(p_kopia_elem_sumy->p_tensor_,p_kopia_elem_sumy->p_tensor_);
            p_wskaz_po_DD.p_koniec_tens_->p_next_tensor_ = p_wskaz_do_DD.p_poczatek_tens_;
            struct Tensor * p_wskaz_reszta = KopiujWyrOdTensDoKonca(p_kopia_elem_sumy->p_tensor_->p_next_tensor_->p_next_tensor_);
            p_wskaz_po_DD.p_koniec_tens_->p_next_tensor_->p_next_tensor_ = p_wskaz_reszta;
            struct ElementSumy *p_egz_elem_sumy = DodajElementSumy(p_kopia_elem_sumy);
            p_egz_elem_sumy->p_tensor_ = p_wskaz_po_DD.p_poczatek_tens_;
            p_egz_elem_sumy->licznik_ = p_kopia_elem_sumy->licznik_;
            p_egz_elem_sumy->mianownik_ = p_kopia_elem_sumy->mianownik_;
            struct Indeks *p_ind_pom = p_kopia_elem_sumy->p_tensor_->p_next_tensor_->p_indeks_;
          
            while (p_ind_pom->p_next_indeks_ != NULL)
            {
                p_ind_pom=p_ind_pom->p_next_indeks_;
            }
            
            struct Indeks *p_ind1 = DodajIndeksDoIndeks(p_ind_pom);
            p_ind1->wartosc_indeksu_ = p_wskaz_do_DD.p_poczatek_tens_->p_indeks_->wartosc_indeksu_;
            UsunCalyTensZaElemSum(p_kopia_elem_sumy);
            goto KoniecGlownejPetli;
        }
        else if (p_kopia_elem_sumy->p_tensor_ != NULL)
        {
            struct Tensor *p_egz_tensor = p_kopia_elem_sumy->p_tensor_;
            while (p_egz_tensor != NULL && p_egz_tensor->p_next_tensor_->p_next_tensor_ != NULL)
            {
                if (ZnajdzTenZaTen(p_egz_tensor,"DD") != NULL  && p_egz_tensor->p_next_tensor_->p_next_tensor_->p_next_tensor_ != NULL  && p_egz_tensor->p_next_tensor_->p_next_tensor_ != NULL && ZnajdzTenZaTenRozny(p_egz_tensor->p_next_tensor_,"DD") != NULL)
                {
                    struct DwaWskDoTensora  p_wskaz = KopiujWyrPomiedzyTens(p_kopia_elem_sumy->p_tensor_, p_egz_tensor);
                    struct DwaWskDoTensora p_wskaz_po_DD = KopiujWyrPomiedzyTens(p_egz_tensor->p_next_tensor_->p_next_tensor_, p_egz_tensor->p_next_tensor_->p_next_tensor_);
                    struct DwaWskDoTensora p_wskaz_do_DD = KopiujWyrPomiedzyTens(p_egz_tensor->p_next_tensor_, p_egz_tensor->p_next_tensor_);
                    p_wskaz.p_koniec_tens_->p_next_tensor_ = p_wskaz_po_DD.p_poczatek_tens_;
                    p_wskaz_po_DD.p_koniec_tens_->p_next_tensor_ = p_wskaz_do_DD.p_poczatek_tens_;
                    struct Tensor * p_wskaz_reszta = KopiujWyrOdTensDoKonca(p_egz_tensor->p_next_tensor_->p_next_tensor_->p_next_tensor_);
                    p_wskaz_po_DD.p_koniec_tens_->p_next_tensor_->p_next_tensor_ = p_wskaz_reszta;
                    struct ElementSumy * p_elem_sum = DodajElementSumy(p_kopia_elem_sumy);
                    p_elem_sum->p_tensor_ = p_wskaz.p_poczatek_tens_;
                    p_elem_sum->licznik_ = p_kopia_elem_sumy->licznik_;
                    p_elem_sum->mianownik_ = p_kopia_elem_sumy->mianownik_;
                    struct Indeks * p_ind_pom = p_egz_tensor->p_next_tensor_->p_next_tensor_->p_indeks_;
                    
                    while (p_ind_pom->p_next_indeks_ != NULL)
                    {
                        p_ind_pom = p_ind_pom->p_next_indeks_;
                    }
                    
                    struct Indeks * p_ind1 = DodajIndeksDoIndeks(p_ind_pom);
                    p_ind1->wartosc_indeksu_ = p_wskaz_do_DD.p_poczatek_tens_->p_indeks_->wartosc_indeksu_;
                    UsunCalyTensZaTens(p_egz_tensor);
                    goto KoniecGlownejPetli;
                }
                else if (ZnajdzTenZaTen(p_egz_tensor,"DD") != NULL  && p_egz_tensor->p_next_tensor_->p_next_tensor_->p_next_tensor_ == NULL  && 
                            ZnajdzTenZaTenRozny(p_egz_tensor->p_next_tensor_,"DD") != NULL)
                {
                    struct DwaWskDoTensora p_wskaz_do_DD = KopiujWyrPomiedzyTens(p_egz_tensor->p_next_tensor_,p_egz_tensor->p_next_tensor_);
                    struct Indeks *p_ind_pom = p_egz_tensor->p_next_tensor_->p_next_tensor_->p_indeks_;
                    
                    while (p_ind_pom->p_next_indeks_ != NULL)
                    {
                    p_ind_pom = p_ind_pom->p_next_indeks_;
                    }

                    struct Indeks *p_ind1 = DodajIndeksDoIndeks(p_ind_pom);
                    p_ind1->wartosc_indeksu_ = p_wskaz_do_DD.p_poczatek_tens_->p_indeks_->wartosc_indeksu_;
                    UsunCalyTensZaTens(p_egz_tensor);
                    goto KoniecGlownejPetli;
                }

                p_egz_tensor=p_egz_tensor->p_next_tensor_;
            }

        }

        KoniecGlownejPetli:
        p_kopia_elem_sumy=p_kopia_elem_sumy->p_next_element_sumy_;
    }
}

//funkcja przeszukuje cale rownanie jesli isnieja niewykonane pochodne DD(i) wyrzuca true
bool ZnajdzPochodne(struct ElementSumy * p_wsk_do_pocz_wyr)
{
    struct ElementSumy *p_kopia_elem_sum = p_wsk_do_pocz_wyr->p_next_element_sumy_;

    while(p_kopia_elem_sum != NULL)
    {
        if (ZnajdzTenZaElemSum(p_kopia_elem_sum,"DD") != NULL)
        {
            return true;
        }
        else if (p_kopia_elem_sum->p_tensor_ != NULL)
        {
            struct Tensor * p_egz_tensor = p_kopia_elem_sum->p_tensor_;

            while (p_egz_tensor!=NULL && p_egz_tensor->p_next_tensor_!=NULL )
            {
                if (ZnajdzTenZaTen(p_egz_tensor,"DD")!=NULL)
                {
                    return true;
                }
                p_egz_tensor=p_egz_tensor->p_next_tensor_;
            }
        }
        
        p_kopia_elem_sum=p_kopia_elem_sum->p_next_element_sumy_;
    }

    return false;
}

//wyswietlenie calego rownania
void WyswietlCaleRownanie(struct ElementSumy * p_pocz_elem_sumy)
{
    struct ElementSumy *p_elem_sumy = p_pocz_elem_sumy->p_next_element_sumy_;
    
    while(p_elem_sumy!=NULL)
    {
        WyswietlElementSumy(p_elem_sumy);
        p_elem_sumy=p_elem_sumy->p_next_element_sumy_;
    }
}

//wyswietlenie ile elementow ma rownanie
void WyswietlLiczbeElementowRownania(struct ElementSumy * p_wsk_pocz_elem_sum)
{
    struct ElementSumy *p_elem_sum_pomoc = p_wsk_pocz_elem_sum->p_next_element_sumy_;
    int liczba = 0;

    while(p_elem_sum_pomoc!=NULL)
    {
        liczba++;
        p_elem_sum_pomoc=p_elem_sum_pomoc->p_next_element_sumy_;
    }

    printf("%d",liczba);
}