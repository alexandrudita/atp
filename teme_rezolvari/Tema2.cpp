/*
															TEMA 2

Plecand de la continutul prezentat in cadrul seminarului din saptmana a doua  - https://github.com/alexandrudita/atp/blob/master/Seminar2.cpp - implementati urmatoarele cerinte:
1. Sa se analizeze codul implementat si sa se extraga cel putin 5 metoda. In functia main sa se apeleze metodele identificate in asa fel incat rezultatul obtinut sa fie identic cu cel de la seminar.
2. Sa se implementeze o functie care sa asigure introducerea de studenti de la tastatura intr-un fisier text, ordonati alfabetic.
3. Sa se implementeze o functie care sa scrie intr-un fisier binar toti studentii integralisti din fiserul de la punctul 2.
4. Sa se implementeze o functie care sa citeasca studentii integralisti adaugati la punctul anterior.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct STUDENT {
	char nume[20];
	float* note;
	int nr_note;
};

STUDENT* citire_studenti_fisier_text(const char* nume_fisier, int& nr_studenti) {
	//deschidere fisier
	FILE* fisier;
	fopen_s(&fisier,nume_fisier, "r");
	if (fisier != NULL && !feof(fisier)) {
		//preluare numar studenti din fisier
		fscanf_s(fisier, "%d", &nr_studenti);
		//alocare vector dinamic studenti cu numarul din fisier
		STUDENT* studenti = (STUDENT*)malloc(sizeof(STUDENT)*nr_studenti);
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
		fclose(fisier);
		return studenti;
	}
	else {
		printf("\nFisierul nu s-a putut deschide\n");
	}
}

void afisare_studenti_tastatura(STUDENT* studenti, int nr_studenti) {
	printf("\nAfisare la consola studenti\n");
	for (int i = 0; i < nr_studenti; i++) {
		//afisare nume student
		printf("\nNume student: %s", studenti[i].nume);
		//afisare note
		for (int j = 0; j < studenti[i].nr_note; j++) {
			printf("\nNote[%d] = %f", j, studenti[i].note[j]);
		}
	}
}

float media_notelor(float* note, int nr_note) {
	//calcul medie
	float media = 0;
	for (int i = 0; i < nr_note; i++) {
		media = media + note[i];
	}
	if (nr_note == 0) {
		return media;
	}
	return media / nr_note;
}

void scriere_raport(STUDENT* studenti, int nr_studenti) {
	FILE* fisier;
	fopen_s(&fisier, "rezultat_2.txt", "w");
	if (fisier != NULL) {
		//accesez fiecare student
		for (int i = 0; i < nr_studenti; i++) {
			float media = media_notelor(studenti[i].note, studenti[i].nr_note);
			//scriere nume student fisier
			fprintf(fisier, "%s", studenti[i].nume);
			//scriere medie in fisier
			fprintf(fisier, "%f\n", media);
		}
		fclose(fisier);
	}
}

void dezalocare(STUDENT* studenti, int nr_studenti) {
	if (studenti != NULL && nr_studenti > 0) {
		//dezalocare vector dinamic
		for (int i = 0; i < nr_studenti; i++) {
			//dezalocare note
			free(studenti[i].note);
		}
		free(studenti);
	}
}

//cerinta 2
STUDENT* citire_studenti_tastatura(int& nr) {
	printf("\nIntroduceti numarul de studenti: ");
	scanf_s("%d", &nr);
	//alocare spatiu pentru vectorul de studenti
	STUDENT* studenti = (STUDENT*)malloc(sizeof(STUDENT)*nr);
	for (int i = 0; i < nr; i++) {
		//citire studenti
		printf("\nNume: ");
		getc(stdin);
		gets_s(studenti[i].nume, 20);
		//pentru a pastra structura din exercitiul 1, o sa adaugam aceeasi structura de fisier. OBS nu este obligatoriu sa faceti asa
		studenti[i].nr_note = 5;
		studenti[i].note = (float*)malloc(sizeof(float)*studenti[i].nr_note);
		for (int j = 0; j < studenti[i].nr_note; j++) {
			printf("\nNota[%d]= ", j);
			scanf_s("%f", &studenti[i].note[j]);
		}
	}
	return studenti;
}

void ordonare_alfabetic_studenti(STUDENT** studenti, int nr) {
	for (int i = 0; i < nr - 1; i++) {
		for (int j = i; j < nr; j++) {
			//strcmp este functia care compara 2 siruri de caractere. posibile rezultat 0 - egalitate, -1 daca primul e mai mare decat al doilea, 1 daca al doilea este mai mare decat primul
			if (strcmp((*studenti)[i].nume, (*studenti)[j].nume) == 1) {
				//interschimbare studenti
				STUDENT temp = (*studenti)[i];
				(*studenti)[i] = (*studenti)[j];
				(*studenti)[j] = temp;
			}
		}
	}
}

void scriere_studenti_alfabetic() {
	//scriere studenti fisier
	int nr = 0;
	STUDENT* studenti = citire_studenti_tastatura(nr);
	ordonare_alfabetic_studenti(&studenti, nr);
	FILE* fisier; 
	fopen_s(&fisier, "studenti_alfabetic.txt", "w");
	if (fisier != NULL) {
		//parcurgere vector sortat pentru scrierea in fisier text
		fprintf(fisier, "%d", nr);
		for (int i = 0; i < nr; i++) {
			fprintf(fisier, "\n%s\n", studenti[i].nume);
			for (int j = 0; j < studenti[i].nr_note; j++) {
				fprintf(fisier, "%2.2f ", studenti[i].note[j]);
			}			
		}
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}
	//dezalocare vector dinamic
	dezalocare(studenti, nr);
}

//cerinta 3
void scriere_studenti_integralisti() {
	int nr = 0;
	//citim vectorul de studenti folosind functia de la punctul 1.
	STUDENT* studenti = citire_studenti_fisier_text("studenti_alfabetic.txt", nr);
	//deschidere fisier binar pentru a scrie studentii integralisti
	FILE* fisier;
	fopen_s(&fisier, "studenti_integralisti.dat", "wb");
	if (fisier != NULL) {
		//parcurgem lista de studenti
		for (int i = 0; i < nr; i++) {
			//consideram un student integralist daca are media mai mare decat 8
			float media = media_notelor(studenti[i].note, studenti[i].nr_note);
			if (media >= 8.50) {
				//daca in structura pe dorim sa o scriem intr-un fisier binar, un camp alocat dinamic, atunci trebuie sa scriem element cu element in fisier, altfel se poate apela o singura data functia fwrite(&structura...);
				fwrite(&studenti[i].nume, sizeof(studenti[i].nume), 1, fisier);
				//scriem nr de note
				fwrite(&studenti[i].nr_note, sizeof(studenti[i].nr_note), 1, fisier);
				//scriem fiecare nota in parte
				for (int j = 0; j < studenti[i].nr_note; j++) {
					fwrite(&studenti[i].note[j], sizeof(float), 1, fisier);
				}
			}
		}
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}
	//dezalocare vector alocat dinamic
	dezalocare(studenti, nr);
}

//cerinta 4
int nr_elemente_fis_binar(FILE* fisier, int lungime) {
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

void afisare_studenti_integralisti() {
	//deschidere fisier binar pentru a scrie studentii integralisti
	FILE* fisier;
	fopen_s(&fisier, "studenti_integralisti.dat", "rb");
	if (fisier != NULL) {
		STUDENT s;
		//calculam numarul de studenti din fisier
		int nr = nr_elemente_fis_binar(fisier, sizeof(STUDENT));
		for (int i = 0; i < nr; i++) {
			//citim studentul din fisier
			//citim numele studentului
			fread(&s.nume, sizeof(s.nume), 1, fisier);
			//citim nr de note din fisier
			fread(&s.nr_note, sizeof(s.nr_note), 1, fisier);
			//alocam spatiu de memorie pentru notele studentului
			s.note = (float*)malloc(sizeof(float)*s.nr_note);
			for (int j = 0; j < s.nr_note; j++) {
				//citim fiecare nota in parte.
				fread(&s.note[j], sizeof(float), 1, fisier);
			}
			//afisare nume student
			printf("\nNume student: %s", s.nume);
			//afisare note
			for (int j = 0; j < s.nr_note; j++) {
				printf("\nNote[%d] = %f", j, s.note[j]);
			}
		}
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}
}
void main()
{
	//cerinta 1
	int nr_studenti = 0;
	STUDENT* studenti = citire_studenti_fisier_text("catalog.txt",nr_studenti);
	afisare_studenti_tastatura(studenti, nr_studenti);
	printf("\nScriere fisier nume student + media notelor\n");
	scriere_raport(studenti, nr_studenti);
	dezalocare(studenti, nr_studenti);
	////cerinta 2
	//scriere_studenti_alfabetic();
	//cerinta 3
	scriere_studenti_integralisti();
	//cerinta 4
	afisare_studenti_integralisti();
}