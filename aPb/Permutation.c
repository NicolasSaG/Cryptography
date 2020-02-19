#include <stdio.h>

#include <stdlib.h>
#include "PermutationLibrary.h"
#include "Sort.h"

int main(){

	int prueba [5] = {4,3,1,5,2};
	int * x = malloc(sizeof(int) * 5);
	char h [6] = "hola ";
	int i;
	//x = inversePermutation(5, prueba);
	//printf("_____________ inversa guardada\n");
	for(i = 0; i< 5; i++){
		printf("%d, ", prueba[i]);
	}

	printf("\nmensaje con prueba a cifrar con no inversa: %s\n", h);

	permuteString(h, 5, prueba);
		printf("Permutada:%s|\n", h);

	return 0;
}