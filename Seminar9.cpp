#include<stdio.h>
#include<stdlib.h>

//============= functii comune ==============================
//verificare daca in vector pana la poziat curenta(n) nu exista valori egale
int posibil(int* vector, int n) {
	for (int i = 0; i < n; i++) {
		if (vector[n] == vector[i]) {
			return 0;
		}
	}
	return 1;
}

void retine_solutia(int num, int dim, int* vector) {
	printf("\n Solutia numarul %d: ", num);
	for (int i = 0; i < dim; i++) {
		printf("%d ", vector[i]);
	}
}
//=================================================================
//1. Sa se genereze toate permutarile unei multimi cu elemente. 
//subprogram care genereaza permutari de n elemente
int permutari(int n) {
	int* solutie = (int*)malloc(sizeof(int)*n);
	//prima valoare 
	solutie[0] = 0;
	//numar solutii
	int nr = 0;
	int i = 0;
	int acceptat = 0;
	while (i >= 0) {
		acceptat = 0;
		//se alege urmatoarea valoare acceptata 
		while (solutie[i] < n && acceptat == 0) {
			solutie[i]++;
			acceptat = posibil(solutie, i);
		}
		//nu s-a gasit o solutie acceptata pentru pozitia i
		if (acceptat == 0) {
			i--;
		}
		//am ajuns la finalul configuratiei
		else if(i==n-1) {
			retine_solutia(++nr, n, solutie);
		}
		else {
			// nu am identificat o solutie ok
			solutie[++i] = 0;
		}
	}
	//dezalocare vector solutii
	free(solutie);
	return nr;
}

//permutari recursiv
int permutari_recursiv(int n, int pas_curent, int* solutie_partiala, int nr_solutii) {
	if (pas_curent == n) {
		retine_solutia(++nr_solutii, n, solutie_partiala);
	}
	else {
		for (int j = 1; j <= n; j++) {
			solutie_partiala[pas_curent] = j;
			if (posibil(solutie_partiala, pas_curent) == 1) {
				nr_solutii = permutari_recursiv(n, pas_curent + 1, solutie_partiala, nr_solutii);
			}
		}
	}
	return nr_solutii;
}

void apel_permutari() {
	printf("\n============================= START - apel_permutari =============================");
	int numar, nr_permutari;
	printf("\nNumar: "); 
	scanf_s("%d", &numar);
	int* solutie = (int*)malloc(sizeof(int)*numar);
	//iterativ
	printf("\nRezultat permutari varinta iterativa:");
	nr_permutari = permutari(numar);
	printf("\nNumar total de permutari %d", nr_permutari);
	//recursiv
	printf("\nRezultat permutari varinta recursiva:");
	nr_permutari = permutari_recursiv(numar, 0, solutie, 0);
	printf("\nNumar total de permutari %d", nr_permutari);
	free(solutie);
	printf("\n============================= END - apel_permutari =============================");
}
//================================================================
//2. Sa se genereze toate aranjamentele dintr-o multime cu elemente.
int aranjamente(int n, int k, int pas_curent, int* solutie_partiala, int nr_solutii) {
	if (pas_curent == k) {
		retine_solutia(++nr_solutii, k, solutie_partiala);
	}
	else {
		for (int i = 1; i <= n; i++) {
			solutie_partiala[pas_curent] = i;
			if (posibil(solutie_partiala, pas_curent)==1) {
				nr_solutii = aranjamente(n, k, pas_curent + 1, solutie_partiala, nr_solutii);
			}
		}
	}
	return nr_solutii;
}

void apel_aranjamente() {
	printf("\n============================= START - apel_aranjamente =============================");
	int n, k, nr;
	printf("\nn: ");
	scanf_s("%d", &n);
	printf("\nk: ");
	scanf_s("%d", &k);
	int* solutie = (int*)malloc(sizeof(int)*n);
	if (k > 0 && k <= n) {
		nr = aranjamente(n, k, 0, solutie, 0);
		printf("\nNumarul de aranjamente este: %d", nr);
	}
	else {
		printf("\nNu exista solutii");
	}
	free(solutie);
	printf("\n============================= END - apel_aranjamente =============================");
}
//================================================================
//3. Sa se genereze toate combinarile dintr-o multime cu elemente
void afiseaza(int k, int* vector) {
	for (int i = 0; i < k; i++) {
		printf("\n%d ", vector[i]);
	}
}

int verificare_acceptanta(int p, int* solutie) {
	if (p > 0 && solutie[p] <= solutie[p - 1]) {
		return 0;
	} 
	return 1;
}

void combinari(int p, int n, int k, int* solutie_partiala) {
	for (int i = 1; i <= n; i++) {
		solutie_partiala[p] = i;
		if (verificare_acceptanta(p, solutie_partiala) == 1) {
			if (p == k - 1) {
				afiseaza(k, solutie_partiala);
			}
			else {
				combinari(p + 1, n, k, solutie_partiala);
			}
		}
	}
}

void apel_combinari() {
	printf("\n============================= START - apel_combinari =============================");
	int n, k, nr;
	printf("\nn: ");
	scanf_s("%d", &n);
	printf("\nk: ");
	scanf_s("%d", &k);
	int* solutie = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		solutie[i] = 0;
	}
	if (k > 0 && k <= n) {
		combinari(0, n, k, solutie);
	}
	else {
		printf("\nNu exista solutii");
	}
	free(solutie);
	printf("\n============================= END - apel_combinari =============================");
}
//================================================================
//4. Problema celor 8 (n) regine. Se cere să se așeze 8 regine pe o tablă de șah astfel încît să nu existe două
//regine care să se atace.Trebuie găsite toate posibilitățile de așezare a celor 8 regine pe tabla de șah.
int continua(int* solutie_partiala, int n) {
	for (int i = 1; i < n; i++) {
		//prima conditie verifica daca 2 regine sunt pe aceeasi pozitie pe tabla de sah sau pe linie 
		if (solutie_partiala[n] == solutie_partiala[i]
			//a doua conditie verifica daca 2 regine sunt pe aceeasi linie sau coloana sau diagonala
			|| abs(n - i) == abs(solutie_partiala[n] - solutie_partiala[i])) {
			return 0;
		}
	}
	return 1;
}

void afisare_solutie_partiala(int nr, int n, int* solutie) {
	printf("\nSolutia numarul %d\n", nr);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%c", j == solutie[i] ? 'R' : 'x');
		}
		printf("\n");
	}
}

int regine(int n) {
	int* solutie = (int*)malloc(sizeof(int)*(n + 1));
	int nr = 0;
	solutie[1] = 0;
	int i = 1;
	int cont;
	while (i > 0) {
		cont = 0;
		//cautam urmatoarea valoare acceptabila 
		while (solutie[i] < n && cont == 0) {
			solutie[i]++;
			cont = continua(solutie, i);
		}
		//verificare motiv oprire din while
		// nu este o solutie acceptabila
		if (cont == 0) {
			i--;
		}
		//am ajuns la final
		else if (i == n) {
			afisare_solutie_partiala(++nr, n, solutie);
		}
		else {
			//trecem la urmatoarea pozitie
			solutie[++i] = 0;
		}
	}
	free(solutie);
	return nr;
}

int regine_recursiv(int n, int pas_curent, int* solutie_partiala, int nr) {
	if (pas_curent == n + 1) {
		afisare_solutie_partiala(++nr, n, solutie_partiala);
	}
	else {
		for (int j = 1; j <= n; j++) {
			solutie_partiala[pas_curent] = j;
			if (continua(solutie_partiala, pas_curent) == 1) {
				nr = regine_recursiv(n, pas_curent + 1, solutie_partiala, nr);
			}
		}
	}
	return nr;
}

void apel_regine() {
	printf("\n============================= START - apel_regine =============================");
	int numar, nr;
	printf("\nNumar: ");
	scanf_s("%d", &numar);
	int* solutie = (int*)malloc(sizeof(int)*(numar+1));
	//iterativ
	printf("\nRezultat regine varinta iterativa:");
	nr = regine(numar);
	printf("\nNumar total de solutii %d", nr);
	//recursiv
	printf("\nRezultat regina varinta recursiva:");
	//nr = regine_recursiv(numar, 1, solutie, 0);
	printf("\nNumar total de solutii %d", nr);
	free(solutie);
	printf("\n============================= END - apel_regine =============================");
}
//================================================================

void main() {
	//apel_permutari();
	//apel_aranjamente();
	//apel_combinari();
	apel_regine();
}
