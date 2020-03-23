/*
                                             TEMA 3 

Fie un fisier organizat relativ, cu date despre facturile emise de o societate cormerciala.
Articolele au urmatoarea structura: cod factura(intreg), nume(sir de caractere dimensiune 30),
data facturii(sir de caractere dimensiune fixa 11, format dd/MM/yyyy), numarul de produse(intreg),
valoare produse(vector alocat dinamic).

Cheia relativa a fisierului este codul facturii, care se incrementeaza incepand cu valoarea 1.
Consideram ca pe o pozitie in fisier nu exista factura daca codul acesteia este mai mic decat 1.

Sa se implementeze urmatoarele cerinte:
1. Sa se scrie un subprogram care sa populeze fiserul binar relativ cu date despre factura
introduse de la tastatura.
2. Sa se scrie un subprogram care sa afiseze intr-un fisier text toate facturile dintr-un anumit an a
caror valoare totala depaseste o limita data. O linie din fisier are formatul: nume client valoarea
totala, cod factura.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int INCREMENT_COD_FACTURA = 1;
struct Factura {
	int cod_factura;
	char nume[30];
	char data_facturii[11];
	int nr_produse;
	float* valoare_produse;
};

Factura citire_factura_tastatura() {
	Factura f;
	f.cod_factura = INCREMENT_COD_FACTURA;
	INCREMENT_COD_FACTURA++;
	printf("\nNume: ");
	getc(stdin);
	gets_s(f.nume, 30);
	printf("\nData facturii dd/MM/yyyy:");
	gets_s(f.data_facturii, 11);
	printf("\nNr produse: ");
	scanf_s("%d", &f.nr_produse);
	//alocare dinamica vector
	f.valoare_produse = (float*)malloc(sizeof(float)*f.nr_produse);
	for (int i = 0; i < f.nr_produse; i++) {
		printf("\n valoare[%d]= ", i);
		scanf_s("%f", &f.valoare_produse[i]);
	}
	return f;
}

Factura citire_factura_dummy() {
	Factura f;
	f.cod_factura = 0;
	f.nr_produse = 1;
	f.valoare_produse = (float*)malloc(sizeof(float));
	f.valoare_produse[0] = 0;
	return f;
}

void scriere_factura_fisier_binar(FILE* fisier, Factura f) {
	fwrite(&f.cod_factura, sizeof(f.cod_factura), 1, fisier);
	fwrite(&f.nume, sizeof(f.nume), 1, fisier);
	fwrite(&f.data_facturii, sizeof(f.data_facturii), 1, fisier);
	fwrite(&f.nr_produse, sizeof(f.nr_produse), 1, fisier);
	for (int i = 0; i < f.nr_produse; i++) {
		fwrite(&f.valoare_produse[i], sizeof(f.valoare_produse[i]), 1, fisier);
	}
}

Factura citire_factura_fisier_binar(FILE* fisier) {
	Factura f;
	fread(&f.cod_factura, sizeof(f.cod_factura), 1, fisier);
	fread(&f.nume, sizeof(f.nume), 1, fisier);
	fread(&f.data_facturii, sizeof(f.data_facturii), 1, fisier);
	//verificam daca in f avem valori, ca sa facem dezalocarea memorie. Daca uitati sa dezalocati o zona atunci pot aparea memory leaks-uri
	if (f.nr_produse > 0 && f.valoare_produse != NULL) {
		free(f.valoare_produse);
	}
	fread(&f.nr_produse, sizeof(f.nr_produse), 1, fisier);
	//alocam spatiu de memorie pentru a citi vectorul din fisier
	f.valoare_produse = (float*)malloc(sizeof(float)*f.nr_produse);
	for (int i = 0; i < f.nr_produse; i++) {
		fread(&f.valoare_produse[i], sizeof(f.valoare_produse[i]), 1, fisier);
	}
	return f;
}

Factura* citire_facturi_fisier_binar(FILE* fisier, int nr_facturi_mutat) {
	Factura* facturi_de_mutat = (Factura*)malloc(sizeof(Factura)*nr_facturi_mutat);
	for (int i = 0; i < nr_facturi_mutat; i++) {
		facturi_de_mutat[i]=citire_factura_fisier_binar(fisier);
	}
	return facturi_de_mutat;
}

//Avand in vedere ca structura cu care lucram are campuri alocate dinamic nu avem o dimensiune fixa 
//pentru o variabila de tip Factura
//Prin urmare nu putem folosi metoda standard de nr_elemente_fis_binar, ci trebuie sa definim alta.
/*Ex:

Factura f1, f2;
f1.nr_produse = 1;
f1.valoare_produse = (float*)malloc(sizeof(float)*f1.nr_produse);
f1.valoare_produse[0] = 19.0;

f2.nr_produse = 1;
f2.valoare_produse = (float*)malloc(sizeof(float)*f2.nr_produse);
f2.valoare_produse[0] = 19.0;
f2.valoare_produse[1] = 29.0;
*/
//sizeof(f1) nu este egal cu sizeof(f2) deoarece f1 are vectorul valoare_produse intializate cu 1 float, in timp ce f2 are vectorul intializat cu 2 float.
//
//CONCLUZIE: Cand avem structura cu param dinamic metoda de numarare a elementelor din fisierse modifica.
//Metoda de numarare ar trebuie sa faca o parcurgere a fisierului citind fiecare camp
//al structurii, astfel incat sa identificam numar de biti deplasati fata de origine in functie de variatia
//numarului de produse
int nr_elemente_fis_binar(FILE* fisier) {
	int nr = 0;
	//calculam deplasarea curenta a fisierului fata de inceput
	int p = ftell(fisier);
	//ne pozitionam la final
	fseek(fisier, 0, SEEK_END);
	int end_size = ftell(fisier);
	//verificam daca dimensiunea fisierului este cel putin cat o structura Factura care nu are vectorul initializat
	//nu are sens sa mergem mai departe daca fisierul nu are cel putin o dimensiune minima de factura
	if (fisier != NULL && end_size >0) {
		//ne pozitionam la inceput
		fseek(fisier, 0, SEEK_SET);
		Factura f;
		//cat timp nu am ajuns la final de fisier citim factura 
		while (!feof(fisier) && ftell(fisier)<end_size) {
			f= citire_factura_fisier_binar(fisier);
			//dupa o citire corecta a facturii incrementam numarul de element
			nr++;
		}
	}
	//repozitionam fisierul in punctul din care am plecat pentru a calcula dimensiunea
	fseek(fisier, p, SEEK_SET);
	return nr;
}

void scriere_facturi_fisier_bin_rel() {
	FILE* fisier;
	fopen_s(&fisier, "facturi.dat", "wb+");
	if (fisier!=NULL) { 
		int ok = 1;
		while (ok == 1) {
			//introducem pozitia pe care dorim sa salvam factura
			int pozitie;
			printf("\nIntroduceti pozitia: ");
			scanf_s("%d", &pozitie);
			int nr_facturi = nr_elemente_fis_binar(fisier);
			Factura f;
			if (pozitie > nr_facturi) {
				//pozitionare dupa ultimul element din fisier
				fseek(fisier, 0, SEEK_END);
				//adaugam elemente dummy in fisier pana cand ajungem in pozitia dorita.
				//facem acest lucru pentru a putea avea consistenta de date, deoarece ar trebui ca in fisier sa ne asiguram ca adaugam bitii necesari unei facturi pentru fiecare pozitie
				for (int i = nr_facturi; i < pozitie-1; i++) {
					//citire factura dummy
					f = citire_factura_dummy();
					//avand in vedere ca in fisier avem alocare dinamica ar trebui sa scriem fiecare componenta a structurii in fisier
					scriere_factura_fisier_binar(fisier, f);
				}
				f = citire_factura_tastatura();
				//scriere in fisier factura
				scriere_factura_fisier_binar(fisier, f);
			}
			//pozitia se afla inainte de finalul fisierului
			else {
				//ne pozitionam la inceput
				fseek(fisier, 0, SEEK_SET);
				//citim toate facturile din fisier
				Factura* facturi= citire_facturi_fisier_binar(fisier, nr_facturi);
				if (facturi[pozitie - 1].cod_factura != 0) {
					printf("\nPozitia este ocupata de codul %d ", facturi[pozitie - 1].cod_factura);
				}
				else {
					//citim factura factura de la tastatura si suprascriem elementul dummy de pe pozitia tinta din vector
					facturi[pozitie-1] = citire_factura_tastatura();
					//ne pozitionam la inceputul fisierului
					fseek(fisier, 0, SEEK_SET);
					//parcurgem vectorul de facturi ca sa repopulam fisierul cu noul element citit de la tastatura
					for (int i = 0; i < nr_facturi; i++) {
						scriere_factura_fisier_binar(fisier, facturi[i]);
					}
					//dezalocare memorie vector alocat dinamic
					for (int i = 0; i < nr_facturi; i++) {
						free(facturi[i].valoare_produse);
					}
					free(facturi);
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

void afisare_consola_facturi_fisier_binar() {
	FILE* fisier;
	fopen_s(&fisier, "facturi.dat", "rb");
	printf("\nAfisare facturi\n");
	if (fisier != NULL) {
		Factura f;
		//citim cate facturi maxim posibile avem in fisier.
		int nr_facturi = nr_elemente_fis_binar(fisier);
		for (int i = 0; i < nr_facturi; i++)
		{
			f= citire_factura_fisier_binar(fisier);
			if (f.cod_factura != 0) {
				printf("\nCod: %d, Nume: %s, Data facturii: %s", f.cod_factura, f.nume, f.data_facturii);
				//parcurgem vectorul de valori pentru a le afisa				
				for (int i = 0; i < f.nr_produse; i++) {
					printf("\n Valoare produs %d = %2.2f", i, f.valoare_produse[i]);
				}
			}
		}
		//inchidere fisier
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide\n");
	}
}

//cerinta 2
float valoare_totala(Factura f) {
	float total = 0;
	for (int i = 0; i < f.nr_produse; i++) {
		total += f.valoare_produse[i];
	}
	return total;
}

bool verificare_an(Factura f, char an[5]) {
	//functia strstr verifica daca un sir de caractere contine apare intr-un alt sir de caractere
	return strstr(f.data_facturii, an) != NULL;
}

void raport() {
	FILE *fisier_facturi, *fisier_raport;
	fopen_s(&fisier_facturi, "facturi.dat", "rb");
	fopen_s(&fisier_raport, "facturi_raport.txt", "w");
	if (fisier_facturi != NULL && fisier_raport!=NULL) {
		//citire an 
		char an[5];
		printf("\nIntroduceti anul: ");
		getc(stdin);
		gets_s(an, 5);
		//citire limita
		float limita;
		printf("\nLimita: ");
		scanf_s("%f", &limita);
		Factura f;
		//citim cate facturi maxim posibile avem in fisier.
		int nr_facturi = nr_elemente_fis_binar(fisier_facturi);
		for (int i = 0; i < nr_facturi; i++)
		{
			f = citire_factura_fisier_binar(fisier_facturi);
			//verificam codul prima data ca sa evitam analiza unui element dummy, dupa care verificam anul
			if (f.cod_factura != 0 && verificare_an(f, an)) {
				//calculam valoarea total
				float total = valoare_totala(f);
				//scriem in fisier doar daca valoarea total depaseste limita
				if (total >= limita) {
					fprintf(fisier_raport, "%s %2.2f %d\n", f.nume, total, f.cod_factura);
				}
			}
		}
		//inchidere fisier
		fclose(fisier_facturi);
      fclose(fisier_raport);
	}
	else {
		printf("\nFisierul nu se poate deschide\n");
	}
}

void main() {
	//cerinta 1
	scriere_facturi_fisier_bin_rel();
	afisare_consola_facturi_fisier_binar();
	//cerinta 2
	int procesare_raport;
	printf("\nDoriti procesare raportului? Da-1/Nu-0");
	scanf_s("%d", &procesare_raport);
	if (procesare_raport == 1) {
		raport();
	}
}