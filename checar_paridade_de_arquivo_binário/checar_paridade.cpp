#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <time.h>

int* gerar_vetor_binario(int n);

int* gerar_vetor_binario(int n)
{
	int *vetor, num, i;
	vetor = (int*)malloc(sizeof(int) * n);
	if (vetor == NULL)
	{
		printf("Não foi possível alocar o vetor\n");
		char op = _getch();
		exit(1);
	}

	for (i = 0; i < n; i++)
	{
		num = rand() % 2;
		vetor[i] = num;
	}
	return vetor;
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	int n = 10000000;
	int i, n0 = 0, n1 = 0;
	int* v = gerar_vetor_binario(n);
	//Iniciando MPI
	MPI_Init(NULL, NULL);
	int ncpus;
	MPI_Comm_size(MPI_COMM_WORLD, &ncpus);
	int meu_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);

	for (i = meu_rank; i < n; i = i + ncpus)
	{
		if (v[i] == 0) n0++;
		else if (v[i] == 1) n1++;
	}
	MPI_Finalize();
	printf("Número de 0 existentes no vetor: %d\n", n0);
	printf("Número de 1 existentes no vetor: %d\n\n", n1);
	if (n1 % 2 != 0)
	{
		printf("Adicionando o número 1 ao vetor para tornar par a quantidade existente de dígitos 1\n");
		for (i = 0; i < n; i++)
		{
			if (v[i] != 1)
			{
				v[i] = 1;
				i = n;
			}
		}
		printf("Adicionado. A quantidade de dígitos 1 existente no vetor agora é par\n");
	}
	free(v);
	char op = _getch();
}
