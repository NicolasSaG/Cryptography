#include "stdio.h"
#include "math.h"
#define GF3 11 	//1011
#define GF4 19 	//10011
#define GF5	37 	//100101
#define GF6	67 	//1000011
#define GF7	131 //10000011
#define GF8 283 //100011011

void setGFPow(int n);
void printGFHex(int n);
void printGFPolynomial(int n);
int getBitValue(int data, int bit);

int multiplyGF(int a, int b, int pot);
void printBinary(int n, int size);
void representAsPolynomial(int data, int pot, FILE * f);
int GF_Global;

//compile: gcc main.c -o main
//execute: main power 0|1

//power: numero entre 3 y 8
//0: representacion hexadecimal
//1: representacion polinomios

int main(int argc, char const *argv[]){
	printf("Tabla de Multiplicacion de 2^%s\n", argv[1]);
	int gfPow = argv[1][0]-'0';
	setGFPow(gfPow);
	printf("Polinomio irreducible: 0x%.2x\n", GF_Global);
	if(argv[2][0] == '0'){ //representar como hex
		printGFHex(gfPow);
	}else{ // representar como polinomios
		printGFPolynomial(gfPow);
	}
	return 0;
}

void setGFPow(int n){
	switch(n){
		case 3:
			GF_Global = GF3;
		break;
		case 4:
			GF_Global = GF4;
		break;
		case 5:
			GF_Global = GF5;
		break;
		case 6:
			GF_Global = GF6;
		break;
		case 7:
			GF_Global = GF7;
		break;
		case 8:
			GF_Global = GF8;
		break;
		default:
			GF_Global = 0;
		break;
	}
}

void printGFPolynomial(int n){
	int i, j;
	int size;
	size = pow(2, n);
	FILE * f = fopen("MTPolynomial.txt", "w");

	fprintf(f, "\t\t\t");
	for(i= 0; i < size; i++){
		fprintf(f, "0x%.2x\t", i);
	}
	fprintf(f, "\n");
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(j == 0){
				fprintf(f, "0x%.2x\t", i);
			}
			representAsPolynomial(multiplyGF(i, j, n), n, f);
			fprintf(f,"\t| ");
		}
		fprintf(f, "\n");
	}
}

void printGFHex(int n){
	int i, j;
	int size;
	size = pow(2, n);
	FILE * f = fopen("MTHexadecimal.txt", "w");
	fprintf(f, "\t\t\t");
	for(i= 0; i < size; i++){
		fprintf(f, "0x%.2x\t", i);
	}
	fprintf(f,"\n");
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(j == 0){
				fprintf(f, "0x%.2x\t", i);
			}
			fprintf(f,"0x%.2x\t", multiplyGF(i, j, n));
		}
		fprintf(f,"\n");
	}
}

int getBitValue(int data, int bit){
	int i = 1 << bit;
	return !!(data & i);
}

int multiplyGF(int a, int b, int pot){
	int result, max, i;
	max = pow(2, pot) - 1;
	result = 0;
	for(i = 0; i < pot; i++){
		if(getBitValue(b, pot-i-1) == 1){
			result = result ^ (a << (pot-i-1));
		}
	}
	
	int carryIndex;
	carryIndex = pot * 2 - 2;
	while(result > max){
		if(carryIndex == pot - 1)
			break;	
		if(getBitValue(result, carryIndex) == 1){ // hay carry
			int aux, corrAux;
			aux = 1 << carryIndex;
			corrAux = carryIndex - pot;
			aux = 1 << carryIndex - corrAux;

			aux = aux ^ GF_Global; //hacerle modulo con el irreducible al carry
			aux = aux << corrAux;
			int resto;
			resto = 1 << carryIndex;
			result = result ^ resto;
			result = result ^ aux;
			carryIndex--;
		}else{
			carryIndex--;
		}
	}
	return result;
}

void printBinary(int n, int size){
	int i;
	for(i=0; i< size; i++)
		printf("%d", getBitValue(n, size-1-i));
}

void representAsPolynomial(int data, int pot, FILE * f){
	int i;
	if(data == 0){
		fprintf(f, "0");
	}else{
		for(i = 0; i < pot-1; i++){
			if(getBitValue(data, pot - i-1) == 1){
				fprintf(f, "x^%d +", pot - i-1);	
			}
		}
		if(getBitValue(data, 0) == 1){
			fprintf(f, " 1");	
		}	
	}	
}