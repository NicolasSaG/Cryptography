#include <stdio.h>
#include <stdlib.h>
#include "DESLibrary.h"

//texto se lee, se guarda en variable, se le agrega terminador de linea y se pasa aqui
void operationModeEncryptCBC(unsigned char * plaintext, unsigned char iv){
	int i;
	unsigned char c;
	//primer bloque xor con iv
	c = plaintext[0];
	c = iv ^ c;
	c = encodeDESSimplified(c);
	plaintext[0] = c;
	for(i = 1; plaintext[i] != '\0'; i++){
		//cifrar y guardar c para el xor
		c = c ^ plaintext[i];
		c = encodeDESSimplified(c);
		plaintext[i] = c;
	}
}


void operationModeDecryptCBC(unsigned char * ciphertext, int length, unsigned char iv){
	int i;
	unsigned char m, aux;
	//primer bloque xor con iv
	m = ciphertext[0];
	aux = ciphertext[0];
	m = decodeDESSimplified(m);
	m = iv ^ m;

	ciphertext[0] = m;
	i = 1;
	while(i < length){
		m = decodeDESSimplified(ciphertext[i]);
		m = aux ^ m;
		aux = ciphertext[i];
		ciphertext[i] = m;
		i++;
	}
	ciphertext[i] = '\0';
}

unsigned char encodeDESSimplified(unsigned char m){
	unsigned char c;
	//aplicar a m permutaicon inicial
	int initialPermutation[8] = {2, 6, 3, 1, 4, 8, 5, 7};
	c = permutateDataBitLevel(8, initialPermutation, m);
	//ronda 1
	c = makeRound(c, 1);
	//girar r y l de c
	c = changeLtoR(c);
	//ronda 2
	c = makeRound(c, 2);
	//aplicar a c la permutacion inversa de 
	int iP[8] = {4, 1, 3, 5, 7, 2, 8, 6};
	c = permutateDataBitLevel(8, iP, c);	
	return c;
}

unsigned char decodeDESSimplified(unsigned char c){
	unsigned char m;
	//aplicar a m permutaicon inicial
	int initialPermutation[8] = {2, 6, 3, 1, 4, 8, 5, 7};
	m = permutateDataBitLevel(8, initialPermutation, c);
	//ronda 1
	m = makeRound(m, 2);
	//girar r y l de c
	m = changeLtoR(m);
	//ronda 2
	m = makeRound(m, 1);
	//aplicar a c la permutacion inversa de 
	int iP[8] = {4, 1, 3, 5, 7, 2, 8, 6};
	m = permutateDataBitLevel(8, iP, m);	
	return m;
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

int makeRound(unsigned char c, int round){
	unsigned char l, r, rExpandida, rXORk, sBoxResult;
	unsigned char result = 0;
	//seprarar en l y r
	l = c & 0xf0;
	l = l >> 4;
	r = c & 0xf;
	//aplicar Fk
	//se toman r se les aplica permutacion de expansion
  int expansionPermutation[8] = {4, 1, 2, 3, 2, 3, 4, 1};
	rExpandida = permutationExpansion(8, expansionPermutation, r, 4);
	//rExpandida xor k1

	if(round == 1){
		rXORk = rExpandida ^ k1;
	}else{
		rXORk = rExpandida ^ k2;
	}
	
	//de los 4 bits mas a la izquerda
	//renglon 1er y 4to bit
	int renglon = 0;
	renglon += getBitValue(rXORk, 7);
	renglon = renglon << 1;
	renglon += getBitValue(rXORk, 4);
	//columna 2do y 3er bit
	int columna = 0;
	columna += getBitValue(rXORk, 6);
	columna = columna << 1;
	columna += getBitValue(rXORk, 5);

	//buscar en s0
	int sBox0 [4][4]= {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}}; 
	sBoxResult = sBox0[renglon][columna];
	
	renglon = 0;
	renglon += getBitValue(rXORk, 3);
	renglon = renglon << 1;
	renglon += getBitValue(rXORk, 0);
	//columna 2do y 3er bit
	columna = 0;
	columna += getBitValue(rXORk, 2);
	columna = columna << 1;
	columna += getBitValue(rXORk, 1);

	//buscar en s1
	int sBox1 [4][4]= {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};
	sBoxResult = sBoxResult << 2;
	sBoxResult += sBox1[renglon][columna];
	
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

int permutationExpansion(int n, int permutation[n], int data, int sizeData){
	int i;
	int result = 0;
	int bitPosition, bitValue;
	for(i = 0; i < n; i++){
		bitPosition = permutation[i] - 1;
		//obtener bit
		bitValue = getBitValue(data, sizeData - 1 - bitPosition);
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

int generateRandomKey(){
	int i;
	time_t t;
	srand((unsigned) time(&t));
	int key = (rand() % 1024);
	return key;
}

int generateRandomIV(){
	int i;
	time_t t;
	srand((unsigned) time(&t));
	int iv = (rand() % 256);
	return iv;
}