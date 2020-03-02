#include <stdio.h>
#include "DESLibrary.h"

int main(int argc, char const *argv[]){
	int a = 96, i, aP;
	int permutation[8] = {2, 4, 6, 8, 1, 3, 5, 7};

	printf("a=%d\n", a);
	for(i = 7; i >= 0; i--)
		printf("%d", getBitValue(a, i));

	aP = permutateCharBitLevel(8, permutation, a);
	printf("\na permutada= %d\n", aP);
	for(i = 7; i >= 0; i--)
		printf("%d", getBitValue(aP, i));
	return 0;
}