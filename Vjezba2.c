#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
    char ime[50];
    char prezime[50];
    int godina_rodenja;
    struct Osoba* next;
} Osoba;
// Funkcija za dodavanje novog elementa na početak liste
Osoba* dodajNaPocetak(Osoba* head, char* ime, char* prezime, int godina_rodenja) {
    Osoba* nova_osoba = (Osoba*)malloc(sizeof(Osoba));
    if (!nova_osoba) {
        printf("Greška pri alokaciji memorije!\n");
        return head;
    }
    strcpy(nova_osoba->ime, ime);
    strcpy(nova_osoba->prezime, prezime);
    nova_osoba->godina_rodenja = godina_rodenja;
    nova_osoba->next = head;
    return nova_osoba;
}
// Funkcija za ispis liste
void ispisiListu(Osoba* head) {
    Osoba* temp = head;
    while (temp) {
        printf("Ime: %s, Prezime: %s, Godina rođenja: %d\n", temp->ime, temp->prezime, temp->godina_rodenja);
        temp = temp->next;
    }
}
// Funkcija za dodavanje novog elementa na kraj liste
Osoba* dodajNaKraj(Osoba* head, char* ime, char* prezime, int godina_rodenja) {
    Osoba* nova_osoba = (Osoba*)malloc(sizeof(Osoba));
    if (!nova_osoba) {
        printf("Greška pri alokaciji memorije!\n");
        return head;
    }
    strcpy(nova_osoba->ime, ime);
    strcpy(nova_osoba->prezime, prezime);
    nova_osoba->godina_rodenja = godina_rodenja;
    nova_osoba->next = NULL;
    if (head == NULL)
        return nova_osoba;

    Osoba* temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = nova_osoba;
    return head;
}
// Funkcija za pronalazak elementa u listi prema prezimenu
Osoba* pronadiElement(Osoba* head, char* prezime) {
    Osoba* temp = head;
    while (temp) {
        if (strcmp(temp->prezime, prezime) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
// Funkcija za brisanje određenog elementa iz liste prema prezimenu
Osoba* obrisiElement(Osoba* head, char* prezime) {
    Osoba* temp = head, * prev = NULL;

    while (temp && strcmp(temp->prezime, prezime) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Osoba s prezimenom %s nije pronađena.\n", prezime);
        return head;
    }
    if (!prev) {
        head = temp->next;
    }
    else {
        prev->next = temp->next;
    }
    free(temp);
    return head;
}
int main() {
    Osoba* head = NULL;
    int izbor;
    char ime[50], prezime[50];
    int godina_rodenja;
    do {
        printf("\nOdaberite opciju:\n");
        printf("1. Dodaj na početak\n");
        printf("2. Ispiši listu\n");
        printf("3. Dodaj na kraj\n");
        printf("4. Pronađi po prezimenu\n");
        printf("5. Obriši po prezimenu\n");
        printf("0. Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor);
        switch (izbor) {
        case 1:
            printf("Unesite ime: ");
            scanf("%s", ime);
            printf("Unesite prezime: ");
            scanf("%s", prezime);
            printf("Unesite godinu rođenja: ");
            scanf("%d", &godina_rodenja);
            head = dodajNaPocetak(head, ime, prezime, godina_rodenja);
            break;
        case 2:
            ispisiListu(head);
            break;
        case 3:
            printf("Unesite ime: ");
            scanf("%s", ime);
            printf("Unesite prezime: ");
            scanf("%s", prezime);
            printf("Unesite godinu rođenja: ");
            scanf("%d", &godina_rodenja);
            head = dodajNaKraj(head, ime, prezime, godina_rodenja);
            break;
        case 4:
            printf("Unesite prezime za pretragu: ");
            scanf("%s", prezime);
            Osoba* pronadena = pronadiElement(head, prezime);
            if (pronadena)
                printf("Pronađena osoba - Ime: %s, Prezime: %s, Godina rođenja: %d\n", pronadena->ime, pronadena->prezime, pronadena->godina_rodenja);
            else
                printf("Osoba s prezimenom %s nije pronađena.\n", prezime);
            break;
        case 5:
            printf("Unesite prezime za brisanje: ");
            scanf("%s", prezime);
            head = obrisiElement(head, prezime);
            break;
        case 0:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Pogrešan unos, pokušajte ponovno.\n");
        }
    } while (izbor != 0);
    while (head) {
        Osoba* temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}
