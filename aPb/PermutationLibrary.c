#include <stdio.h>
#include <stdlib.h>
#include "Sort.h"
#include "PermutationLibrary.h"


int * inversePermutation(int n, int  permutation[n]){
	int * inverse = malloc(sizeof(int)*n);
	int inverseAux[n][2];
	int i;
	int * j;
	 
	//identificar valores
	for(i = 0; i < n; i++){
		inverseAux[i][0] = i;
		inverseAux[i][1] = permutation[i];
	}
	// 0 1 2 3
	// 2 0 3 1
	//ordenar los de arriba respecto a la fila de abajo
	printPermutation(n, inverseAux);
	mergeBidimentionalSort(n, inverseAux, 0, n-1);
	printPermutation(n, inverseAux);
	//ordenar valores
	for(i = 0; i < n; i++)
		inverse[i] = inverseAux[i][0]; 
	return inverse;
}

void printPermutation(int n, int permutation[n][2]){
	int i;
	for(i = 0; i < n; i++){
		printf("%d ", permutation[i][0] +1);
	}
	printf("\n");
	for(i = 0; i < n; i++){
		printf("%d ", permutation[i][1]);
	}
	printf("\n");
}