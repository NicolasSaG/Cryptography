#include <stdio.h>
#include "PermutationLibrary.h"

void inversePermutation( int n, int  permutation[][n]){
	int inverse [2][n];
	int i;
	int * j;
	//voltar valores de aux, 
	for(i = 0; i < n; i++){
		inverse[0][i] = permutation[1][i];
		inverse[1][i] = permutation[0][i];
	}

	//se guardan los varoles en el array original si se trabaja dentro de la funcion
	//permutation[0][1] = 5;

	printPermutation(n, inverse);
	//ordenar valores
	

	//return permutation;
}

void printPermutation(int n, int permutation[][n]){
	int i;
	for(i = 0; i < n; i++){
		printf("%d  %d\n", permutation[0][i], permutation[1][i]);
	}
}