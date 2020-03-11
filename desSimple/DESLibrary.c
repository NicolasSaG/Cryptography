#include <stdio.h>
#include "DESLibrary.h"

unsigned char encodeDESSimplified(unsigned char m, int n){
	unsigned char c;
	//aplicar a m permutaicon inicial
	int initialPermutation[8] = {2, 6, 3, 1, 4, 8, 5, 7};
	c = permutateDataBitLevel(n, initialPermutation, m);

	//ronda 1
	c = makeRound(c);
	//girar r y l de c
	c = changeLtoR(c);


	//ronda 2
	c = makeRound(c);
	//aplicar a c la permutacion inversa de initialPermutation
	
	//c = permutateDataBitLevel(n, inverseInitialPermutation, c);	
	
	return c;
}

unsigned char changeLtoR(unsigned char c){
	int result;
	//obtener l
	result = c & 0xf0;
	//correrlos a la derecha
	result = result >> 4;
	//obtener los primeros 4 bits y correrlos a la izquierda
	//sumar con el resultado
	result += ((c & 0xf) << 4);
	return result;
}

int makeRound(unsigned char c){
	unsigned char l, r, rExpandida, rXORk, sBoxResult;
	unsigned char result;
	//seprarar en l y r
	l = c & 0xf0;
	r = c & 0xf;

	//aplicar Fk

	//se toman r se les aplica permutacion de expansion
	int expansionPermutation[8] = {4, 1, 2, 3, 2, 3, 4, 1};
	rExpandida = permutateDataBitLevel(8, expansionPermutation, r);
	//rExpandida xor k1
	rXORk = rExpandida ^ k1;

	//buscar en s0

	//buscar en s1
	sBoxResult = 15;

	//permutamos los datos encontrados en las tablas
	int p4[4] = {2, 4, 3, 1};
	sBoxResult = permutateDataBitLevel(4, p4, sBoxResult);

	//xor con l
	l = sBoxResult ^ l;
	result = l << 4;
	result += r;
	return result;
}

void findKn(int k, int n, int permutation[n]){
	//permutar a k
	int kp;
	int i;
	kp = permutateDataBitLevel(n, permutation, k);
	kp = circularOneLeftShift(kp);

	//permutacion de compresion
	//crear permutacion de compresion
	int compresion[8] = {6, 3, 7, 4, 8, 5, 10, 9};
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
	kl = 0x3e0 & k; //5 bits mas significativos
	kr = 0x1f & k; //5 bits menos significativos
	//1 corrimiento circular a la izquierda
	int i;
	//regresar kl a tam de 5 bits
	kl = kl >> 5;
	bitAux = getBitValue(kl, 4);
	kl = kl << 1;
	kl = 0x1f & kl;
	kl += bitAux;
	bitAux = getBitValue(kr, 4);
	kr = kr << 1;
	kr = 0x1f & kr;
	kr += bitAux;

	//concatenar
	kfinal += kl << 5;
	kfinal += kr;
	return kfinal;
}

int permutationCompression(int n, int permutation[n], int data, int pos){
	int i,j;
	int result = 0;
	int bitPosition, bitValue;
	for(i = 0; i < n; i++){
		bitPosition = permutation[i] - 1;
		//obtener bit
		bitValue = getBitValue(data, n + pos - 1 - bitPosition);
		result += (bitValue << (n - 1 - i));
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
		bitValue = getBitValue(data, n - 1 - bitPosition);
		result += (bitValue << (n - 1 - i));
	}
	return result;
}

int getBitValue(int data, int bit){
	int i = 1 << bit;
	return !!(data & i);
}


void printBinary(int n, int size){
	int i;
	for(i=0; i< size; i++)
		printf("%d ", getBitValue(n, size-1-i));
	printf("\n");
}