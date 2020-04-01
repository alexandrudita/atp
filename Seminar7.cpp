#include<stdio.h>
#include<stdlib.h>

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
float* preluare_vector_fisier(int& dim) {
	FILE* fisier;
	fopen_s(&fisier, "vector.txt", "r");
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

void interclasare(float* &vector, int index_s, int index_mij, int index_f)
{
	int i, j, k; 
	float* temp;
	//calculez dimensiunea vectorului
	int dim = (index_f - index_s) + 1;
	i = index_s; j = index_mij + 1; k = 0;
	//definesc vector temp in care sa sortez elementele
	temp = (float*)malloc(sizeof(float)*dim);
	//parcurg cele 2 jum ale vector si compar elementele
	while ((i <= index_mij) && (j <= index_f))
	{
		if (vector[i] < vector[j])
		{
			temp[k] = vector[i]; i++; k++;
		}
		else
		{
			temp[k] = vector[j]; j++; k++;
		}
	}
	//am pus toate element din a doua jumatate, prin urmare copiez ce a mai ramas in prima jum
	if (i <= index_mij) {
		for (int l = i; l <= index_mij; l++)
		{
			temp[k] = vector[l];
			k++;
		}
	}
	//am pus toate elementele din prima jumatate, prin urmare copiez ce a mai ramas in cea de a doua jum
	if (j <= index_f) {
		for (int l = j; l <= index_f; l++)
		{
			temp[k] = vector[l];
			k++;
		}
	}
	int t = index_s;
	//copiezi elementele din vectorul temp in vectorul primit ca param pentru a salva in memorie sortarea
	for (k = 0; k < dim; k++)
		vector[t++] = temp[k];
	free(temp);
}void sortare_numarare(float* &vector, int dim)
{
	int i, j;
	//vector intermediar
	float* temp = (float*)malloc(sizeof(float)*dim);
	int* num = (int*)malloc(sizeof(int)*dim);
	//initializam vector num care o sa retina cate elemente ar depasi valoarea de pe o pozitie i
	for (i = 0; i < dim; i++) {
		num[i] = 0;
	}
	//vector temporar cu toate elementele din vectorul sursa
	for (i = 0; i < dim; i++) {
		temp[i] = vector[i];
	}
	//algoritmul de sortare.
	//se aplica dublu vor pentru a compara elementele din vector
	for (i = 0; i < dim - 1; i++) {
		for (j = i + 1; j < dim; j++) {
			//verificam daca exista un element dupa pozitia i care este mai mic decat cel din i
			if (vector[j] < vector[i]) {
				//numaram cate elemente sunt mai mici decat cel de pe pozitia i
				num[i] = num[i] + 1;
			}
			else {
				num[j] = num[j] + 1;
			}
		}
	}
	//aplicam sortarea pe baza vectorul cu numarari.
	//num are urmatoarea regula: index reprezinta cate elemente sunt mai mici decat cele de pe pozitia i
	for (i = 0; i < dim; i++) {
		vector[num[i]] = temp[i];
	}
	free(temp);
	free(num);
} 
void sortare_di_interclasare(float* &vector, int index_s, int index_f) {
	if (index_s < index_f) {
		int mij = (index_s + index_f) / 2;
		sortare_di_interclasare(vector, index_s, mij);
		sortare_di_interclasare(vector, mij + 1, index_f);
		interclasare(vector, index_s, mij, index_f);
	}
}

void sortare_met_bulelor(float* &vector, int dim) {
	int gata = 0;
	while (gata == 0) {
		gata = 1;
		for (int i = 0; i < dim - 1; i++) {
			//verificam conditia de interschimbare
			if (vector[i] > vector[i + 1]) {
				gata = 0;
				float aux = vector[i];
				vector[i] = vector[i + 1];
				vector[i+1] = aux;
			}
		}
	}
}

void sortare_selectie(float* &vector, int dim) {
	//reprezinta indexul celui mai mic element din secventa
	int p;
	for (int i = 0; i < dim - 1; i++) {
		//initial este cel de pe pozitia i dupa care urmeaza sa l comparam cu celelalte valori
		p = i;
		for (int j = i + 1; j < dim; j++) {
			//conditie de modificare a minimului
			if (vector[j] < vector[p]) {
				p = j;
			}
		}
		//interschimbam cel mai mic element gasit dupa pozitia i cu cel din i
		float aux = vector[p];
		vector[p] = vector[i];
		vector[i] = aux;
	}
}

void sortare_interschimbare(float* &vector, int dim) {
	float aux;
	for (int i = 0; i < dim - 1; i++) {
		for (int j = i + 1; j < dim; j++) {
			if (vector[i] > vector[j]) {
				aux = vector[i];
				vector[i] = vector[j];
				vector[j] = aux;
			}
		}
	}
}

void main() {
	int dim = 0;
	float* vector = preluare_vector_fisier(dim);
	afisare(vector, dim);
	printf("\n++++++++++++++++++++++++Sortare unui vector folosind interclasarea+++++++++++++++++++++++++\n");
	sortare_di_interclasare(vector, 0, dim - 1);
	afisare(vector, dim);
	printf("\n++++++++++++++++++++++++Sortare unui vector folosind numararea+++++++++++++++++++++++++\n");
	vector = preluare_vector_fisier(dim);
	sortare_numarare(vector, dim);
	afisare(vector, dim);
	printf("\n++++++++++++++++++++++++Sortare unui vector folosind bulele+++++++++++++++++++++++++\n");
	vector = preluare_vector_fisier(dim);
	sortare_met_bulelor(vector, dim);
	afisare(vector, dim);
	printf("\n++++++++++++++++++++++++Sortare unui vector folosind selectia+++++++++++++++++++++++++\n");
	vector = preluare_vector_fisier(dim);
	sortare_selectie(vector, dim);
	afisare(vector, dim);
	printf("\n++++++++++++++++++++++++Sortare unui vector folosind interschimbarea+++++++++++++++++++++++++\n");
	vector = preluare_vector_fisier(dim);
	sortare_interschimbare(vector, dim);
	afisare(vector, dim);
}