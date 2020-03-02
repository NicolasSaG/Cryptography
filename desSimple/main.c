#include <stdio.h>
#include "DESLibrary.h"

int main(int argc, char const *argv[]){
	int a = 228, i, aP;
	int permutation[8] = {7, 8, 6, 4, 3, 5};

	printf("a=%d\n", a);
	for(i = 7; i >= 0; i--)
		printf("%d", getBitValue(a, i));

	aP = permutationCompression(8, permutation, a, 2);
	printf("\na permutada= %d\n", aP);
	for(i = 7; i >= 0; i--)
		printf("%d", getBitValue(aP, i));
	return 0;
}