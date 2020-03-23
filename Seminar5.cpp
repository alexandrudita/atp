#include<stdio.h>
#include<stdlib.h>

struct Curier {
	int cod;//cheie relativa
	char nume[30];
	char tip_vechicul;//valori posibile: B, M, S unde B-bicicleta, M-masina, S-scuter 
	float valoare_fara_tva[10];
};

struct Student {
	int cod; //cheie relativa 
	char nume[30];
	char an_studiu;//valori posibile: I, II, III
	float note[10];
};

Curier citire_curier_tastatura() {
	Curier c;
	printf("\nCod: ");
	scanf_s("%d", &c.cod);
	printf("\nNume: ");
	getc(stdin);
	gets_s(c.nume, 30);
	printf("\nTip vehicul B,M,S: ");
	c.tip_vechicul = getchar();
	for (int i = 0; i < 10; i++) {
		printf("\nvaloare[%d]= ", i);
		scanf_s("%f", &c.valoare_fara_tva[i]);
	}
	return c;
}

Student citire_student_tastatura() {
	Student s;
	printf("\nCod: ");
	scanf_s("%d", &s.cod);
	printf("\nNume: ");
	getc(stdin);
	gets_s(s.nume, 30);
	printf("\nAn I, II, III: ");
	s.an_studiu = getchar();
	for (int i = 0; i < 10; i++) {
		printf("\nNote[%d]= ", i);
		scanf_s("%f", &s.note[i]);
	}
	return s;
}

int nr_elemente_fis_binar(FILE* fisier,
	int lungime) {
	int n, p;
	p = ftell(fisier);
	fseek(fisier, 0, SEEK_END);
	n = ftell(fisier) / lungime;
	fseek(fisier, p, SEEK_SET);
	return n;
}

void scriere_curier_fisier_binar() {
	FILE* fisier;
	fopen_s(&fisier, "curieri.dat", "wb+");
	if (fisier != NULL) {
		int ok = 1;
		while (ok == 1) {
			int pozitie;
			printf("\nIntroduceti pozitia: ");
			scanf_s("%d", &pozitie);
			int nr = nr_elemente_fis_binar(fisier, sizeof(Curier));
			Curier c;
			if (pozitie > nr) {
				fseek(fisier, 0, SEEK_END);
				for (int i = nr; i < pozitie; i++) {
					c.cod = 0;
					fwrite(&c, sizeof(c), 1, fisier);
				}
				fseek(fisier, (pozitie - 1) * sizeof(c), SEEK_SET);
				c = citire_curier_tastatura();
				fwrite(&c, sizeof(c), 1, fisier);
			}
			else {
				fseek(fisier, (pozitie - 1) * sizeof(c), SEEK_SET);
				fread(&c, sizeof(c), 1, fisier);
				if (c.cod != 0) {
					printf("\nNu putem adauga un curier nou pe pozitia %d deoarece este ocupata de curierul %s\n", pozitie, c.nume);
				}
				else {
					fseek(fisier, (pozitie - 1) * sizeof(c), SEEK_SET);
					c = citire_curier_tastatura();
					fwrite(&c, sizeof(c), 1, fisier);
				}
			}
			printf("\n Daca doriti sa continuati apasati tasta 1");
			scanf_s("%d", &ok);
		}
		fclose(fisier);
	}
	else {
		printf("\n Fisierul nu se poate deschide");
	}
}

void scriere_student_fisier_binar() {
	FILE* fisier;
	fopen_s(&fisier, "studenti.dat", "wb+");
	if (fisier != NULL) {
		int ok = 1;
		while (ok == 1) {
			int pozitie;
			printf("\nIntroduceti pozitia: ");
			scanf_s("%d", &pozitie);
			int nr = nr_elemente_fis_binar(fisier, sizeof(Student));
			Student s;
			if (pozitie > nr) {
				fseek(fisier, 0, SEEK_END);
				for (int i = nr; i < pozitie; i++) {
					s.cod = 0;
					fwrite(&s, sizeof(s), 1, fisier);
				}
				fseek(fisier, (pozitie - 1) * sizeof(s), SEEK_SET);
				s = citire_student_tastatura();
				fwrite(&s, sizeof(s), 1, fisier);
			}
			else {
				fseek(fisier, (pozitie - 1) * sizeof(s), SEEK_SET);
				fread(&s, sizeof(s), 1, fisier);
				if (s.cod != 0) {
					printf("\nNu putem adauga un student nou pe pozitia %d deoarece este ocupata de studentul %s\n", pozitie, s.nume);
				}
				else {
					fseek(fisier, (pozitie - 1) * sizeof(s), SEEK_SET);
					s = citire_student_tastatura();
					fwrite(&s, sizeof(s), 1, fisier);
				}
			}
			printf("\n Daca doriti sa continuati apasati tasta 1");
			scanf_s("%d", &ok);
		}
		fclose(fisier);
	}
	else {
		printf("\n Fisierul nu se poate deschide");
	}
}

void afisare_curieri_fisier_binar() {
	FILE* fisier;
	fopen_s(&fisier, "curieri.dat", "rb");
	printf("\nAfisare curieri: ");
	if (fisier != NULL) {
		Curier c;
		int nr = nr_elemente_fis_binar(fisier, sizeof(Curier));
		for (int i = 0; i < nr; i++) {
			fread(&c, sizeof(c), 1, fisier);
			if (c.cod != 0) {
				printf("\n %d %s %c", c.cod, c.nume, c.tip_vechicul);
			}
		}
		fclose(fisier);
	}
	else {
		printf("\n Fisierul nu se poate deschide");
	}
}

void afisare_studenti_fisier_binar() {
	FILE* fisier;
	fopen_s(&fisier, "studenti.dat", "rb");
	printf("\nAfisare studenti: ");
	if (fisier != NULL) {
		Student s;
		int nr = nr_elemente_fis_binar(fisier, sizeof(Student));
		for (int i = 0; i < nr; i++) {
			fread(&s, sizeof(s), 1, fisier);
			if (s.cod != 0) {
				printf("\n %d %s %c", s.cod, s.nume, s.an_studiu);
			}
		}
		fclose(fisier);
	}
	else {
		printf("\n Fisierul nu se poate deschide");
	}
}

float calcul_total_vector(float* valori, int n) {
	float total = 0;
	for (int i = 0; i < n; i++) {
		total += valori[i];
	}
	return total;
}

void raport_curieri() {
	FILE *fisier_curieri, *fisier_raport;
	fopen_s(&fisier_curieri, "curieri.dat", "rb");
	fopen_s(&fisier_raport, "raport_curieri.txt", "w");
	if (fisier_curieri != NULL && fisier_raport != NULL) {
		Curier c;
		float total_M = 0;
		float total_S = 0;
		float total_B =0;
		int nr = nr_elemente_fis_binar(fisier_curieri, sizeof(Curier));
		for (int i = 0; i < nr; i++) {
			fread(&c, sizeof(c), 1, fisier_curieri);
			if (c.cod != 0) {
				if (c.tip_vechicul == 'M') { 
					total_M += calcul_total_vector(c.valoare_fara_tva, 10);
				}
				else if (c.tip_vechicul == 'B') {
					total_B += calcul_total_vector(c.valoare_fara_tva, 10);
				}
				else {
				total_S += calcul_total_vector(c.valoare_fara_tva, 10);
				}
			}
		}
		fprintf(fisier_raport, "B: %2.2f\n", total_B*1.16);
		fprintf(fisier_raport, "M: %2.2f\n", total_M*1.16);
		fprintf(fisier_raport, "S: %2.2f\n", total_S*1.16);
		float medie = (total_B + total_M + total_S) / 3;
		fprintf(fisier_raport, "Medie: %2.2f", medie*1.16);
		fclose(fisier_curieri);
		fclose(fisier_raport);
	}
	else {
		printf("\nFisierele nu sunt ok");
	}
}

float calcul_medie(float* valori, int n) {
	float medie = 0;
	for (int i = 0; i < n; i++) {
		medie += valori[i];
	}
	return medie / n;
}

void raport_studenti() {
	FILE *fisier_studenti, *fisier_raport;
	fopen_s(&fisier_studenti, "studenti.dat", "rb");
	fopen_s(&fisier_raport, "raport_studenti.txt", "w");
	if (fisier_studenti != NULL && fisier_raport != NULL) {
		Student s, s_max, s_min;
		float min = 0;
		float max = 0;
		char an;
		printf("\nIntroduceti an: ");
		an = getchar();
		int nr = nr_elemente_fis_binar(fisier_studenti, sizeof(Student));
		bool prima_procesare = true;
		for (int i = 0; i < nr; i++) {
			fread(&s, sizeof(s), 1, fisier_studenti);
			if (s.cod != 0 && s.an_studiu == an) {
				float medie = calcul_medie(s.note, 10);
				if (prima_procesare) {
					min = medie;
					max = medie;
					s_min = s;
					s_max = s;
					prima_procesare = false;
				}
				if (min > medie) {
					min = medie;
					s_min = s;
				}
				if (max < medie) {
					max = medie;
					s_max = s;
				}
			}
		}
		fprintf(fisier_raport, "%s %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f\n",
			s_max.nume, s_max.note[0], s_max.note[1], s_max.note[2], s_max.note[3], s_max.note[4],
			s_max.note[5], s_max.note[6], s_max.note[7], s_max.note[8], s_max.note[9]);
		fprintf(fisier_raport, "%s %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f\n",
			s_min.nume, s_min.note[0], s_min.note[1], s_min.note[2], s_min.note[3], s_min.note[4], 
			s_min.note[5], s_min.note[6], s_min.note[7], s_min.note[8], s_min.note[9]);
		fprintf(fisier_raport, "Amplitudine: %2.2f", max - min);
		fclose(fisier_studenti);
		fclose(fisier_raport);
	}else {
		printf("\nFisierele nu sunt ok");
	}
}
void main() {
	//Subiect Grupa 1014
	//Cerinta 1 
	scriere_curier_fisier_binar();
	afisare_curieri_fisier_binar();
	//Cerinta 2
	raport_curieri();
	//Subiect Grupa 1015
	//Cerinta 1
	scriere_student_fisier_binar();
	afisare_studenti_fisier_binar();
	//Cerinta 2
	raport_studenti();
}