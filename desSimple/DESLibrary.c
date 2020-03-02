#include <stdio.h>
#include "DESLibrary.h"

void findKn(int k, int n, int permutation[n]){
	//permutar a k
	int kp, k1, k2;
	kp = permutateDataBitLevel(n, permutation, k);
	kp = circularOneLeftShift(kp);

	//permutacion de compresion
	//crear permutacion de compresion
	int compresion[8] = {7, 8, 6, 10, 9, 4, 3, 5};
	//generar k1
	k1 = permutationCompression(8, compresion, kp, 2);
	
	//corrimiento circular de 2 bits a izquierda
	kp = circularOneLeftShift(kp);
	kp = circularOneLeftShift(kp);

	//generar k2
	k2 = permutationCompression(8, compresion, kp, 2);
}

int circularOneLeftShift(int k){
	int kl, kr; //division de bits
	int kfinal = 0;
	int bitAux;
	//separar k en 2 partes de 5 bits
	kl = k & 0x3e0; //5 bits mas significativos
	kr = k & 0x1f; //5 bits menos significativos

	//1 corrimiento circular a la izquierda
	bitAux = getBitValue(kl, 5);
	kl = kl << 1;
	kl += bitAux;
	bitAux = getBitValue(kr, 5);
	kr = kr << 1;
	kr += bitAux;

	//concatenar
	kfinal += kl << 5;
	kfinal += kr;
	return kfinal;
}

int permutationCompression(int n, int permutation[n], int data, int pos){
	int i;
	int result = 0;
	int bitPosition, bitValue;
	for(i = pos; i < n; i++){
		bitPosition = permutation[i-pos] - 1;
		//obtener bit
		bitValue = getBitValue(data, n - 1 - i);
		result += (bitValue << n - 1 - bitPosition);
	}
	return result;
}

int permutateDataBitLevel(int n, int permutation[n], int data){
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
