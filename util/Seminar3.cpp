#include "pch.h"
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
void main() {
	int n = 0;
	float* vector = citire_vector_tastatura(n);
	FILE* fisier;
	//fopen_s(&fisier, "vector.dat", "wb");
	//scriere_vector_binar_sec(fisier, vector, n);
	free(vector);//dezaloc deoarece refolosesc variabila vector
	fopen_s(&fisier, "vector.dat", "rb");
	vector = citire_vect_fisier_binar(fisier, n);
	afisare_vector_tastatura(vector, n);
}