#include "pch.h"
#include<stdio.h>
#include<stdlib.h>

struct STUDENT {
	char nume[20];
	float* note;
	int nr_note;
};

void main() 
{
	STUDENT* studenti;
	int nr_studenti = 0;
	//deschidere fisier
	FILE* fisier;
	fopen_s(&fisier, "catalog.txt", "r");
	if (fisier != NULL && !feof(fisier)) {
		//preluare numar studenti din fisier
		fscanf_s(fisier, "%d", &nr_studenti);
		//alocare vector dinamic studenti cu numarul din fisier
		studenti = (STUDENT*)malloc(sizeof(STUDENT)*nr_studenti);
		//parcurgere fisier de la 0<nr_studenti
		for (int i = 0; i < nr_studenti; i++) {
			//citire nume student pozitia i
			fgetc(fisier);//curata zona tampon
			fgets(studenti[i].nume, 20, fisier);
			//initializare note student + citire din fisier
			studenti[i].nr_note = 5;
			//alocare dinamica vectorul de note ale 
			//studentului de pe pozitia i
			studenti[i].note = (float*)malloc(sizeof(float) * 5);
			for (int j = 0; j < studenti[i].nr_note; j++) {
				//preluare din fisier nota de pe pozitia j 
				//a studentului de pe pozitia i
				fscanf_s(fisier, "%f", &studenti[i].note[j]);
			}
		}
		//adaugare student de la tastatura
		fclose(fisier);
		printf("\nAfisare la consola studenti\n");
		for (int i = 0; i < nr_studenti; i++) {
			//afisare nume student
			printf("\nNume student: %s", studenti[i].nume);
			//afisare note
			for (int j = 0; j < studenti[i].nr_note; j++) {
				printf("\nNote[%d] = %f", j, studenti[i].note[j]);
			}
		}

		printf("\nScriere fisier nume student + media notelor\n");
		fopen_s(&fisier, "rezultat_2.txt", "w");
		if (fisier != NULL) {
			//accesez fiecare student
			for (int i = 0; i < nr_studenti; i++) {
				//calcul medie
				float media = 0;
				for (int j = 0; j < studenti[i].nr_note; j++) {
					media = media + studenti[i].note[j];
				}
				media = media / studenti[i].nr_note;
				//scriere nume student fisier
				fprintf(fisier, "%s", studenti[i].nume);
				//scriere medie in fisier
				fprintf(fisier, "%f\n", media);
			}
			fclose(fisier);
		}
		//dezalocare vector dinamic
		for (int i = 0; i < nr_studenti; i++) {
			//dezalocare note
			free(studenti[i].note);
		}
		free(studenti);
	}
	else {
		printf("\nFisierul nu s-a putut deschide\n");
	}
}