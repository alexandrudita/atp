#include<stdio.h>
#include<stdlib.h>

//============================== METODE UTILITARE =========================================
int* initializare_vector_vizitate(int nr_noduri) {
	//vectorul are dimensiunea egala cu nr de noduri din graf
	//initializam vectorul cu valoarea 0
	int* vizitate = (int*)malloc(sizeof(int)*nr_noduri);
	for (int i = 0; i < nr_noduri; i++) {
		vizitate[i] = 0;
	}
	return vizitate;
}

int** initializare_matrice(int n) {
	int** ma = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++) {
		ma[i] = (int*)malloc(sizeof(int)*n);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			ma[j][i] = ma[i][j] = 0;
		}
	}
	return ma;
}

void afisare_matrice_consola(int** ma, int nr_linii, int nr_coloane) {
	for (int i = 0; i < nr_linii; i++) {
		for (int j = 0; j < nr_coloane; j++) {
			printf("%d ", ma[i][j]);
		}
		printf("\n");
	}
}

void afisare_vector(int* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		printf("%d ", vector[i]);
	}
}

//============================== CITIRE GRAF FORMA TABELARA ==================================
int** citire_tabelara_graf(int& nr_v, int &nr_m) {
	int** tabelara = NULL;
	FILE* fisier;
	//deschidem fisierul
	fopen_s(&fisier, "graf.txt", "r");
	//verificam daca fisierul s-a deschis
	if (fisier) {
		//citim numarul de varfuri
		fscanf_s(fisier, "%d %d", &nr_v, &nr_m);
		tabelara = (int**)malloc(sizeof(int*)*nr_m);
		for (int i = 0; i < nr_m; i++) {
			tabelara[i] = (int*)malloc(sizeof(int) * 2);
		}
		//parcurgem toate muchiile si citim nodul de inceput si final
		for (int i = 0; i < nr_m; i++) {
			int vi, vf;
			fscanf_s(fisier, "%d %d", &vi, &vf);
			tabelara[i][0] = vi;
			tabelara[i][1] = vf;
		}
		//inchidem fisierul dupa procesare
		fclose(fisier);
	}
	else {
		printf("\n Fisierul nu se poate deschide");
	}
	//returnam matricea de adiacenta
	return tabelara;
}

int** citire_tabelara_graf_ponderat(int& nr_v, int &nr_m) {
	int** tabelara = NULL;
	FILE* fisier;
	//deschidem fisierul
	fopen_s(&fisier, "graf_ponderat.txt", "r");
	//verificam daca fisierul s-a deschis
	if (fisier) {
		//citim numarul de varfuri
		fscanf_s(fisier, "%d %d", &nr_v, &nr_m);
		tabelara = (int**)malloc(sizeof(int*)*nr_m);
		for (int i = 0; i < nr_m; i++) {
			tabelara[i] = (int*)malloc(sizeof(int) * 2);
		}
		//parcurgem toate muchiile si citim nodul de inceput si final
		for (int i = 0; i < nr_m; i++) {
			int vi, vf, pondere;
			fscanf_s(fisier, "%d %d %d", &vi, &vf, &pondere);
			tabelara[i][0] = vi;
			tabelara[i][1] = vf;
			tabelara[i][2] = pondere;
		}
		//inchidem fisierul dupa procesare
		fclose(fisier);
	}
	else {
		printf("\n Fisierul nu se poate deschide");
	}
	//returnam matricea de adiacenta
	return tabelara;
}


//============================== MATRICE DE ADIACENTA ==================================
/* Matricea de adiacenta este o matrice patratica care are valori 0 si 1 unde 
0 inseamna ca intre nodul linie si cel de pe coloana nu exista o muchie iar 1 ca exista o muchie*/
int** citire_matrice_adiacenta_graf(int& nr_v) {
	//citim toate nodurile dintr-un fisier care are structua prima lini numarul de varf si numarul de muchii,
	//dupa care pe fiecare linie este scris nodul de inceput si nodul de final intre care se realizeaza o muchie
	int** ma = NULL;
	FILE* fisier;
	//deschidem fisierul
	fopen_s(&fisier, "graf.txt", "r");
	//verificam daca fisierul s-a deschis
	if (fisier) {
		//citim numarul de varfuri
		fscanf_s(fisier, "%d", &nr_v);
		//initializam matricea de adiacenta cu valorea 0
		ma = initializare_matrice(nr_v);
		int nr_m = 0;
		//citim nr de muchii
		fscanf_s(fisier, "%d", &nr_m);
		//parcurgem toate muchiile si citim nodul de inceput si final
		for (int i = 0; i < nr_m; i++) {
			int vi, vf;
			fscanf_s(fisier, "%d %d", &vi, &vf);
			//marcam cu 1 intersectia intre nodul de incet si nodul final astfel incat sa stim ca exista o muchie
			ma[vi - 1][vf - 1] = ma[vf - 1][vi - 1] = 1;
		}
		//inchidem fisierul dupa procesare
		fclose(fisier);
	}
	else {
		printf("\n Fisierul nu se poate deschide");
	}
	//returnam matricea de adiacenta
	return ma;
}

int** citire_matrice_adiacenta_graf_ponderat(int& nr_v) {
	//citim toate nodurile dintr-un fisier care are structua prima lini numarul de varf si numarul de muchii,
	//dupa care pe fiecare linie este scris nodul de inceput si nodul de final intre care se realizeaza o muchie
	int** ma = NULL;
	FILE* fisier;
	//deschidem fisierul
	fopen_s(&fisier, "graf_ponderat.txt", "r");
	//verificam daca fisierul s-a deschis
	if (fisier) {
		//citim numarul de varfuri
		fscanf_s(fisier, "%d", &nr_v);
		//initializam matricea de adiacenta cu valorea 0
		ma = initializare_matrice(nr_v);
		int nr_m = 0;
		//citim nr de muchii
		fscanf_s(fisier, "%d", &nr_m);
		//parcurgem toate muchiile si citim nodul de inceput si final
		for (int i = 0; i < nr_m; i++) {
			int vi, vf, pondere;
			fscanf_s(fisier, "%d %d %d", &vi, &vf, &pondere);
			//adaugam ponderea din fisier pentru intersectia celor doua noduri
			ma[vi - 1][vf - 1] = ma[vf - 1][vi - 1] = pondere;
		}
		//inchidem fisierul dupa procesare
		fclose(fisier);
	}
	else {
		printf("\n Fisierul nu se poate deschide");
	}
	//returnam matricea de adiacenta
	return ma;
}

//============================== METODE COADA  ========================================= 
/*COADA: - adaugarea se face la final, iar citirea se face din varf.
         - in cod la inserare  adaugam noul element pe pozitia dimensiune_coada 
		   deoarece aceasta variabila contine numarul curent de elemente
		 - ne asiguram ca dimensiune_coada creste cu o unitate dupa adaugare
		 - in cazul extragerii tot timpul coada[0] contine primul element dupa care pacurgem intr-un for 
		 toate elementele de la 0 pana n-1(deoarece scadam dimensiunea cu 1) si mutam elemente de pe pozitia i+1 pe i 
		 astfel incat sa eliminam din vectorul coada primul element
*/
int insereaza_coada(int *coada, int dimensiune_coada, int nod_curent) {
	coada[dimensiune_coada] = nod_curent;
	dimensiune_coada++;
	return dimensiune_coada;
}

int extragere_coada(int *coada, int dimensiune_coada, int &nod_curent) {
	nod_curent = coada[0];
	for (int i = 0; i < dimensiune_coada - 1; i++) {
		coada[i] = coada[i + 1];
	}
	dimensiune_coada--;
	return dimensiune_coada;
}

//============================== METODE STIVA =========================================
/*STIVA: - inserarea si extragere se fac tot timpul la inceput
         - in cod operatia de inserare presupune sa adaugam invectorul stiva elementul nou pe pozitia 0 
		 prin urmare facem un for care pleaca de la dimensiune_stiva(dimensiunea curenta inainte de adaugare)
		 si mutam elementele de pe pozitia i pe i+1 astfel incat 0 sa devina libera
		 - nu uitam sa crestem dimensiune_stiva dupa adaugare
		 - in cazul extragerii tot timpul stiva[0] contine ultimul element adaugat dupa care pacurgem 
		 intr-un for toate elementele de la 0 pana n-1(deoarece scadam dimensiunea cu 1) si mutam 
		 elemente de pe pozitia i+1 pe i astfel incat sa eliminam din vectorul coada primul element
		 */
int insereaza_stiva(int* stiva, int dimensiune_stiva, int nod_curent) {
	for (int i = dimensiune_stiva - 1; i >= 0; i--) {
		stiva[i + 1] = stiva[i];
	}
	stiva[0] = nod_curent;
	dimensiune_stiva++;
	return dimensiune_stiva;
}

int extrage_stiva(int *stiva, int dimensiune_stiva, int &nod_curent) {
	nod_curent = stiva[0];
	for (int i = 0; i < dimensiune_stiva - 1; i++) {
		stiva[i] = stiva[i + 1];
	}
	dimensiune_stiva--;
	return dimensiune_stiva;
}

//============================ METODE PARCURGERE BF ========================================
int* parcurgere_bf(int index_nod_inceput, int **matrice_adiacenta, int nr_noduri, int &contor_rezultate) {
	//initializam coada in care punem nodurile ce urmeaza sa fie vizitate in functie de index_nod_inceput
	int* coada = (int*)malloc(sizeof(int)*nr_noduri);
	//initializam vector in care marcam nodurile din graf ce au fost deja vizitate, astfel incat sa nu procesam de mai multe ori acelas nod
	//intre noduri si pozitia din aceast vector este relatia ca nodurile sunt asezate in ordinea crescatoare,
	//astfel: pe pozitia 0 din vector se afla nodul 1, pe pozitia 1 se afla nodul 2 etc.
	int* vizitate = initializare_vector_vizitate(nr_noduri);
	//initilizare vector rezultat care o sa contina ordinea de parcurgere a nodurilor
	int* rezultat = (int*)malloc(sizeof(int)*nr_noduri);
	//dimensiunea cozii. aceasta varibila se modifica dinamic pe masura ce un nod este vizitat
	int dim_coada = 0;
	//adaugam in coada de parcurgere nodul de inceput
	dim_coada = insereaza_coada(coada, dim_coada, index_nod_inceput);
	//marcam nodul de inceput ca fiind vizitat
	vizitate[index_nod_inceput] = 1;
	//variabila care contine nodul ce urmeaza sa l procesam
	int index_nod_curent = 0;
	//cat timp nu am terminat de parcurs toate elementele din graf procesam acest algoritm
	while (dim_coada) {
		//scoatem din coada primul element si il procesam. valoarea acestuia se afla in index_nod_curent
		dim_coada = extragere_coada(coada, dim_coada, index_nod_curent);
		//in vector rezultat adaugam nodul procesat. NU uitati adaugam 1 la index deoarece exista relatia specificata la vector vizitat.
		rezultat[contor_rezultate++]= index_nod_curent + 1; 
		//parcurgem matricea de adiacenta pentru a gasi toate nodurile cu care cel curent are o muchie
		for (int k = 0; k < nr_noduri; k++) {
			//conditia ca un nod nou sa fie adaugat in coada este urmatoarea: 
			// -> intre nodul curent si altul din grafic sa existe o muchie
			// -> nodul k din graf cu care cel curent are o muchie sa nu fie marcat ca vizitat 
			if (matrice_adiacenta[index_nod_curent][k] == 1 && vizitate[k] == 0) {
				//adaugam in coada noul nod cu care cel curent are o muchie
				dim_coada = insereaza_coada(coada, dim_coada, k);
				//marcam noul nod ca vizitat ca sa evitam dubla procesare
				vizitate[k] = 1;
			}
		}
	}
	//dezalocam variabilele intermediare alocate dinamic
	free(coada);
	free(vizitate);
	//intoarcem rezultatul gasit
	return rezultat;
}

//============================ METODE PARCURGERE DF ========================================
int* parcurgere_df(int index_nod_inceput, int **matrice_adiacenta, int nr_noduri, int &contor_rezultate) {
	//initializam stiva in care punem nodurile ce urmeaza sa fie vizitate in functie de index_nod_inceput
	int* stiva = (int*)malloc(sizeof(int)*nr_noduri);
	//initializam vector in care marcam nodurile din graf ce au fost deja vizitate, astfel incat sa nu procesam de mai multe ori acelas nod
	//intre noduri si pozitia din aceast vector este relatia ca nodurile sunt asezate in ordinea crescatoare,
	//astfel: pe pozitia 0 din vector se afla nodul 1, pe pozitia 1 se afla nodul 2 etc.
	int* vizitate = initializare_vector_vizitate(nr_noduri);
	//initilizare vector rezultat care o sa contina ordinea de parcurgere a nodurilor
	int* rezultat = (int*)malloc(sizeof(int)*nr_noduri);
	//dimensiunea stivei. aceasta varibila se modifica dinamic pe masura ce un nod este vizitat
	int dim_stiva = 0;
	dim_stiva = insereaza_stiva(stiva, dim_stiva, index_nod_inceput);
	//marcam nodul de inceput ca fiind vizitat
	vizitate[index_nod_inceput] = 1;
	//variabila care contine nodul ce urmeaza sa l procesam
	int index_nod_curent = 0;
	//cat timp nu am terminat de parcurs toate elementele din graf procesam acest algoritm
	while (dim_stiva) {
		//scoatem din stiva primul element si il procesam. valoarea acestuia se afla in index_nod_curent
		dim_stiva = extrage_stiva(stiva, dim_stiva, index_nod_curent);
		//in vector rezultat adaugam nodul procesat. NU uitati adaugam 1 la index deoarece exista relatia specificata la vector vizitat.
		rezultat[contor_rezultate++] = index_nod_curent + 1;
		//parcurgem matricea de adiacenta pentru a gasi toate nodurile cu care cel curent are o muchie
		for (int k = 0; k < nr_noduri; k++) {
			//conditia ca un nod nou sa fie adaugat in stiva este urmatoarea: 
			// -> intre nodul curent si altul din grafic sa existe o muchie
			// -> nodul k din graf cu care cel curent are o muchie sa nu fie marcat ca vizitat 
			if (matrice_adiacenta[index_nod_curent][k] == 1 && vizitate[k] == 0) {
				//adaugam in stiva noul nod cu care cel curent are o muchie
				dim_stiva = insereaza_stiva(stiva, dim_stiva, k);
				//marcam noul nod ca vizitat ca sa evitam dubla procesare
				vizitate[k] = 1;
			}
		}
	}
	//dezalocam variabilele intermediare alocate dinamic
	free(stiva);
	free(vizitate);
	//intoarcem rezultatul gasit
	return rezultat;
}

void apel_parcurgere_bf() {
	printf("\nCitire matrice adiacenta graf");
	int nr_v = 0;
	int** ma = citire_matrice_adiacenta_graf(nr_v);
	afisare_matrice_consola(ma, nr_v, nr_v);
	int varf = 1;
	printf("\nvarf=");
	scanf_s("%d", &varf);
	printf("\nParcurgere bf\n");
	int dim_rez = 0;
	int* rezultat = parcurgere_bf(varf - 1, ma, nr_v, dim_rez);
	afisare_vector(rezultat, dim_rez);
	free(rezultat);
	for (int i = 0; i < nr_v; i++) {
		free(ma[i]);
	}
	free(ma);
}

void apel_parcurgere_df() {
	printf("\nCitire matrice adiacenta graf");
	int nr_v = 0;
	int** ma = citire_matrice_adiacenta_graf(nr_v);
	afisare_matrice_consola(ma, nr_v, nr_v);
	int varf = 1;
	printf("\nvarf=");
	scanf_s("%d", &varf);
	printf("\nParcurgere df\n");
	int dim_rez = 0;
	int* rezultat = parcurgere_df(varf - 1, ma, nr_v, dim_rez);
	afisare_vector(rezultat, dim_rez);
	free(rezultat);
	for (int i = 0; i < nr_v; i++) {
		free(ma[i]);
	}
	free(ma);
}

void apel_citire_ma_graf_ponderat() {
	printf("\nCitire matrice adiacenta graf ponderat");
	int nr_v = 0;
	int** ma = citire_matrice_adiacenta_graf_ponderat(nr_v);
	afisare_matrice_consola(ma, nr_v, nr_v);
}

void apel_citire_tabelara_graf() {
	printf("\nCitire matrice tabelara graf");
	int nr_v = 0;
	int nr_m = 0;
	int** ma = citire_tabelara_graf(nr_v, nr_m);
	afisare_matrice_consola(ma, nr_m, 2);

}
void apel_citire_tabelara_graf_ponderat() {
	printf("\nCitire matrice tabelara graf ponderat");
	int nr_v = 0;
	int nr_m = 0;
	int** ma = citire_tabelara_graf_ponderat(nr_v, nr_m);
	afisare_matrice_consola(ma, nr_m, 3);
}
void main() {
	apel_citire_ma_graf_ponderat();
	apel_citire_tabelara_graf();
	apel_citire_tabelara_graf_ponderat();
	apel_parcurgere_bf();
	apel_parcurgere_df();
}