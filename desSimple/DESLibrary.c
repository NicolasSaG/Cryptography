#include <stdio.h>
#include "DESLibrary.h"

/*
void generateKn(int n, int kActual[n], int kNext[n]){

}

void generatePermutation(int n, int permutation[n]){
		int i;
		int aux;

    for (i = 0; i <= n-2; i++) {
    		//generate random
    		int j = 0;
    		//swap permutation i j
    		aux = permutation[i];
    		permutation[i] = permutation[j];
    		permutation[j] = aux;
    }
}


void permutateBits(int n, int permutation[n], int data){
	int i; 
	int result = 0;
	for(i = n; n > 0; i--){
		//obtenemos bit de permutacion
		getBit(data, permutation[i]);
		result += getBit(,);
	}
}*/
int permutateCharBitLevel(int n, int permutation[n], char data){
	int i;
	int result = 0;
	int bitPosition, bitValue;
	for(i = 0; i < n; i++){
		bitPosition = permutation[i] - 1;
		//obtener bit
		bitValue = getBitValue(data, n - 1 - i);
		result += (bitValue << n - 1 - bitPosition);
	}
	return result;
}

int getBitValue(int data, int bit){
	int i = 1 << bit;
	return !!(data & i);
}
