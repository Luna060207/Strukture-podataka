#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50
#define EXIT_SUCCESS 0
#define MALLOC_ERROR -1

struct _person;
typedef struct _person* Position;

typedef struct _person {
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
} Person;

// Deklaracije funkcija
Position createPerson();
int insertBegin(Position head);
int printList(Position current);
int insertEnd(Position head);
Position findPerson(Position current, char* surname);
int deletePerson(Position head, char* surname);
int deleteList(Position head);

int main() {
    Person head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };
    char choice = 0;
    char searchSurname[MAX_SIZE];
    Position found = NULL;

    do {
        printf("\n--- IZABERI OPERACIJU ---\n");
        printf("1 - Dodaj na pocetak liste (A)\n");
        printf("2 - Ispisi listu (B)\n");
        printf("3 - Dodaj na kraj liste (C)\n");
        printf("4 - Pronadji osobu po prezimenu (D)\n");
        printf("5 - Brisi osobu po prezimenu (E)\n");
        printf("0 - Izlaz\n");
        printf("Izbor: ");
        scanf(" %c", &choice);

        switch (choice) {
        case '1':
            insertBegin(&head);
            break;
        case '2':
            printf("\nSadrzaj liste:\n");
            printList(head.next);
            break;
        case '3':
            insertEnd(&head);
            break;
        case '4':
            printf("Unesi prezime za pretragu: ");
            scanf(" %s", searchSurname);
            found = findPerson(head.next, searchSurname);
            if (found != NULL) {
                printf("Pronadjena osoba: %s %s, roden(a) %d.\n", found->name, found->surname, found->birthYear);
            }
            else {
                printf("Osoba s prezimenom '%s' nije pronadjena.\n", searchSurname);
            }
            break;
        case '5':
            printf("Unesi prezime osobe koju zelis obrisati: ");
            scanf(" %s", searchSurname);
            deletePerson(&head, searchSurname);
            break;
        case '0':
            printf("Izlaz iz programa...\n");
            break;
        default:
            printf("Krivi unos, pokusaj ponovno.\n");
        }
    } while (choice != '0');

    // Oslobaðanje memorije prije izlaza
    deleteList(&head);

    return EXIT_SUCCESS;
}

// Funkcija za stvaranje i alokaciju novog èvora
Position createPerson() {
    Position newPerson = (Position)malloc(sizeof(Person));
    if (!newPerson) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }

    printf("Unesi ime: ");
    scanf(" %s", newPerson->name);
    printf("Unesi prezime: ");
    scanf(" %s", newPerson->surname);
    printf("Unesi godinu rodenja: ");
    scanf(" %d", &newPerson->birthYear);

    newPerson->next = NULL;
    return newPerson;
}

// A. Dinamièki dodaje novi element na poèetak liste
int insertBegin(Position head) {
    Position newPerson = createPerson();
    if (!newPerson) return MALLOC_ERROR;

    newPerson->next = head->next;
    head->next = newPerson;

    printf("Osoba uspjesno dodana na pocetak!\n");
    return EXIT_SUCCESS;
}

// B. Ispisuje listu
int printList(Position current) {
    if (current == NULL) {
        printf("\tLista je prazna!\n");
        return EXIT_SUCCESS;
    }

    while (current != NULL) {
        printf("\tIme: %s, Prezime: %s, Godina rodenja: %d\n", current->name, current->surname, current->birthYear);
        current = current->next;
    }
    return EXIT_SUCCESS;
}

// C. Dinamièki dodaje novi element na kraj liste
int insertEnd(Position head) {
    Position newPerson = createPerson();
    if (!newPerson) return MALLOC_ERROR;

    while (head->next != NULL) {
        head = head->next;
    }

    head->next = newPerson;
    printf("Osoba uspjesno dodana na kraj!\n");
    return EXIT_SUCCESS;
}

// D. Pronalazi element u listi (po prezimenu)
Position findPerson(Position current, char* surname) {
    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// E. Briše odreðeni element iz liste
int deletePerson(Position head, char* surname) {
    Position prev = head;
    Position current = head->next;

    while (current != NULL && strcmp(current->surname, surname) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Osoba s prezimenom '%s' ne postoji u listi.\n", surname);
        return EXIT_SUCCESS;
    }

    prev->next = current->next;
    free(current);
    printf("Osoba uspjesno obrisana iz liste.\n");

    return EXIT_SUCCESS;
}

// Pomoæna funkcija za potpuno brisanje liste (èišæenje memorije)
int deleteList(Position head) {
    Position temp = NULL;
    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
    return EXIT_SUCCESS;
}