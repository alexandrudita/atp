/*Rezolvare propusa de studentii de la Grupa 1015*/

void quicksort(float* x, int a, int b)
{
	if (a < b)
	{
		int lp = partitionare(x, a, b);
		quicksort(x, a, lp);
		quicksort(x, lp + 1, b);
	}
}

void shellsort(float*v, int n)
{
	for (int a = n / 2; a > 0; a = a / 2)
		for (int i = a; i < n; i++)
		{
			float temp = v[i];
			int j;
			for (j = i; j >= a && v[j - a] > temp; j = j - a) v[j] = v[j - a];
			v[j] = temp;
		}
}

int partitionare(float* x, int a, int b)
{
	float p = x[a];
	int leftwall = a;
	for (int i = a; i <= b; i++)
		if (x[i] < p)
		{
			float aux = x[i];
			x[i] = x[leftwall];
			x[leftwall++] = aux;
		}
	float aux = p;
	p = x[leftwall];
	x[leftwall] = aux;
	return leftwall;
}
void quicksort(float* x, int a, int b)
{
	if (a < b)
	{
		int lp = partitionare(x, a, b);
		quicksort(x, a, lp);
		quicksort(x, lp + 1, b);
	}
}

