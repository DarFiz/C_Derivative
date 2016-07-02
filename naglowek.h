#ifndef NAGLOWEK_H_INCLUDED
#define NAGLOWEK_H_INCLUDED

struct Indeks
{
    unsigned int wartosc_indeksu_;
    struct Indeks * p_next_indeks_;
};

struct Tensor
{
    char * p_nazwa_tensora_;
    struct Indeks * p_indeks_;
    struct Tensor * p_next_tensor_;
};

struct ElementSumy
{
    struct ElementSumy * p_next_element_sumy_;
    int licznik_;
    int mianownik_;
    struct Tensor * p_tensor_;
};

struct DwaWskDoTensora
{
    struct Tensor *p_poczatek_tens_;
    struct Tensor *p_koniec_tens_;
};

struct ElementSumy  *DodajElementSumy(struct ElementSumy *);
struct Tensor *DodajTensorDoElementSumy(struct ElementSumy  *);
struct Tensor *DodajTensorDoTensora(struct Tensor *);
struct Indeks *DodajIndeksDoTensora(struct Tensor * );
struct DwaWskDoTensora KopiujWyrPomiedzyTens(struct Tensor *, struct Tensor *);
struct ElementSumy *ZnajdzTenZaElemSum(struct ElementSumy *,char *);
struct Tensor *ZnajdzTenZaTenRozny(struct Tensor *,char *);
struct Tensor *KopiujWyrOdTensDoKonca(struct Tensor *);
struct Indeks *DodajIndeksDoIndeks(struct Indeks *);
struct Tensor *ZnajdzTenZaTen(struct Tensor *,char *);
void ZamienDDDnaIloczynDD(struct ElementSumy *);
void PochRaz2(struct ElementSumy *);
void WyswietlCaleRownanie(struct ElementSumy *);
void WyswietlLiczbeElementowRownania(struct ElementSumy *);
void WyswietlElementSumy(struct ElementSumy *);

#endif // NAGLOWEK_H_INCLUDED
