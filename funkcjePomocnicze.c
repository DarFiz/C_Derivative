#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "naglowek.h"

//funkcja wstawia nowa strukture ElementSumy za strukture p_egz_element_sumy
struct ElementSumy * DodajElementSumy(struct ElementSumy * p_egz_element_sumy)
{
    struct ElementSumy *p_kopia_wskaznika;
    p_kopia_wskaznika = (*p_egz_element_sumy).p_next_element_sumy_;
    (*p_egz_element_sumy).p_next_element_sumy_ = (struct ElementSumy *) malloc(sizeof(struct ElementSumy));
    struct ElementSumy *KopiaNext = (*p_egz_element_sumy).p_next_element_sumy_;
    (*KopiaNext).p_next_element_sumy_ = p_kopia_wskaznika;
    
    return KopiaNext;
}

//funkcja wstawia strukture Tensor "zaraz za ElementSumy"
struct Tensor *DodajTensorDoElementSumy(struct ElementSumy  *p_egz_element_sumy)
{
    struct Tensor *p_kopia_wskaznika;
    p_kopia_wskaznika = p_egz_element_sumy->p_tensor_;
    p_egz_element_sumy->p_tensor_ = malloc(sizeof(struct Tensor));
    struct Tensor *p_kopia_next = p_egz_element_sumy->p_tensor_;
    p_kopia_next->p_next_tensor_ = p_kopia_wskaznika;
    p_kopia_next->p_indeks_ = NULL;
    
    return p_kopia_next;
}

//wstawia tensor za tensorem p_egz_tensora
struct Tensor *DodajTensorDoTensora(struct Tensor *p_egz_tensora)
{
    struct Tensor *p_kopia_wskaznika;
    p_kopia_wskaznika = p_egz_tensora->p_next_tensor_;
    p_egz_tensora->p_next_tensor_ = (struct Tensor *)malloc(sizeof(struct Tensor));
    struct Tensor *p_kopia_next = p_egz_tensora->p_next_tensor_;
    p_kopia_next->p_next_tensor_ = p_kopia_wskaznika;
    p_kopia_next->p_indeks_ = NULL;
    
    return p_kopia_next;
}

//dodaje strukture Indeks do struktury Tensor ("pierwszy indeks tensora")
struct Indeks * DodajIndeksDoTensora(struct Tensor *p_egz_tensora )
{
    struct Indeks *p_kopia_wskaznika;
    p_kopia_wskaznika = p_egz_tensora->p_indeks_;
    p_egz_tensora->p_indeks_ = (struct Indeks *)malloc(sizeof(struct Indeks));
    struct Indeks *p_kopia_next = p_egz_tensora->p_indeks_;
    p_kopia_next->p_next_indeks_ = p_kopia_wskaznika;

    return p_kopia_next;
}

//wstawia strukture Indeks za struktura Indeks o wskazniku p_egz_indeksu
struct Indeks *DodajIndeksDoIndeks(struct Indeks *p_egz_indeksu )
{
    struct Indeks *p_kopia_wskaznika;
    p_kopia_wskaznika = p_egz_indeksu->p_next_indeks_;
    p_egz_indeksu->p_next_indeks_ = (struct Indeks *)malloc(sizeof(struct Indeks));
    struct Indeks *p_kopia_next = p_egz_indeksu->p_next_indeks_;
    p_kopia_next->p_next_indeks_ = p_kopia_wskaznika;
    
    return p_kopia_next;
}

//usuniecie struktury Indeks za struktura Indeks o adresie p_egz_indeksu
bool UsunIndeksZaIndeksem(struct Indeks *p_egz_indeksu)
{
    if ((p_egz_indeksu->p_next_indeks_) != NULL)
    {
        struct Indeks *p_kopia_wskaznika;
        p_kopia_wskaznika = p_egz_indeksu->p_next_indeks_->p_next_indeks_;
        free(p_egz_indeksu->p_next_indeks_);
        p_egz_indeksu->p_next_indeks_ = p_kopia_wskaznika;
        
        return true;
    }
    else
    {
        return false;
    }
}

//usuniecie struktury Indeks za struktura Tensor o adresie p_egz_tensora (usuniecie pierwszego indeksu)
bool UsunIndeksZaTensorem(struct Tensor * p_egz_tensora)
{
    if ((p_egz_tensora->p_indeks_) != NULL)
    {
        struct Indeks *p_kopia_wskaznika;
        p_kopia_wskaznika = p_egz_tensora->p_indeks_->p_next_indeks_;
        free(p_egz_tensora->p_indeks_);
        p_egz_tensora->p_indeks_ = p_kopia_wskaznika;
        
        return true;
    }
    else
    {
        return false;
    }
}

//usuniecie tensora za tensorem
bool UsunTensorZaTensorem(struct Tensor * p_egz_tensora)
{
    if (((p_egz_tensora->p_next_tensor_) != NULL) && ((p_egz_tensora->p_next_tensor_->p_indeks_) == NULL))
    {
        struct Tensor * p_kopia_wskaznika;
        p_kopia_wskaznika = p_egz_tensora->p_next_tensor_->p_next_tensor_;
        free(p_egz_tensora->p_next_tensor_);
        p_egz_tensora->p_next_tensor_ = p_kopia_wskaznika;
        return true;
    }
    else
    {
        return false;
    }
}

//usniecie pierwszego tensora za elementem sumy
bool UsunTensorZaElementemSumy(struct ElementSumy *p_egz_elementu_sumy)
{
    if (((p_egz_elementu_sumy->p_tensor_) != NULL) && ((p_egz_elementu_sumy->p_tensor_->p_indeks_) == NULL))
    {
        struct Tensor *p_kopia_wskaznika;
        p_kopia_wskaznika = p_egz_elementu_sumy->p_tensor_->p_next_tensor_;
        free(p_egz_elementu_sumy->p_tensor_);
        p_egz_elementu_sumy->p_tensor_ = p_kopia_wskaznika;
        return true;
    }
    else
    {
        return false;
    }
}

//usuniecie elementu sumy
bool UsunElementSumyZaElementemSumy(struct ElementSumy * p_egz_elementu_sumy)
{
    if (((p_egz_elementu_sumy->p_next_element_sumy_) != NULL))
    {
        struct ElementSumy * p_kopia_wskaznika;
        p_kopia_wskaznika = p_egz_elementu_sumy->p_next_element_sumy_->p_next_element_sumy_;
        free(p_egz_elementu_sumy->p_next_element_sumy_);
        p_egz_elementu_sumy->p_next_element_sumy_ = p_kopia_wskaznika;
        
        return true;
    }
    else
    {
        return false;
    }
}

//usuniecie tensora za elemtemsumy przy czym uprzednio "usuniete" sa rowniez wszystkie jego indeksy
void UsunCalyTensZaElemSum(struct ElementSumy *p_wsk_do_el_sum)
{
    while (UsunIndeksZaTensorem(p_wsk_do_el_sum->p_tensor_))
    {

    }
    bool zm1 = UsunTensorZaElementemSumy(p_wsk_do_el_sum);
}

//podobnie jak wyzej ale tensora za tensorem
void UsunCalyTensZaTens(struct Tensor * p_wsk_do_tens)
{
    while (UsunIndeksZaTensorem(p_wsk_do_tens->p_next_tensor_))
    {

    }

    bool zm2=UsunTensorZaTensorem(p_wsk_do_tens);
   // printf("%d\n\n",zm2);
}

///////////////////////////
///////////////////////////

//sprawdzenie czy za struktura elementsumy o wskazniku p_wsk_elem_sum "stoi" tensor o nazwie p_nazwa_tens
struct ElementSumy *ZnajdzTenZaElemSum(struct ElementSumy * p_wsk_elem_sum,char * p_nazwa_tens)
{
    if (strcmp(p_wsk_elem_sum->p_tensor_->p_nazwa_tensora_,p_nazwa_tens)==0)
    {
        return p_wsk_elem_sum;
    }
    else
    {
        return NULL;
    }
}

//sprawdzenie czy za struktura tensor o wskazniku p_wsk_tens "stoi" tensor o nazwie p_nazwa_tens
struct Tensor * ZnajdzTenZaTen(struct Tensor *p_wsk_tens,char * p_nazwa_tens)
{
    if (strcmp(p_wsk_tens->p_next_tensor_->p_nazwa_tensora_,p_nazwa_tens) == 0)
    {
        return p_wsk_tens;
    }
    else
    {
        return NULL;
    }
}

//sprawdzenie czy za struktura tensor o wskazniku p_wsk_tens "stoi" tensor rozny od nazwy p_nazwa_tens
struct Tensor * ZnajdzTenZaTenRozny(struct Tensor * p_wsk_tens,char * p_nazwa_tens)
{
    if (strcmp(p_wsk_tens->p_next_tensor_->p_nazwa_tensora_,p_nazwa_tens) != 0)
    {
        return p_wsk_tens;
    }
    else
    {
        return NULL;
    }
}

//sprawdzenie czy za struktura tensor o wskazniku p_wsk_tens "stoi" indeks o nazwie p_nazwa_ind
struct Tensor * ZnajdzIndZaTen(struct Tensor * p_wsk_tens, int p_nazwa_ind)
{
    if (p_wsk_tens->p_indeks_->wartosc_indeksu_ == p_nazwa_ind)
    {
        return p_wsk_tens;
    }
    else
    {
        return NULL;
    }
}

//sprawdzenie czy za struktura Indeks o wskazniku p_wsk_ind "stoi" indeks o nazwie p_nazwa_ind
struct Indeks *ZnajdzIndZaInd(struct Indeks * p_wsk_ind,int p_nazwa_ind)
{
    if (p_wsk_ind->p_next_indeks_->wartosc_indeksu_ == p_nazwa_ind)
    {
        return p_wsk_ind;
    }
    else
    {
        return NULL;
    }
}

//////////////////////////////
/////////////////////////////

//funkcja kopiuje wszystkie indeksu ktorych poczatkiem jest wskanik p_wsk_do_indeksu
//zwraca wskaznik do poczatkowego skopiowanego indeksu
struct Indeks *KopiujIndeksy(struct Indeks *p_wsk_do_indeksu)
{
    struct Indeks *p_wsk_nowy_indeks,*p_wsk_nowy_indeks_pomoc;

    if (p_wsk_do_indeksu != NULL)
    {
        p_wsk_nowy_indeks = (struct Indeks *)malloc(sizeof(struct Indeks));
        *p_wsk_nowy_indeks = *p_wsk_do_indeksu;
        p_wsk_nowy_indeks_pomoc = p_wsk_nowy_indeks;
    }

    while (p_wsk_do_indeksu->p_next_indeks_ != NULL)
    {
        p_wsk_nowy_indeks_pomoc->p_next_indeks_ = (struct Indeks *)malloc(sizeof(struct Indeks));
        *(p_wsk_nowy_indeks_pomoc->p_next_indeks_) = *(p_wsk_do_indeksu->p_next_indeks_);
        p_wsk_do_indeksu = p_wsk_do_indeksu->p_next_indeks_;
        p_wsk_nowy_indeks_pomoc = p_wsk_nowy_indeks_pomoc->p_next_indeks_;
    }
    
    p_wsk_nowy_indeks_pomoc->p_next_indeks_ = NULL;

    return p_wsk_nowy_indeks;
}

//kopiowanie wszystkich tensorow pomiedzy tensorami p_wsk_pocz_tens i p_wsk_koni_tens
//wynikiem sa dwa wskazniki poczatkowy i koncowy reprezentowane przez strukture DwaWskDoTensora (patrz naglowek.h)
struct DwaWskDoTensora KopiujWyrPomiedzyTens(struct Tensor * p_wsk_pocz_tens, struct Tensor * p_wsk_koni_tens)
{
    struct Tensor *p_wsk_nowy_do_pocz_tens, *p_wsk_nowy_do_konc_tens, *p_wsk_pomocniczy, *p_wsk_pomocniczy2;
    p_wsk_nowy_do_pocz_tens = (struct Tensor *)malloc(sizeof(struct Tensor));
    *p_wsk_nowy_do_pocz_tens = *p_wsk_pocz_tens;
    p_wsk_nowy_do_pocz_tens->p_indeks_ = KopiujIndeksy(p_wsk_pocz_tens->p_indeks_);
    p_wsk_pomocniczy = p_wsk_nowy_do_pocz_tens;
    p_wsk_pomocniczy2 = p_wsk_pocz_tens;

    if (p_wsk_pocz_tens != p_wsk_koni_tens)
    {
        do
        {
            p_wsk_pomocniczy->p_next_tensor_=(struct Tensor *)malloc(sizeof(struct Tensor));
            p_wsk_pomocniczy = p_wsk_pomocniczy->p_next_tensor_;
            p_wsk_pomocniczy2 = p_wsk_pomocniczy2->p_next_tensor_;
            *p_wsk_pomocniczy = *p_wsk_pomocniczy2;
            p_wsk_pomocniczy->p_indeks_ = KopiujIndeksy(p_wsk_pomocniczy2->p_indeks_);
            //printf("%s\n",WskPomocniczy2!=WskKoniTens?"tr":"fals");
        }       
        while(p_wsk_pomocniczy2 != p_wsk_koni_tens);
    }

    p_wsk_nowy_do_konc_tens = p_wsk_pomocniczy;
    p_wsk_nowy_do_konc_tens->p_next_tensor_ = NULL;
    struct DwaWskDoTensora p_wsk_pocz_i_koniec = {p_wsk_nowy_do_pocz_tens, p_wsk_nowy_do_konc_tens};

    return p_wsk_pocz_i_koniec;
}

//kopiowanie tensorow zaczynajacych sie od wskaznika p_wsk_pocz_tens
//wynikiem jest poczatkowy wskaznik do kopii tensorow
struct Tensor * KopiujWyrOdTensDoKonca(struct Tensor *p_wsk_pocz_tens)
{
    struct Tensor *p_wsk_nowy_do_pocz_tens, *p_wsk_pomocniczy, *p_wsk_pomocniczy_2;
    p_wsk_nowy_do_pocz_tens = (struct Tensor *)malloc(sizeof(struct Tensor));
    *p_wsk_nowy_do_pocz_tens = *p_wsk_pocz_tens;
    p_wsk_nowy_do_pocz_tens->p_indeks_ = KopiujIndeksy(p_wsk_pocz_tens->p_indeks_);
    p_wsk_pomocniczy = p_wsk_nowy_do_pocz_tens;
    p_wsk_pomocniczy_2 = p_wsk_pocz_tens;

    while(p_wsk_pomocniczy_2->p_next_tensor_ != NULL)
    {
        p_wsk_pomocniczy->p_next_tensor_ = (struct Tensor *)malloc(sizeof(struct Tensor));
        p_wsk_pomocniczy = p_wsk_pomocniczy->p_next_tensor_;
        p_wsk_pomocniczy_2 = p_wsk_pomocniczy_2->p_next_tensor_;
        *p_wsk_pomocniczy = *p_wsk_pomocniczy_2;
        p_wsk_pomocniczy->p_indeks_ = KopiujIndeksy(p_wsk_pomocniczy_2->p_indeks_);
    }

    p_wsk_pomocniczy->p_next_tensor_ = NULL;

    return p_wsk_nowy_do_pocz_tens;
}

///////////////////////////
///////////////////////////

//wyswietlenie jednego tensora z indeksami
void WyswietlTensor(struct Tensor *p_wskaznik_egz_tensora )
{
    printf("%s(",p_wskaznik_egz_tensora->p_nazwa_tensora_);
    struct Indeks *p_wskaz_ind = p_wskaznik_egz_tensora->p_indeks_;

    if (p_wskaz_ind != NULL)
    {
        printf("%d",p_wskaz_ind->wartosc_indeksu_);
        p_wskaz_ind=p_wskaz_ind->p_next_indeks_;
    }

    while(p_wskaz_ind != NULL)
    {
        printf(",%d",p_wskaz_ind->wartosc_indeksu_);
        p_wskaz_ind = p_wskaz_ind->p_next_indeks_;
    }
    
    printf(")");
}

//wyswietlenie calego elementu sumy
void WyswietlElementSumy(struct ElementSumy *p_wskaznik_element_sumy)
{
    printf("%d/%d",p_wskaznik_element_sumy->licznik_, p_wskaznik_element_sumy->mianownik_);
    struct Tensor *p_wskaz_ten = p_wskaznik_element_sumy->p_tensor_;

    while (p_wskaz_ten != NULL)
    {
        printf("*");
        WyswietlTensor(p_wskaz_ten);
        p_wskaz_ten=p_wskaz_ten->p_next_tensor_;
    }
}
