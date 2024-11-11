#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Polinom {
    int koeficijent;
    int eksponent;
    struct Polinom* sljedeci;
} Polinom;

Polinom* noviClan(int koeficijent, int eksponent) {
    Polinom* novi = (Polinom*)malloc(sizeof(Polinom));
    novi->koeficijent = koeficijent;
    novi->eksponent = eksponent;
    novi->sljedeci = NULL;
    return novi;
}

void dodajClan(Polinom** glava, int koeficijent, int eksponent) {
    Polinom* novi = noviClan(koeficijent, eksponent);
    Polinom* trenutni = *glava, * prethodni = NULL;

    while (trenutni != NULL && trenutni->eksponent > eksponent) {
        prethodni = trenutni;
        trenutni = trenutni->sljedeci;
    }

    if (trenutni != NULL && trenutni->eksponent == eksponent) {
        trenutni->koeficijent += koeficijent;
        free(novi);
    }
    else {
        if (prethodni == NULL) {
            novi->sljedeci = *glava;
            *glava = novi;
        }
        else {
            prethodni->sljedeci = novi;
            novi->sljedeci = trenutni;
        }
    }
}
Polinom* ucitajPolinom(char* nazivDatoteke) {
    FILE* datoteka = fopen(nazivDatoteke, "r");
    if (datoteka == NULL) {
        printf("Greska: Nije moguće otvoriti datoteku.\n");
        return NULL;
    }

    Polinom* polinom = NULL;
    int koeficijent, eksponent;

    while (fscanf(datoteka, "%d %d", &koeficijent, &eksponent) != EOF) {
        dodajClan(&polinom, koeficijent, eksponent);
    }

    fclose(datoteka);
    return polinom;
}

void ispisiPolinom(Polinom* polinom) {
    while (polinom != NULL) {
        printf("%dx^%d ", polinom->koeficijent, polinom->eksponent);
        polinom = polinom->sljedeci;
        if (polinom != NULL) printf("+ ");
    }
    printf("\n");
}

Polinom* zbrojiPolinome(Polinom* p1, Polinom* p2) {
    Polinom* rezultat = NULL;
    while (p1 != NULL) {
        dodajClan(&rezultat, p1->koeficijent, p1->eksponent);
        p1 = p1->sljedeci;
    }
    while (p2 != NULL) {
        dodajClan(&rezultat, p2->koeficijent, p2->eksponent);
        p2 = p2->sljedeci;
    }
    return rezultat;
}
Polinom* pomnoziPolinome(Polinom* p1, Polinom* p2) {
    Polinom* rezultat = NULL;
    for (Polinom* i = p1; i != NULL; i = i->sljedeci) {
        for (Polinom* j = p2; j != NULL; j = j->sljedeci) {
            int noviKoeficijent = i->koeficijent * j->koeficijent;
            int noviEksponent = i->eksponent + j->eksponent;
            dodajClan(&rezultat, noviKoeficijent, noviEksponent);
        }
    }
    return rezultat;
}

void oslobodiPolinom(Polinom* polinom) {
    while (polinom != NULL) {
        Polinom* temp = polinom;
        polinom = polinom->sljedeci;
        free(temp);
    }
}

int main() {
    Polinom* p1, * p2, * zbroj, * umnozak;

    p1 = ucitajPolinom("polinom1.txt");
    p2 = ucitajPolinom("polinom2.txt");

    printf("Prvi polinom: ");
    ispisiPolinom(p1);

    printf("Drugi polinom: ");
    ispisiPolinom(p2);

    zbroj = zbrojiPolinome(p1, p2);
    printf("Zbroj polinoma: ");
    ispisiPolinom(zbroj);

    umnozak = pomnoziPolinome(p1, p2);
    printf("Umnozak polinoma: ");
    ispisiPolinom(umnozak);

    oslobodiPolinom(p1);
    oslobodiPolinom(p2);
    oslobodiPolinom(zbroj);
    oslobodiPolinom(umnozak);

    return 0;
}
