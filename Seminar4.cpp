// Seminar4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include<stdio.h>
#include<stdlib.h>

struct Candidat {
	int is; //cheie relativa fisier binar poate sa fie orice element
	char nume[30];
	float nota;
};

Candidat citire_candidat_tastatura() {
	Candidat c;
	c.is = 1;
	printf("\nCitire candidat tastatura\n");
	printf("\nNume: ");
	getc(stdin);
	gets_s(c.nume, 30);
	printf("\nNota: ");
	scanf_s("%f", &c.nota);
	return c;
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

void scriere_angajati_fisier_bin_rel() {
	FILE* fisier;
	fopen_s(&fisier, "candidati.dat", "wb+");
	if (fisier!=NULL) { 
		int ok = 1;
		while (ok == 1) {
			//introducem pozitia pe care dorim sa salvam candidatul
			int pozitie;
			printf("\nIntroduceti pozitia: ");
			scanf_s("%d", &pozitie);
			//dimensiune fisier atat cu canditati 1 - prezenti cat si cu 0 - lipsa
			int nr_candidati = nr_elemente_fis_binar(fisier, sizeof(Candidat));
			Candidat c;
			if (pozitie > nr_candidati) {
				//pozitionare dupa ultimul element din fisier
				fseek(fisier, 0, SEEK_END);
				//adaugam elemente dummy in fisier pana cand ajungem in pozitia dorita.
				//facem acest lucru pentru a putea avea consistenta de date, deoarece ar trebui ca in fisier sa ne asiguram ca adaugam bitii necesari unui candidat pentru fiecare pozitie
				for (int i = nr_candidati; i < pozitie; i++) {
					c.is = 0;
					fwrite(&c, sizeof(c), 1, fisier);
				}
				//ne deplasam cu bitii din punctul de start al fisierului pana in pozitia dorita
				fseek(fisier, (pozitie - 1) * sizeof(c),
					SEEK_SET);
				c = citire_candidat_tastatura();
				//scriere in fisier candidat
				fwrite(&c, sizeof(c), 1, fisier);
			}
			//pozitia se afla inainte de finalul fisierului
			else {
				//ne deplasam cu bitii din punctul de start al fisierului pana in pozitia dorita
				fseek(fisier, (pozitie - 1) * sizeof(c),
					SEEK_SET);
				//citim candidatul aflat pe aceasta pozitie in fisier
				fread(&c, sizeof(c), 1, fisier);
				//verificam daca exista deja un candidat. In cazul in care exista un candidat afisam mesaj de eroare 
				if (c.is != 0) {
					printf("\nNu putem adauga un candidat nou pe pozitia %d deoarece este ocupata de candidatul %s\n", pozitie, c.nume);
				}
				else {
					//adaugam un nou candidat
					c = citire_candidat_tastatura();
					fwrite(&c, sizeof(c), 1, fisier);
				}
			}
			printf("\n Daca doriti sa continuati apasati tasta 1");
			scanf_s("%d", &ok);
		}
		//inchidere fisier
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu s-a putut deschide");
	}
}

void afisare_consola_candidati_fisier_bin_rel() {
	FILE* fisier;
	fopen_s(&fisier, "candidati.dat", "rb");
	printf("\nAfisare candidati\n");
	if (fisier != NULL) {
		Candidat c;
		//citim cati candidati avem in fisier. ATENTIE aceasta variabila nu specifica daca toti candidatii sunt valizi. Putem avea variabile de tip Candidat cu codul -1 pe care-l consideram invalid conform metodei de scriere in fisier
		int nr_candidati = nr_elemente_fis_binar(fisier, sizeof(Candidat));
		for (int i = 0; i < nr_candidati; i++)
		{
			fread(&c, sizeof(c), 1, fisier);
			if (c.is != 0) {
				printf("\nNume: %s, Nota %2.2f", c.nume, c.nota);
			}
		}
		//inchidere fisier
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide\n");
	}
}

float nota_maxima_candidati();

float nota_minima_candidati();

float medie_candidati();

void afisare_candidat_pozitie();

void modifica_candidat_pozitie();

void stergere_candidat_pozitie();
void main() {
	scriere_angajati_fisier_bin_rel();
	afisare_consola_candidati_fisier_bin_rel();
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++");
	float minim = nota_minima_candidati();
	printf("\nNota minima: %2.2f", minim);
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++");
	float maxim = nota_maxima_candidati();
	printf("\nNota maxima: %2.2f", maxim);
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++");
	float medie = medie_candidati();
	printf("\nMedia notelor: %2.2f", medie);
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("\Afisare candidat pozitie");
	afisare_candidat_pozitie();
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("\nModificare candidat pozitie");
	modifica_candidat_pozitie();
	afisare_consola_candidati_fisier_bin_rel();
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("\nStergere candidat pozitie");
	stergere_candidat_pozitie();
	afisare_consola_candidati_fisier_bin_rel();
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++");
}