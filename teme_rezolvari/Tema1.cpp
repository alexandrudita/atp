///*
//											TEMA 1
//
//Sa se rezolve urmatoarele cerinte:
//
//1. Scrieti un subprogram care sa realizeze adaugarea unor valori reale preluate de la consola intr-un fisier text. 
//Utilizatorul poate sa introduca cate elemente doreste, dupa fiecare adaugare acesta este intrebat daca doreste sa continue. 
//Raspunsul afirmativ este marcat prin apasarea tastei '1'.
//
//2. Pentru fisierul construit anterior sa se implementeze un alt subprogram care sa elimine valorile cuprinse intr-un 
//interval [a,b], unde a si b sunt citite de la tastatura.
//
//3.  Fie structura Angajat care are informatiile nume(sir de caractere cu o lungime fixa de maxim 30 de caractere),
//salariul(numar real) si departament(sir de caractere alocat dinamic). Sa se implementeze un subprogram care sa 
//realizeze adaugarea unor angajati preluati de la tastatura intr-un fisier text.
//
//4. Pentru fisierul de la punctul 3 sa se implementeze un alt subprogram care sa asigure eliminarea tuturor angajatilor 
//care au un salariu in intervalul [a,b], unde a si b sunt preluati de la tastatura.
//*/
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct Angajat {
//	char nume[100];
//	float salariu;
//	char* departament;
//};
//
//void adaugare_valori_fisier(char nume_fisier[30]) {
//	//deschidere fisier
//	FILE* fisier;
//	fopen_s(&fisier, nume_fisier, "w");
//	if (fisier != NULL) {//verificare daca s-a deschis fisierul
//		printf("\nIntroduceti elementele: ");
//		//declarare variabila intermediara pentru a continua preluarea de date de la tastatura. 
//		int ok = 1;
//		while (ok == 1) {
//			float valoare;
//			//preluare valoare de la tastatura
//			scanf_s("%f", &valoare);
//			//scriere in fisier
//			fprintf(fisier, "%f", valoare);
//			//se continua adaugarea de elemente? 
//			printf("\nContinuati? Da-1 Nu-0 ");
//			scanf_s("%d", &ok);
//			//daca se continua adaugarea de elemente se introduce o linie noua in fisier, astfel incat fiecare element sa fie adaugat pe rand nou
//			if (ok == 1) {
//				fprintf(fisier,"\n");
//			}
//		}
//		//inchidere fisier
//		fclose(fisier);
//	}
//	else 
//	{
//		printf("\nFisierul nu s-a putut deschide");
//	}
//}
//
//void citire_elemente_fisier(char nume_fisier[30],float valori[100], int& n) {
//	//deschidere fisier
//	FILE* fisier;
//	fopen_s(&fisier, nume_fisier, "r");
//	if (fisier != NULL) {//verificare daca s-a deschis fisierul
//		//citire elemente din fisier si stocarea lor intr-un vector de tip float
//		while (!feof(fisier)) {
//			fscanf_s(fisier, "%f", &valori[n]);
//			n++;
//		}
//		//inchidere fisier
//		fclose(fisier);
//	}
//	else
//	{
//		printf("\nFisierul nu s-a putut deschide");
//	}
//}
//
//void eliminare_elemente_din_fisier(char nume_fisier[30]) {
//	//declarare contor pentru a numara elementele din fisier
//	int n = 0;
//	//declarare vector static dimensiune fixa. Se poate lua o valoare cat mai mare 
//	float valori[100];
//	citire_elemente_fisier(nume_fisier, valori, n);
//	//citire valori interval
//	float a, b;
//	printf("\na = ");
//	scanf_s("%f", &a);
//	printf("\nb = ");
//	scanf_s("%f", &b);
//	//trebuie sa continuam procesarea doar daca a<b si n>0, altfel nu avem un interval valid sau elemente in vector
//	if (a < b && n>0) {
//		//deschidere fisier pentru scriere
//		FILE* fisier;
//		fopen_s(&fisier, nume_fisier, "w");
//		if (fisier != NULL) {//verificare daca s-a deschis fisierul
//			//pentru a putea adauga linie noua doar daca procesarea nu a fost executata prima data
//			//daca scriem direct printf("\n") la finalul fisierului o sa avem o linie goala.
//			bool prima_procesare = true;
//			//parcurgere elemente din vectorul preluat din fisier si adaugarea celor din afara intervalului in fisierul deschis
//			for (int i = 0; i < n; i++) {
//				if (valori[i]<a || valori[i]>b) {
//					if (!prima_procesare) {
//						fprintf(fisier, "\n");
//					}
//					else {
//						prima_procesare = false;
//					}
//					fprintf(fisier, "%f", valori[i]);
//				}
//			}
//			//inchidere fisier
//			fclose(fisier);
//		}
//		else {
//			printf("\nFisierul nu s-a putut deschide");
//		}
//	}
//	else {
//		printf("\na este mai mare decat b");
//	}
//}
//
//Angajat introducere_angajat_tastatura() {
//	Angajat angajat;
//	printf("\nNume: ");
//	gets_s(angajat.nume, 100);
//	printf("\nSalariu: ");
//	scanf_s("%f", &angajat.salariu);
//	printf("\nDepartament: ");
//	//golire buffer dupa ce am utilizat un scanf
//	getchar();
//	//pentru alocarea dinamica a sirurilor de caractere este necesar ca in prealabil sa se utilizeze o variabila 
//	//de siruri de caractere statice astfel incat sa putem prelua valoarea de la tastatura
//	//dupa preluare se determina numarul de caractere introduse de utilizare, dupa care se aloca spatiu pentru variabila dinamica
//	//declarare variabila intermediara
//	char buf[30];
//	//citire departament de la tastatura
//	gets_s(buf, 30);
//	//determinare numar de caractere introduse de la tastatura
//	int nr = strlen(buf) + 1;//se adauga + 1 pentru semnul de bit.
//	//alocare spatiu departament
//	angajat.departament = (char*)malloc(sizeof(char)*nr);
//	//copiere valoare din buf in departament
//	strcpy_s(angajat.departament, nr, buf);
//	return angajat;
//}
//void adaugare_angajati_fisier(char nume_fisier[30]) {
//	//deschidere fisier
//	FILE* fisier;
//	fopen_s(&fisier, nume_fisier, "w");
//	if (fisier != NULL) {//verificare daca s-a deschis fisierul
//		int n = 0;
//		printf("\nIntroduceti numarul de elemente: ");
//		scanf_s("%d", &n);
//		//scriere numar de angajat pe prima linie
//		fprintf(fisier, "%d", n);
//		//golire buffer dupa ce am utilizat un scanf_s
//		getchar();
//		for (int i = 0; i < n; i++) {
//			Angajat angajat = introducere_angajat_tastatura();
//			//adaugare angajat in fisier
//			fprintf(fisier, "\n%s\n%f\n%s", angajat.nume, angajat.salariu, angajat.departament);
//		}
//		//inchidere fisier
//		fclose(fisier);
//	}
//	else
//	{
//		printf("\nFisierul nu s-a putut deschide");
//	}
//
//}
//
//Angajat* citire_angajati_fisier(char nume_fisier[30], int& n) {
//	//deschidere fisier
//	FILE* fisier;
//	fopen_s(&fisier, nume_fisier, "r");
//	if (fisier != NULL) {//verificare daca s-a deschis fisierul
//		Angajat* angajati;
//		//citire numar de angajati din prima linie a fisierului
//		fscanf_s(fisier, "%d", &n);
//		//curatare buff deoarece avem un fscanf_s mai sus apelat. 
//		//OBS: nu introduceti in for acest fgetc, deaorece a doua executie a for-ului presupune 
//		//ca inainte de preluare numelui sa fie preluat departamentul ceea ce inseamna tot un apel de gets. 
//		//Nu uitat folosirea cu fgetc/getchar se face doar dupa un fscanf_s/scanf_s
//		fgetc(fisier);
//		//alocare vector de angajati
//		angajati = (Angajat*)malloc(sizeof(Angajat)*n);
//		//preluare angajat unul cate unul din fisier cu ajutorul for-ului
//		for (int i = 0; i < n; i++) {
//			//preluare nume
//			fgets(angajati[i].nume, 100, fisier);
//			//preluare salariu angajat pozitia i
//			fscanf_s(fisier, "%f", &angajati[i].salariu);
//			//curatare buffer
//			fgetc(fisier);
//			//preluare departament. acelas principiu ca la preluare de la tastatura. vezi metoda introducere_angajat_tastatura
//			char buf[30];
//			fgets(buf, 30, fisier);
//			int nr= strlen(buf) + 1; 
//			angajati[i].departament = (char*)malloc(sizeof(char)*nr);
//			strcpy_s(angajati[i].departament, nr, buf);
//		}
//		//inchidere fisier
//		fclose(fisier);
//		return angajati;
//	}
//	else
//	{
//		printf("\nFisierul nu s-a putut deschide");
//	}
//}
//
//void eliminare_angajati_din_fisier(char nume_fisier[30]) {
////nr de angajati
//	int n = 0;
//	Angajat* angajati = citire_angajati_fisier(nume_fisier, n);
//	//citire valori interval
//	float a, b;
//	printf("\na = ");
//	scanf_s("%f", &a);
//	printf("\nb = ");
//	scanf_s("%f", &b);
//	//trebuie sa continuam procesarea doar daca a<b si n>0, altfel nu avem un interval valid sau elemente in vector
//	if (a < b && n>0) {
//		//deschidere fisier pentru scriere
//		FILE* fisier;
//		fopen_s(&fisier, "eliminare_angajat.txt", "w");
//		if (fisier != NULL) {//verificare daca s-a deschis fisierul
//			//parcurgere elemente din vectorul preluat din fisier si adaugarea celor din afara intervalului in fisierul deschis
//			for (int i = 0; i < n; i++) {
//				if (angajati[i].salariu<a || angajati[i].salariu>b) {
//					//adaugare angajat in fisier
//					fprintf(fisier, "%s%f\n%s", angajati[i].nume, angajati[i].salariu, angajati[i].departament);
//				}
//			}
//			//inchidere fisier
//			fclose(fisier);
//		}
//		else {
//			printf("\nFisierul nu s-a putut deschide");
//		}
//	}
//	else {
//		printf("\na este mai mare decat b");
//	}
//	//dezalocare vector angajati
//	if (n > 0) {
//		//dezalocare se incepe in ordinea inversa a alocarii. prin urmare, ar trebui ca prima data sa se elimine alocarea pentru departament
//		for (int i = 0; i < n; i++) {
//			free(angajati[i].departament);
//		}
//		//dezalocare pentru vector angajati
//		free(angajati);
//	}
//}
//
//void main() {
//	//cerinta 1
//	printf("\nCerinta 1\n");
//	char nume_fisier[30];
//	strcpy_s(nume_fisier, 30, "cerinta1.txt");
//	//adaugare_valori_fisier(nume_fisier);
//	//cerinta 2
//	printf("\nCerinta 2\n");
//	//eliminare_elemente_din_fisier(nume_fisier);
//	//cerinta 3
//	printf("\nCerinta 3\n");
//	strcpy_s(nume_fisier, 30, "cerinta3.txt");
//	//adaugare_angajati_fisier(nume_fisier);
//	//cerinta 4
//	printf("\nCerinta 4\n");
//	eliminare_angajati_din_fisier(nume_fisier);
//}