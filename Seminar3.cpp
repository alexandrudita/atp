#include <stdio.h>
#include<stdlib.h>

float* citire_vector_tastatura(int& n) {
	printf("\nCitire verctor:\n");
	printf("\nDimensiune: ");
	//citire dimensiune vector
	scanf_s("%d", &n);
	//alocare vector dinamic
	float* vector = (float*)malloc(sizeof(float)*n);
	for (int i = 0; i < n; i++) {
		printf("\nvector[%d]= ", i);
		scanf_s("%f", &vector[i]);
	}
	return vector;
}

int nr_elemente_fis_binar(FILE* fisier,
	int lungime) {
	int n, p;
	p = ftell(fisier);
	//pozitionar final fisier
	fseek(fisier, 0, SEEK_END);
	//determinare dimensiune vector
	n = ftell(fisier) / lungime;
	//repozitionare in locul initial
	fseek(fisier, p, SEEK_SET);
	return n;
}
void scriere_vector_binar_sec(FILE* fisier,
	float* vector, int n) {
	//verificare fisier deschis
	if (fisier != NULL) {
		//parcurgere vector si scriere
		for (int i = 0; i < n; i++) {
			fwrite(&vector[i], sizeof(float), 1, fisier);
		}
		//inchidere fisier
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu s-a putut deschide");
	}
}

float* citire_vect_fisier_binar(FILE* fisier,
	int& n) {
	//verificare deschidere fisier
	if (fisier != NULL) {
		//calculam dimensiunea vectorului
		n = nr_elemente_fis_binar(fisier, sizeof(float));
		//alocare dinamica vector 
		float* vector = (float*)malloc(sizeof(float)*n);
		//citire valori din fisier
		for (int i = 0; i < n; i++) {
			fread(&vector[i], sizeof(float), 1, fisier);
		}
		//inchidere fisier
		fclose(fisier);
		return vector;
	}
	else {
		printf("\nFisierul nu s-a deschis");
	}
}

void afisare_vector_tastatura(float* vector, int n) {
	printf("\nAfisare vector\n");
	for (int i = 0; i < n; i++) {
		printf("\nvector[%d] = %f", i, vector[i]);
	}
}

void sortare(float** vector, int nr) {
	for (int i = 0; i < nr-1; i++) {
		for (int j = i + 1; j < nr; j++) {
			if ((*vector)[i] > (*vector)[j]) {
				float temp = (*vector)[j];
				(*vector)[j] = (*vector)[i];
				(*vector)[i] = temp;
			}
		}
	}
}

void interclasare_fisier_binare(FILE* fisier1, FILE* fisier2, FILE* rezultat) {
	if (fisier1 != NULL && fisier2 != NULL && rezultat != NULL) {//verificam daca cele 3 fisiere sunt deschise corect
		//citim primele elemente din cele doua fisiere
		float x, y;
		fread(&x, sizeof(float), 1, fisier1);
		fread(&y, sizeof(float), 1, fisier2);
		//cat timp nu am ajuns la finalul unui fisier verific conditia de interclasare si citesc elementul urmator
		while (!feof(fisier1) && !feof(fisier2)) {
			//conditia de interclasare - pastram sortarea crescatoare si in fisierul rezultat
			if (x < y) {
				fwrite(&x, sizeof(float), 1, rezultat);
				fread(&x, sizeof(float), 1, fisier1);
			}
			else {
				fwrite(&y, sizeof(float), 1, rezultat);
				fread(&y, sizeof(float), 1, fisier2);
			}
		}
		//verific daca mai pot citi din fisier1
		while (!feof(fisier1)) {
			fwrite(&x, sizeof(float), 1, rezultat);
			fread(&x, sizeof(float), 1, fisier1);
		}
		//verific daca mai pot citi din fisier2
		while (!feof(fisier2)) {
			fwrite(&y, sizeof(float), 1, rezultat);
			fread(&y, sizeof(float), 1, fisier2);
		}
		//inchide fisierele
		fclose(fisier1);
		fclose(fisier2);
		fclose(rezultat);
	}
}


void main() {
	int nr1 = 0;
	int nr2 = 0;
	float* vector1 = citire_vector_tastatura(nr1);
	float* vector2 = citire_vector_tastatura(nr2);
	if (nr1 > 0 && nr2 > 0) {
		sortare(&vector1, nr1);
		sortare(&vector2, nr2);
		FILE *fisier1, *fisier2, *rezultat;
		fopen_s(&fisier1, "vector1.dat", "wb");
		scriere_vector_binar_sec(fisier1, vector1, nr1);
		fopen_s(&fisier2, "vector2.dat", "wb");
		scriere_vector_binar_sec(fisier2, vector2, nr2);
		fopen_s(&fisier1, "vector1.dat", "rb");
		fopen_s(&fisier2, "vector2.dat", "rb");
		fopen_s(&rezultat, "rezultat.dat", "wb");
		interclasare_fisier_binare(fisier1, fisier2, rezultat);
		//dupa realizarea interclasarii se deschide fisierul rezultat, se citeste vectorul stocat si se afiseaza la consola
		fopen_s(&rezultat, "rezultat.dat", "rb+");
		int nr = 0;
		float* vector = citire_vect_fisier_binar(rezultat, nr);
		afisare_vector_tastatura(vector, nr);
		free(vector);
	}
	//dezalocare
	if (nr1 > 0)
	{
		free(vector1);
	}
	if (nr2 > 0)
	{
		free(vector2);
	}
}