 #include<stdio.h>
 #include<stdlib.h>

 int* initializare_vector_vizitate(int nr_noduri) {
	//vectorul are dimensiunea egala cu nr de noduri din graf
	//initializam vectorul cu valoarea 0
	int* vizitate = (int*)malloc(sizeof(int)*nr_noduri);
	for (int i = 0; i < nr_noduri; i++) {
		vizitate[i] = 0;
	}
	return vizitate;
 }

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

 int primul_nevizitat(int* vizitate, int nr)
 {
     for(int i =0;i<nr;i++)
     {
        if(vizitate[i]==0)
        {
         return i;
        }
     }
     return -1;
 }

 void verificare(int nr_noduri, int** ma)
 {
     int* vizitate = (int*)malloc(sizeof(int)*nr_noduri);
     for(int i=0;i<nr_noduri;i++)
     {
         vizitate[i]=0;
     }
     int comp_conexa = 1;
     do
     {
         int index_vi = primul_nevizitat(vizitate, nr_noduri);
     int dim_rez = 0;
     int* rezultat = parcurgere_bf(index_vi, ma, nr_noduri, dim_rez);
     for(int i=0;i<dim_rez;i++)
     {
         int index_vizitate = rezultat[i] - 1;
         vizitate[index_vizitate] = comp_conexa;
     }
     comp_conexa++;
     free(rezultat);
     } while(primul_nevizitat(vizitate, nr_noduri)!= -1);
 }

