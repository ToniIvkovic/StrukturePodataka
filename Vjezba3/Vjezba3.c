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
// Funkcija za dodavanje novog elementa iza određenog elementa
Osoba* dodajIzaElementa(Osoba* head, char* ime, char* prezime, int godina_rodenja, char* prezime_za_trazenje) {
    Osoba* temp = head;
    while (temp && strcmp(temp->prezime, prezime_za_trazenje) != 0)
        temp = temp->next;

    if (temp) {
        Osoba* nova_osoba = (Osoba*)malloc(sizeof(Osoba));
        if (!nova_osoba) {
            printf("Greška pri alokaciji memorije!\n");
            return head;
        }
        strcpy(nova_osoba->ime, ime);
        strcpy(nova_osoba->prezime, prezime);
        nova_osoba->godina_rodenja = godina_rodenja;
        nova_osoba->next = temp->next;
        temp->next = nova_osoba;
    }
    else {
        printf("Osoba s prezimenom %s nije pronađena.\n", prezime_za_trazenje);
    }
    return head;
}
// Funkcija za dodavanje novog elementa ispred određenog elementa
Osoba* dodajIspredElementa(Osoba* head, char* ime, char* prezime, int godina_rodenja, char* prezime_za_trazenje) {
    Osoba* nova_osoba = (Osoba*)malloc(sizeof(Osoba));
    if (!nova_osoba) {
        printf("Greška pri alokaciji memorije!\n");
        return head;
    }
    strcpy(nova_osoba->ime, ime);
    strcpy(nova_osoba->prezime, prezime);
    nova_osoba->godina_rodenja = godina_rodenja;

    if (head && strcmp(head->prezime, prezime_za_trazenje) == 0) {
        nova_osoba->next = head;
        return nova_osoba;
    }

    Osoba* temp = head;
    while (temp->next && strcmp(temp->next->prezime, prezime_za_trazenje) != 0)
        temp = temp->next;

    if (temp->next) {
        nova_osoba->next = temp->next;
        temp->next = nova_osoba;
    }
    else {
        printf("Osoba s prezimenom %s nije pronađena.\n", prezime_za_trazenje);
        free(nova_osoba);
    }
    return head;
}
// Funkcija za sortiranje liste po prezimenima
Osoba* sortirajPoPrezimenu(Osoba* head) {
    if (!head) return head;

    Osoba* temp1 = head, * temp2 = NULL;
    char tempIme[50], tempPrezime[50];
    int tempGodina;

    while (temp1) {
        temp2 = temp1->next;
        while (temp2) {
            if (strcmp(temp1->prezime, temp2->prezime) > 0) {
                strcpy(tempIme, temp1->ime);
                strcpy(tempPrezime, temp1->prezime);
                tempGodina = temp1->godina_rodenja;

                strcpy(temp1->ime, temp2->ime);
                strcpy(temp1->prezime, temp2->prezime);
                temp1->godina_rodenja = temp2->godina_rodenja;

                strcpy(temp2->ime, tempIme);
                strcpy(temp2->prezime, tempPrezime);
                temp2->godina_rodenja = tempGodina;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return head;
}
// Funkcija za spremanje liste u datoteku
void upisiUDatoteku(Osoba* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Greška pri otvaranju datoteke!\n");
        return;
    }

    Osoba* temp = head;
    while (temp) {
        fprintf(file, "%s %s %d\n", temp->ime, temp->prezime, temp->godina_rodenja);
        temp = temp->next;
    }
    fclose(file);
    printf("Lista je uspješno upisana u datoteku %s.\n", filename);
}
// Funkcija za čitanje liste iz datoteke
Osoba* citajIzDatoteke(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Greška pri otvaranju datoteke!\n");
        return NULL;
    }

    Osoba* head = NULL;
    char ime[50], prezime[50];
    int godina_rodenja;

    while (fscanf(file, "%s %s %d", ime, prezime, &godina_rodenja) != EOF) {
        head = dodajNaKraj(head, ime, prezime, godina_rodenja);
    }
    fclose(file);
    printf("Lista je uspješno učitana iz datoteke %s.\n", filename);
    return head;
}
int main() {
    Osoba* head = NULL;
    int izbor;
    char ime[50], prezime[50], prezime_za_trazenje[50];
    int godina_rodenja;

    do {
        printf("\nOdaberite opciju:\n");
        printf("1. Dodaj na početak\n");
        printf("2. Ispiši listu\n");
        printf("3. Dodaj na kraj\n");
        printf("4. Dodaj iza određenog elementa\n");
        printf("5. Dodaj ispred određenog elementa\n");
        printf("6. Sortiraj po prezimenima\n");
        printf("7. Spremi listu u datoteku\n");
        printf("8. Učitaj listu iz datoteke\n");
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
            printf("Unesite ime: ");
            scanf("%s", ime);
            printf("Unesite prezime: ");
            scanf("%s", prezime);
            printf("Unesite godinu rođenja: ");
            scanf("%d", &godina_rodenja);
            printf("Unesite prezime osobe iza koje želite dodati: ");
            scanf("%s", prezime_za_trazenje);
            head = dodajIzaElementa(head, ime, prezime, godina_rodenja, prezime_za_trazenje);
            break;
        case 5:
            printf("Unesite ime: ");
            scanf("%s", ime);
            printf("Unesite prezime: ");
            scanf("%s", prezime);
            printf("Unesite godinu rođenja: ");
            scanf("%d", &godina_rodenja);
            printf("Unesite prezime osobe ispred koje želite dodati: ");
            scanf("%s", prezime_za_trazenje);
            head = dodajIspredElementa(head, ime, prezime, godina_rodenja, prezime_za_trazenje);
            break;
        case 6:
            head = sortirajPoPrezimenu(head);
            printf("Lista je sortirana po prezimenima.\n");
            break;
        case 7:
            upisiUDatoteku(head, "osobe.txt");
            break;
        case 8:
            head = citajIzDatoteke("osobe.txt");
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
