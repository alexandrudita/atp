#include<stdlib.h>
#include<stdio.h>
struct Eticheta {
	int varf;
	float lungime;
};

//============================== METODE UTILITARE =========================================
float** initializare_matrice(int n, float val_max) {
	float** ma = (float**)malloc(sizeof(float*)*n);
	for (int i = 0; i < n; i++) {
		ma[i] = (float*)malloc(sizeof(float)*n);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			ma[j][i] = ma[i][j] = val_max;
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

//============================== MATRICE DE ADIACENTA ==================================
float** citire_matrice_ponderilor_graf(int& nr_v, float val_max) {
	//citim toate nodurile dintr-un fisier care are structua prima lini numarul de varf si numarul de muchii,
	//dupa care pe fiecare linie este scris nodul de inceput si nodul de final intre care se realizeaza o muchie
	float** ma = NULL;
	FILE* fisier;
	//deschidem fisierul
	fopen_s(&fisier, "graf_ponderat.txt", "r");
	//verificam daca fisierul s-a deschis
	if (fisier) {
		//citim numarul de varfuri
		fscanf_s(fisier, "%d", &nr_v);
		//initializam matricea de adiacenta cu valorea 0
		ma = initializare_matrice(nr_v, val_max);
		int nr_m = 0;
		//citim nr de muchii
		fscanf_s(fisier, "%d", &nr_m);
		//parcurgem toate muchiile si citim nodul de inceput si final
		for (int i = 0; i < nr_m; i++) {
			int vi, vf;
			float cost; 
			fscanf_s(fisier, "%d %d %f", &vi, &vf, &cost);
			//marcam cu 1 intersectia intre nodul de incet si nodul final astfel incat sa stim ca exista o muchie
			ma[vi - 1][vf - 1] = ma[vf - 1][vi - 1] = cost;
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
			tabelara[i] = (int*)malloc(sizeof(int) * 3);
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

//=================================== DIJKSTRA ============================================
Eticheta* dijkstra(float** ma, int nr_v, int varf_initial, float val_max){
	float lmin;
	int varf_min;
	Eticheta* etichete = (Eticheta*)malloc(sizeof(Eticheta)*nr_v);
	for (int i = 0; i < nr_v; i++) {
		etichete[i].lungime = val_max;
	}
	etichete[varf_initial - 1].lungime = 0;
	etichete[varf_initial - 1].varf = varf_initial;
	int* prelucrat = (int*)malloc(sizeof(int)*nr_v);
	for (int i = 0; i < nr_v; i++) {
		prelucrat[i] = 0;
	}
	prelucrat[varf_initial - 1] = 1;
	int ui = varf_initial;
	for (int it = 0; it < nr_v - 1; it++) {
		lmin = val_max;
		for (int varf = 1; varf <= nr_v; varf++) {
			if (prelucrat[varf - 1] == 0 
				&& (etichete[varf - 1].lungime > etichete[ui - 1].lungime + ma[varf - 1][ui - 1])) {
				etichete[varf - 1].lungime = etichete[ui - 1].lungime + ma[varf - 1][ui - 1];
				etichete[varf - 1].varf = ui;
			}
			if (prelucrat[varf - 1] == 0 && etichete[varf - 1].lungime < lmin) {
				lmin = etichete[varf - 1].lungime;
				varf_min = varf;
			}
		}
		ui = varf_min;
		prelucrat[ui - 1] = 1;
	}
	free(prelucrat);
	return etichete;
}

void afisare_dijkstra(Eticheta* rez,int nr_v, int v0) {
	int u;
	for (int v = 1; v <= nr_v; v++)
		if (v != v0)
		{
			printf("Costul unui cel mai ieftin drum de la %i la %i este %8.3f", v, v0, rez[v - 1].lungime);
			printf("\n Un drum de cost minim: %i ", v);
			u = v;
			while (rez[u - 1].varf != v0)
			{
				printf("%i ", rez[u - 1].varf);
				u = rez[u - 1].varf;
			}
			printf("%i \n\n", v0);
		}
}

//========================================= KRUSKAL ==========================
int radacina(int varf, int* tata) {
	int u = varf;
	while (tata[u] >= 0) {
		u=tata[u];
	}
	return u;
}

int kruskal(int a[][3], int nr_muchii, int nr_varfuri) {
	int tata[50];
	int v1, v2, k, p, c = 0;
	for (int i = 0; i < nr_varfuri; i++) {
		tata[i] = -1;
	}
	for (int j=0, i = 0; i < nr_varfuri - 1; j++) {
		int v1 = a[j][0];
		int v2 = a[j][1];
		k = radacina(v2, tata);
		p = radacina(v1, tata);
		if (k - p) {
			if (tata[k] < tata[p]) {
				tata[k] += tata[p];
				tata[p] = k;
			}
			else {
				tata[p] += tata[k];
				tata[k] = p;
			}
			c += a[j][2];
			printf("%d->%d cost %d\n", v1 + 1, v2 + 1, a[j][2]);
			i++;
		}
	}
	return c;
}

//=================================== PRIM ============================
float prim(float **ma, int n, int v0, int ***arb, float MAX)
{
	float cost, cmin;
	int i, u, v, vf1, vf2;
	cost = 0;
	int *ind = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		ind[i] = 0;
	ind[v0 - 1] = 1;
	//ind este vectorul indicator:
	//ind[i]=1 daca virful i+1 a fost trecut in A, altfel este 0
	int **muchii = (int**)malloc((n - 1) * sizeof(int*));
	for (i = 0; i < n - 1; i++)
		muchii[i] = (int*)malloc(2 * sizeof(int));
	for (i = 0; i < n - 1; i++)
	{
		cmin = MAX;
		for (u = 1; u <= n; u++)
			if (ind[u - 1])
				for (v = 1; v <= n; v++)
					if ((!ind[v - 1]) && (ma[u - 1][v - 1] <= cmin))
					{
						vf1 = u;
						vf2 = v;
						cmin = ma[u - 1][v - 1];
					}
		cost += cmin;
		muchii[i][0] = vf1;
		muchii[i][1] = vf2;
		ind[vf2 - 1] = 1;
	}
	*arb = muchii;
	free(ind);
	return cost;
}

void apel_dijkstra() {
	int nr_v;
	float** ma = citire_matrice_ponderilor_graf(nr_v, 100000000000);
	Eticheta* rez = dijkstra(ma, nr_v, 1, 100000000000000);
	afisare_dijkstra(rez, nr_v, 1);
	free(rez);
	for (int i = 0; i < nr_v; i++) {
		free(ma[i]);
	}
	free(ma);
}

void apel_kruskal() {
	int cost, i, j, nv, nm, a[100][3];
	//graful este preluat de la tastatura
	//datele citite:numarul de virfuri, numarul de muchii si tabela 
	//muchiilor in ordinea crescatoare a costurilor
	printf("Numarul de virfuri:"); scanf_s("%i", &nv);
	printf("Numarul de muchii:"); scanf_s("%i", &nm);
	printf("Matricea de reprezentare\n");
	for (i = 0; i < nm; i++)
	{
		printf("Muchia %i si ponderea:", i + 1);
		for (j = 0; j < 3; j++)
			scanf_s("%i", &a[i][j]);
	}
	for (i = 0; i < nm; i++)
		for (j = 0; j < 2; j++)a[i][j]--;
	printf("Arborele de cost minim: \n");
	cost = kruskal(a, nm, nv);
	printf("\ncu costul %i", cost);
}

void apel_prim()
{
	int i, j, nv, nm, v, u, v0, **arb; float **ma, MAX = 1000000, cost, p;
	//graful este preluat de la tastatura
	//datele citite:numarul de virfuri, numarul de muchii si matricea ponderilor
	printf("Numarul de virfuri:"); scanf("%i", &nv);
	printf("Numarul de muchii:"); scanf("%i", &nm);

	//alocare memorie pentru matricea ponderilor
	ma = (float**)malloc((nv) * sizeof(float*));
	for (i = 0; i < nv; i++)
		ma[i] = (float*)malloc(nv * sizeof(float));

	printf("Matricea ponderilor\n");
	for (i = 0; i < nv; i++)
		for (j = 0; j < nv; j++)
			ma[i][j] = MAX;
	for (i = 0; i < nm; i++)
	{
		printf("Muchia %i si ponderea:", i + 1);
		scanf("%i %i %f", &v, &u, &p);
		ma[u - 1][v - 1] = ma[v - 1][u - 1] = p;
	}
	printf("Introduceti varful de pornire:");
	scanf("%i", &v0);

	cost = prim(ma, nv, v0, &arb, MAX);
	printf("\nArborele partial de cost minim este:\n");
	for (i = 0; i < nv - 1; i++)
		printf("%i -> %i\n", arb[i][0], arb[i][1]);
	printf(" cu costul %4.2f\n", cost);
}


void main() {
	apel_dijkstra();
	apel_kruskal();
	apel_prim();
}