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
				fseek(fisier, (pozitie - 1) * sizeof(c), SEEK_SET);
				c = citire_candidat_tastatura();
				//scriere in fisier candidat
				fwrite(&c, sizeof(c), 1, fisier);
			}
			//pozitia se afla inainte de finalul fisierului
			else {
				//ne deplasam cu bitii din punctul de start al fisierului pana in pozitia dorita
				fseek(fisier, (pozitie - 1) * sizeof(c), SEEK_SET);
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

float nota_maxima_candidati() {
	float maxim = 0.0;
	FILE* fisier;
	fopen_s(&fisier, "candidati.dat", "rb+");
	if (fisier != NULL) {
		Candidat c;
		//citim cati candidati avem in fisier. ATENTIE aceasta variabila nu specifica daca toti candidatii sunt valizi. Putem avea variabile de tip Candidat cu codul -1 pe care-l consideram invalid conform metodei de scriere in fisier
		int nr_candidati = nr_elemente_fis_binar(fisier, sizeof(Candidat));
		for (int i = 0; i < nr_candidati; i++)
		{
			fread(&c, sizeof(c), 1, fisier);
			if (c.is == 1 && maxim<c.nota) {
				maxim = c.nota;
			}
		}
		//inchidere fisier
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide\n");
	}
	return maxim;
}

float nota_minima_candidati() {
	float minim = 0.0;
	FILE* fisier;
	fopen_s(&fisier, "candidati.dat", "rb+");
	if (fisier != NULL) {
		Candidat c;
		//citim cati candidati avem in fisier. ATENTIE aceasta variabila nu specifica daca toti candidatii sunt valizi. Putem avea variabile de tip Candidat cu codul -1 pe care-l consideram invalid conform metodei de scriere in fisier
		int nr_candidati = nr_elemente_fis_binar(fisier, sizeof(Candidat));
		for (int i = 0; i < nr_candidati; i++)
		{
			fread(&c, sizeof(c), 1, fisier);
			if (c.is == 1 && minim > c.nota) {
				minim = c.nota;
			}
		}
		//inchidere fisier
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide\n");
	}
	return minim;
}

float medie_candidati() {
	float suma = 0.0;
	int nr_candidati_valizi = 0;
	FILE* fisier;
	fopen_s(&fisier, "candidati.dat", "rb+");
	if (fisier != NULL) {
		Candidat c;
		//citim cati candidati avem in fisier. ATENTIE aceasta variabila nu specifica daca toti candidatii sunt valizi. Putem avea variabile de tip Candidat cu codul -1 pe care-l consideram invalid conform metodei de scriere in fisier
		int nr_candidati = nr_elemente_fis_binar(fisier, sizeof(Candidat));
		for (int i = 0; i < nr_candidati; i++)
		{
			fread(&c, sizeof(c), 1, fisier);
			if (c.is != 0) {
				suma += c.nota;
				nr_candidati_valizi++;
			}
		}
		//inchidere fisier
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide\n");
	}
	if (nr_candidati_valizi > 0) {
		return suma / nr_candidati_valizi;
	}
	else {
		return 0;
	}
}

void afisare_candidat_pozitie() {
	FILE* fisier;
	fopen_s(&fisier, "candidati.dat", "rb");
	if (fisier != NULL){
		Candidat c;
		int pozitie;
		printf("\nIntroduceti pozitia dorita: ");
		scanf_s("%d", &pozitie);
		int nr_candidati = nr_elemente_fis_binar(fisier, sizeof(Candidat));
		if (pozitie >= nr_candidati) {
			printf("\nNu exista element pe pozitia %d", pozitie);
		}
		else {
			fseek(fisier, (pozitie - 1)*sizeof(c), SEEK_SET);
			fread(&c, sizeof(c), 1, fisier);
			if (c.is != 0) {
				printf("\nNume: %s, Nota %2.2f", c.nume, c.nota);
			}
			else {
				printf("\nNu exista element pe pozitia %d", pozitie);
			}
		}
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}
}

void modifica_candidat_pozitie() {
	FILE* fisier;
	fopen_s(&fisier, "candidati.dat", "rb+");
	if (fisier != NULL) {
		Candidat c;
		int pozitie;
		printf("\nIntroduceti pozitia dorita: ");
		scanf_s("%d", &pozitie);
		int nr_candidati = nr_elemente_fis_binar(fisier, sizeof(Candidat));
		if (pozitie >= nr_candidati) {
			printf("\nNu exista element pe pozitia %d", pozitie);
		}
		else {
			fseek(fisier, (pozitie - 1) * sizeof(c), SEEK_SET);
			fread(&c, sizeof(c), 1, fisier);
			if (c.is != 0) {
				c = citire_candidat_tastatura();
				//repozitionare din punctul in care dorim sa scriem. Daca nu facem acest lucru, modificam candidatul de pe pozitia urmatoare, deoarece prin apelul fread am deplasat cursorul in fisier cu un candidat
				fseek(fisier, (pozitie - 1) * sizeof(c), SEEK_SET);
				fwrite(&c, sizeof(c), 1, fisier);
			}
			else {
				printf("\nNu exista element pe pozitia %d", pozitie);
			}
		}
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}
}

void stergere_candidat_pozitie() {
	FILE* fisier;
	fopen_s(&fisier, "candidati.dat", "rb+");
	if (fisier != NULL) {
		Candidat c;
		int pozitie;
		printf("\nIntroduceti pozitia dorita: ");
		scanf_s("%d", &pozitie);
		int nr_candidati = nr_elemente_fis_binar(fisier, sizeof(Candidat));
		if (pozitie >= nr_candidati) {
			printf("\nNu exista element pe pozitia %d", pozitie);
		}
		else {
			fseek(fisier, (pozitie - 1) * sizeof(c), SEEK_SET);
			fread(&c, sizeof(c), 1, fisier);
			if (c.is != 0) {
				c.is = 0;
				//repozitionare din punctul in care dorim sa scriem. Daca nu facem acest lucru, modificam candidatul de pe pozitia urmatoare, deoarece prin apelul fread am deplasat cursorul in fisier cu un candidat
				fseek(fisier, (pozitie - 1) * sizeof(c), SEEK_SET);
				fwrite(&c, sizeof(c), 1, fisier);
			}
			else {
				printf("\nNu exista element pe pozitia %d", pozitie);
			}
		}
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}
}

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