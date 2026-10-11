#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024
#define MAX_SIZE 50
#define FILE_ERROR -1
#define ALLOC_ERROR -2

// Struktura studenata
typedef struct {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int bodovi;
} Stud;

int main() {
	int brojac = 0;
	char buffer[MAX_LINE] = { 0 };
	FILE* fp = NULL;
	Stud* student = NULL;
	int i = 0;
	int max_bodovi = 0;

	// Otvaranje datoteke
	fp = fopen("popis.txt", "r");
	if (!fp) {
		printf("Greska pri otvaranju datoteke!\n");
		return FILE_ERROR;
	}

	// Brojanje redaka u datoteci
	while (fgets(buffer, MAX_LINE, fp) != NULL) {
		brojac++;
	}

	if (brojac == 0) {
		printf("Datoteka je prazna!\n");
		fclose(fp);
		return FILE_ERROR;
	}

	// Dinamièka alokacija memorije za niz studenata
	student = (Stud*)malloc(brojac * sizeof(Stud));
	if (!student) {
		printf("Greška pri alokaciji memorije!\n");
		fclose(fp);
		return ALLOC_ERROR;
	}

	// Vraæanje pokazivaèa na poèetak datoteke radi ponovnog èitanja 	
	rewind(fp);

	// Uèitavanje podataka o studentima iz datoteke
	i = 0;
	while (fscanf(fp, "%s %s %d", student[i].ime, student[i].prezime, &student[i].bodovi) == 3) {
		if (student[i].bodovi > max_bodovi) {
			max_bodovi = student[i].bodovi;
		}
		i++;
	}
	int stvarni_broj = i;

	//Zatvaranje datoteke nakon èitanja 
	fclose(fp);

	//ispis studenata na ekran
	printf("\n--- POPIS STUDENATA ---\n");
	printf("%-15s %-15s %-10s %-10s\n", "IME", "PREZIME", "APS.BODOVI", "REL.BODOVI (%)");
	printf("-------------------------------------------------------------\n");

	for (i = 0; i < stvarni_broj; i++) {
		double relativni_bodovi = 0.0;
		if (max_bodovi > 0) {
			relativni_bodovi = ((double)student[i].bodovi / max_bodovi) * 100.0;

		}
		printf("%-15s %-15s %-10d %.2f%%\n",
			student[i].ime, student[i].prezime, student[i].bodovi, relativni_bodovi);
	}

	free(student);
	return 0;
}

