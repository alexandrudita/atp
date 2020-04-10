#include<stdlib.h>
#include<stdio.h>

int determinare_nr_el_fisier(FILE* fisier) {
	int dim = 0;
	float valoare;
	while (!feof(fisier)) {
		fscanf_s(fisier, "%f", &valoare);
		dim++;
	}
	return dim;
}
void citeste_elemente_recursiv(FILE* fisier, float* &vector, int dim) {
	if (dim != 0) {			
		citeste_elemente_recursiv(fisier, vector, dim - 1);
	}
	fscanf_s(fisier, "%f", &vector[dim]);
}

//fisierul NU contine pe prima linie numarul de elemente. Acesta trebuie determinat
float* preluare_vector_fisier(const char* nume_fisier, int& dim) {
	FILE* fisier;
	fopen_s(&fisier, nume_fisier, "r");
	if (fisier != NULL) {
		//determinare numar de element din vector
		dim = determinare_nr_el_fisier(fisier);
		//repozitionare la inceput in fisier
		rewind(fisier);
		//alocare spatiu de memorie vector dinamic de float
		float* rezultate = (float*)malloc(sizeof(float)*dim);
		//citire element din fisier in mod recursiv
		citeste_elemente_recursiv(fisier, rezultate, dim);
		//inchidere fisier
		fclose(fisier);
		return rezultate;
	}
	else {
		printf("\nFisierul nu s-a putut deschide");
	}
}

void afisare(float* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		printf("\n%2.2f", vector[i]);
	}
}

void afisare(int* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		printf("\n%d", vector[i]);
	}
}

/*
	1. Problema rucsacului - completa
*/
float* procesare_rucsac_completa(float capacitate_totala, float* capacitate_ocupata,
	int nr_elemente){
	//valoarea ptr fiecare element se afla in intervalul [0,1];
	//initializare zona de memorie
	float* rezultat = (float*)malloc(sizeof(float)*nr_elemente);
	//tine minte cat mai trebuie sa ocupam din transport
	float capacitate_ramasa = capacitate_totala;
	for (int i = 0; i < nr_elemente && capacitate_ramasa>0; i++) {
		if (capacitate_ramasa >= capacitate_ocupata[i]) {
			//adaug toata capacitatea in transport
			rezultat[i] = 1;
			//scad ce am adaugat
			capacitate_ramasa -= capacitate_ocupata[i];
		}
		else {
			//fractiune din capacitatea_ocupata astfel incat sa transform capacitatea_ramasa= 0
			rezultat[i] = capacitate_ramasa / capacitate_ocupata[i];
			capacitate_ramasa = 0;
			for (int j = i + 1; j < nr_elemente; j++) {
				rezultat[j] = 0;
			}
		}
	}
	return rezultat;
}

/*
	1. Problema rucsacului - intreaga
*/
float* procesare_rucsac_intreaga(float capacitate_totala, float* capacitate_ocupata,
	int nr_elemente) {
	float* rezultat = (float*)malloc(sizeof(float)*nr_elemente);
	float capacitate_ramasa = capacitate_totala;
	for (int i = 0; i < nr_elemente && capacitate_ramasa>0; i++) {
		if (capacitate_ramasa >= capacitate_ocupata[i]) {
			rezultat[i] = 1;
			capacitate_ramasa -= capacitate_ocupata[i];
		}
		else {
			//varianta intreaga nu poate adauga valori partiale
			rezultat[i] = 0;
			capacitate_ramasa = 0;
			for (int j = i + 1; j < nr_elemente; j++) {
				rezultat[j] = 0;
			}
		}
	}
	return rezultat;
}
void sortare(float* &capacitati, float* &venituri, int nr) {
	float aux;
	for (int i = 0; i < nr - 1; i++) {
		for (int j = i + 1; j < nr; j++) {
			//comparam venitul unitar pozitia i respectiv j
			if (venituri[i]/capacitati[i] < venituri[j]/capacitati[j]) {
				aux = venituri[i];
				venituri[i] = venituri[j];
				venituri[j] = aux;
				aux = capacitati[i];
				capacitati[i] = capacitati[j];
				capacitati[j] = aux;
			}
		}
	}
}

void afisare_rucsac(float* capacitati, float* venituri, float* rezultat, int nr){
	float castig = 0;
	for (int i = 0; i < nr; i++) {
		castig += venituri[i] * rezultat[i];
		printf("\n%d: capacitati=%5.2f venituri=%5.2f rezultat=%5.2f castig=%5.2f", i + 1, capacitati[i],
			venituri[i], rezultat[i], castig);
	}
}
void apel_problema_rucsac() {
	int nr;
	float* capacitati = preluare_vector_fisier("capacitati.txt", nr);
	float* venituri = preluare_vector_fisier("venituri.txt", nr);
	printf("\n++++++++++++++++++++++++ afisare capacitati +++++++++++++++++++++++++++++++++++\n");
	afisare(capacitati, nr);
	printf("\n++++++++++++++++++++++++ afisare venituri +++++++++++++++++++++++++++++++++++\n");
	afisare(venituri, nr);
	float capacitate_totala = 0;
	printf("\nIntroduceti capacitatea totala: ");
	scanf_s("%f", &capacitate_totala);
	sortare(capacitati,venituri, nr);
	printf("\n++++++++++++++++++++++++ afisare rezultat - completa +++++++++++++++++++++++++++++++++++\n");
	float* rezultat = procesare_rucsac_completa(capacitate_totala, capacitati, nr);
	afisare_rucsac(capacitati, venituri, rezultat, nr);
	printf("\n++++++++++++++++++++++++ afisare rezultat - intreaga +++++++++++++++++++++++++++++++++++\n");
	rezultat = procesare_rucsac_intreaga(capacitate_totala, capacitati, nr);
	afisare_rucsac(capacitati, venituri, rezultat, nr);
}

/*
	2. Problema sumei maxime
*/
void suma_maxima(float* vector, int nr_v, float* &rezultat, int &nr_r) {
	nr_r = 0;
	for (int i = 0; i < nr_v; i++) {
		if (vector[i] >= 0) {
			rezultat[nr_r++] = vector[i];
		}
	}
}

void apel_problema_suma_maxima() {
	int nr;
	float* vector = preluare_vector_fisier("suma.txt", nr);
	printf("\n++++++++++++++++++++++++ afisare elemente suma vector +++++++++++++++++++++++++++++++++++\n");
	afisare(vector, nr);
	int nr_r;
	float* rezultat = (float*)malloc(sizeof(float)*nr);
	suma_maxima(vector, nr, rezultat, nr_r);
	if (nr_r == 0) {
		printf("\nNu exista o submultime formata din numere pozitive");
	}
	else {
		printf("\n++++++++++++++++++++++++ afisare suma +++++++++++++++++++++++++++++++++++\n");
		afisare(rezultat, nr_r);
	}
}

/*
	3. Plata unei sume cu bacnota unitate
*/
int* plata_unitate(int suma, int* tipuri_bacnote, int nr_tipuri) {
	//stocam numarul fizic de bacnote utilizate din fiecare tip
	//relatia este pozitia i in vector
	int* rezultat = (int*)malloc(sizeof(int)*nr_tipuri);
	int suma_ramasa = suma;
	for (int i = 0; i < nr_tipuri; i++) {
		//obtin cate bacnote de tip i utilizez pentru suma tinta
		rezultat[i] = suma_ramasa / tipuri_bacnote[i];
		//ce suma ramane de identificat pe i+1
		suma_ramasa = suma_ramasa % tipuri_bacnote[i];
	}
	return rezultat;
}

void sortare_int(int* &vector, int nr) {
	int aux;
	for (int i = 0; i < nr - 1; i++) {
		for (int j = i + 1; j < nr; j++) {
			if (vector[i] < vector[j]) {
				aux = vector[i];
				vector[i] = vector[j];
				vector[j] = aux;
			}
		}
	}
}

void apel_problema_plata_unitate() {
	int nr = 6;
	int* vector = (int*)malloc(sizeof(int)*nr);
	vector[0] = 1; 
	vector[1] = 50; 
	vector[2] = 10; 
	vector[3] = 200; 
	vector[4] = 500; 
	vector[5] = 100; 
	printf("\n++++++++++++++++++++++++ afisare elemente bacnote vector +++++++++++++++++++++++++++++++++++\n");
	float suma;
	printf("\nSuma:");
	scanf_s("%f", &suma);
	//ordonare descrescatoare bacnote, astfel incat sa limitam cat de mult putem numarul fizic de bacnote utilizate
	sortare_int(vector, nr);
	afisare(vector, nr);
	int* rezultat = plata_unitate(suma, vector, nr);
	printf("\n++++++++++++++++++++++++ afisare rezultate bacnote vector +++++++++++++++++++++++++++++++++++\n");
	for (int i = 0; i < nr; i++) {
		printf("\n%d - %d \n", rezultat[i], vector[i]);
	}
}

/*
4. Numarul natural
*/
int verificare(int n, int k) {
	int d = 0;
	for (int i = 2; i <= n / 2; i++) {
		if (n%i == 0) {
			d++;
		}
	}
	/*if (d == k) {
		return 1;
	}
	else {
		return 0;
	}*/
	int r = (d == k) ? 1 : 0;
	return r;
}

int divizor(int k) {
	int n = k + 2;
	while (verificare(n, k) == 0) n++;
	return n;
}

void apel_problema_numar_natural() {
	int k;
	printf("\nIntroduceti numarul de divizori proprii: ");
	scanf_s("%d", &k);
	printf("\nCel mai mic numar natural cu %d divizori proprii este %d\n", k, divizor(k));
}

void main() {
	//apel_problema_rucsac();
	//apel_problema_suma_maxima();
	//apel_problema_plata_unitate();
	apel_problema_numar_natural();
}