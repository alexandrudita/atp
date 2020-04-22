/*
											TEMA 4

In cadrul seminarului de ATP este utilizata urmatoarea modalitate de notare a studentilor: 
- fiecare student are un punctaj cuprins in intervalul intreg [0,100];
- orice student care are un punctaj mai mic decat 45 este considerat picat;

Profesorul de seminar doreste sa rotunjeasca punctajele obtinute la test dupa urmatoarele reguli: 
- daca diferenta dintre punctajul studentului si urmatorul punctaj multiplu de 5 este mai mica decat 3
atunci punctajul final al studentului este majorat la urmatorul multiplu de 5;
- daca punctajul studentului este mai mic decat 43 nu se aplica regula de rotunjire;

Punctajele studentilor sunt stocate in fisierul tema4_stud.txt disponibil in zona de atasament. 
Structura acestuia este urmatoarea: 
- prima linie contine numarul total de studenti
- pe restul de linii sunt listate numele studentului si punctajul acestuia.

Cerinte: 
1. Sa se implementeze o metoda care sa citeasca in mod recursiv informatiile unui student din fisierul 
tema4_stud.txt. Informatiile despre student sunt stocate intr-un vector dinamic de tipul Student, unde 
Student este o structura de forma: 
struct Student {
	char nume[30];
	int punctaj;
};
HINT: operatia de preluare a numarului de studenti din fisier, NU este inclusa in metoda de recursivitate. 
Scopul acelei metode ar fi sa citeasca elementele de tip Student din fisier.
2. Sa se implementeze o metoda care afiseaza la tastatura vectorul de Student citit din fisier.
3. Sa se implementeze o metoda care efectueaza rotunjirea punctajelor conform restrictiilor prezentate 
mai sus.
4. Sa se implementeze o metoda care asigura dezalocarea vectorului Student.
----------------------------------------------------------------------------------------------------
Exemplu: Popescu Daniel 84 -> punctaj final 85, 85-84=1<3, 85 este primul multiplu de 5 dupa 84
Popescu Ionela 81 -> punctaj final 81, 85-81=4>3, 85 este primul multiplu de 5 dupa 81
Popescu Marcel 37 -> punctaj final 37, 37 <punctaj minim de promovare 43
Popescu Victor 43 -> punctaj final 45, 45-43=2<2, 45 primul multiplu de 5 dupa 43
----------------------------------------------------------------------------------------------------
*/

#include<stdio.h>
#include<stdlib.h>

struct Student {
	char nume[30];
	int punctaj;
};

void citeste_student_recursiv(FILE* fisier, Student* &studenti, int dim) {
	if (dim != 0) {			
		citeste_student_recursiv(fisier, studenti, dim - 1);
	}
	fgetc(fisier);
	fgets(studenti[dim].nume, 30, fisier);
	fscanf_s(fisier, "%d", &studenti[dim].punctaj);

}

Student* initializare_vector_studenti(int &n) {
	FILE* fisier;
	fopen_s(&fisier, "tema4_stud.txt", "r");
	if (fisier != NULL) {
		fscanf_s(fisier, "%d", &n);
		Student* studenti = (Student*)malloc(sizeof(Student)*n);
		citeste_student_recursiv(fisier, studenti, n - 1);
		fclose(fisier);
		return studenti;
	}
	else {
		printf("\nFisierul nu s-a putut deschide");
	}
}

void rotunjire(Student* &studenti, int dim) {
	for (int i = 0; i < dim; i++) {
		//calculam numarul de puncte necesar sa ajungem la primul multiplu de 5 mai mare decat punctajul curent 
		//Ex: punctaj 73 => rest = 5 - 73%5, 73%5 = 3 => rest = 2 
		int rest = 5 - studenti[i].punctaj % 5;
		//verificam conditiile de rotunjire din cerinta
		if (studenti[i].punctaj > 43 && rest < 3) {
			studenti[i].punctaj += rest;
		}
	}
}

void afisare(Student* studenti, int dim) {
	for (int i = 0; i < dim; i++) {
		printf("\n%s %d", studenti[i].nume, studenti[i].punctaj);
	}
}

void dezalocare(Student* studenti, int dim) {
	if (dim > 0) {
		free(studenti);
	}
}

void main() {
	int dim = 0;
	Student* studenti = initializare_vector_studenti(dim);
	printf("\n++++++++++++++++ Afisare inainte de procesare +++++++++++++++++++++\n");
	afisare(studenti, dim);
	printf("\n++++++++++++++++ Afisare dupa procesare +++++++++++++++++++++\n");
	rotunjire(studenti, dim);
	afisare(studenti, dim);
	dezalocare(studenti, dim);
}