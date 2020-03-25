#include<stdlib.h>
#include<stdio.h>

float suma(float* valori, int n) {
	float s;
	if (n < 0) {
		s = 0;
	}
	else {
		s = valori[n] + suma(valori, n - 1);
	}
	return s;
}

//Ak,n=n*Ak-1,n-1; unde A1,n=n;
int aranjament(int n, int k) {
	int rezultat;
	if (k == 1) {
		rezultat = n;
	}
	else {
		rezultat = n * aranjament(k - 1, n - 1);
	}
	return rezultat;
}
//Implementam maximului unui vector, folosind devide et impera prin compararea elemetului
//maxim din prima jumatate a vectorului cu cel din cea de a doua jumatate
float maxim_di_v1(float* vector, int index, int dim) {
	float max_jum_1, max_jum_2;
	if (index == dim) {
		return vector[index];
	}
	else {
		max_jum_1 = maxim_di_v1(vector, index, (dim + index) / 2);
		max_jum_2 = maxim_di_v1(vector, (dim + index) / 2 + 1, dim);
		return max_jum_1 > max_jum_2 ? max_jum_1 : max_jum_2;
	}
}


//Implementam maximului unui vector, folosind devide et impera prin compararea 
//elementului maxim din primele n-1 valori ale vectorului cu cel de pe pozitia n
float max_di_v2(float* vector, int dim) {
	float max_ant;
	if (dim == 0) {
		return vector[dim];
	}
	else {
		max_ant=max_di_v2(vector, dim - 1);
		return max_ant > vector[dim] ? max_ant : vector[dim];
	}
}

void afisare_vector(float* vector, int dim, int index) {
	if (index < dim) {
		printf("\nVector[%d]=%2.2f", index, vector[index]);
		afisare_vector(vector, dim, index + 1);
	}
}

int element_lipsa(int* vector, int dim, int index_s, int index_d, int dif) {
	if (index_d < index_s) {
	//nu exista element lipsa
		return -1;
	}
	int mij =index_d- (index_d - index_s) / 2;
	//verificam vecinul din dreapta
	if (mij + 1 < dim && (vector[mij + 1] - vector[mij]) != dif) {
		return vector[mij] + dif;//inseamna ca lipseste primul element dupa mijloc
	}
	//verificam vecinu din stanga
	else if (mij - 1 >= 0 && (vector[mij] - vector[mij - 1]) != dif) {
		return vector[mij] - dif;//inseamna ca lipseste primul element inainte de mijloc
	}
	//determinam in ce parte refacem procesarea recursiva
	return (vector[mij] - vector[index_s]) != mij * dif
		? element_lipsa(vector, dim, index_s, mij - 1, dif)
		: element_lipsa(vector, dim, mij + 1, index_d, dif);
}

int calcul_diferenta_element_lipsa_vector(int* valori, int n) {
	int dif = 0;
	for (int i = 1; i < n; i++) {
		if ((valori[i] - valori[i - 1]) == dif) {
			return dif;
		}
		else {
			dif = valori[i] - valori[i - 1];
		}
	}
}
void exemplu_suma_vector_recursiva() {
	int n;
	printf("\nDimensiune vector: ");
	scanf_s("%d", &n);
	float* valori = (float*)malloc(sizeof(float)*n);
	for (int i = 0; i < n; i++) {
		printf("\nvalori[%d]= ", i);
		scanf_s("%f", &valori[i]);
	}
	printf("\nSuma recursa: %2.2f", suma(valori, n - 1));
}

void exemplu_aranjament_n_k() {
	int k, n;
	printf("\nIntroduceti k: ");
	scanf_s("%d", &k);
	printf("\nIntroduceti n: ");
	scanf_s("%d", &n);
	printf("\n Rezultat aranjament n luat cate k: %d", aranjament(n, k));
}

void exemplu_devide_et_impera_max_vector() {
	int n;
	printf("\nDimensiune vector: ");
	scanf_s("%d", &n);
	float* valori = (float*)malloc(sizeof(float)*n);
	for (int i = 0; i < n; i++) {
		printf("\nvalori[%d]= ", i);
		scanf_s("%f", &valori[i]);
	}
	printf("\nMaxim v1: %2.2f", maxim_di_v1(valori,0,n-1));
	printf("\nMaxim v2: %2.2f", max_di_v2(valori, n - 1));
}

void exemplu_devide_impera_afisare_elemente_vector() {
	int n;
	printf("\nDimensiune vector: ");
	scanf_s("%d", &n);
	float* valori = (float*)malloc(sizeof(float)*n);
	for (int i = 0; i < n; i++) {
		printf("\nvalori[%d]= ", i);
		scanf_s("%f", &valori[i]);
	}
	afisare_vector(valori, n, 0);
}

//Problema: Se da un vector v, dimensiune n>0, avand proprietatea 
//ca diferenta intre elementele consecutive este constanta.
//Diferenta este calculata astfel: (v[n-1]-v[0])/n;
//Ex: vector = [5,7,9,11,15], n=5, diferenta = 2;
//Element lipsa 13;
void exemplu_devide_impera_identificare_element_lipsa_vector() {
	int n;
	printf("\nDimensiune vector: ");
	scanf_s("%d", &n);
	int* valori = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		printf("\nvalori[%d]= ", i);
		scanf_s("%d", &valori[i]);
	}
	int dif = calcul_diferenta_element_lipsa_vector(valori, n);
	printf("\nElement lipsa: %d", element_lipsa(valori,n,0,n-1,dif));
}
void main() {
	printf("\n+++++++++++++++++++++++ exemplu_suma_vector_recursiva ++++++++++++++++++++++++\n");
	//exemplu_suma_vector_recursiva();
	printf("\n++++++++++++++++++++++ exemplu_aranjament_n_k +++++++++++++++++++++++++\n");
	//exemplu_aranjament_n_k();
	printf("\n++++++++++++++++++++++ exemplu_devide_et_impera_max_vector +++++++++++++++++++++++++\n");
	//exemplu_devide_et_impera_max_vector();
	printf("\n++++++++++++++++++++++ exemplu_devide_impera_afisare_elemente_vector +++++++++++++++++++++++++\n");
	//exemplu_devide_impera_afisare_elemente_vector();
	printf("\n++++++++++++++++++++++ exemplu_devide_impera_identificare_element_lipsa_vector +++++++++++++++++++++++++\n");
	//exemplu_devide_impera_identificare_element_lipsa_vector();
}