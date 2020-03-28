#include "stdio.h"
#include "math.h"
#define GF3 11 	//1011
#define GF4 19 	//10011
#define GF5	37 	//100101
#define GF6	67 	//1000011
#define GF7	131 //10000011
#define GF8 283 //100011011

//checar error con el 4to cuadrante de las tablas
//			]
//			]
// ===========
//			} aqui
//			}
//multiplicaciones por ejemplo 111*111

void setGFPow(int n);
void printGF(int n);
int getBitValue(int data, int bit);

int multiplyGF(int a, int b, int pot);
void printBinary(int n, int size);
int GF_Global;

int main(int argc, char const *argv[]){
	printf("Tabla de Multiplicacion de 2^3\n");
	int gfPow = argv[1][0]-'0';
	setGFPow(gfPow);
	printf("Polinomio irreducible: 0x%.2x\n", GF_Global);
	printGF(gfPow);
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

void printGF(int n){
	int i, j;
	int size;
	size = pow(2, n);

	//printf("\t\t");
	for(i= 0; i < size; i++){
		//printf("0x%.2x\t", i);
	}
	//printf("\n");
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(j == 0){
				//printf("0x%.2x\t", i);
			}
			//operaciones
			
			//impresion de multiplicacion i*j abajo
			//printBinary(multiplyGF(i, j, n), n);
			//printf("\t\t");
			multiplyGF(i, j, n);
			printf("\n");
			//printf("x%.2x\t\t", multiplyGF(i, j, n));
		}
		printf("\n");
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
	printBinary(result, 8);
	//10000000 << 10000000 = 100000000000000
	//x^7 * x^7 = x^14 = x^8*x^6 = x^pot*x^((pot*2-2)-pot)
	//100000000000000 (15 bits) and 11111111111111 (14bits)
	//= 00 0000 0000 0000
	// aux = 
	//el maximo que se podria recorrer es de pot*2 - 1

	if(result > max && result < (max+1)*2-1){
		for(i = 0; i < (pot*2-1)-pot; i++){ // recorrer los que se salgan de los n bits con un carry
			if(getBitValue(result, pot*2-1-i) == 1){
				//100 0000 0000 0000
				//restamos ese bit
				//res -= 1 << pot*2-1-i
				//aux = 1 << pot*2-1-i
				//
			}
		}
		printf("entre\n");
		result = result ^ GF_Global;
	}
	return result;
}

void printBinary(int n, int size){
	int i;
	for(i=0; i< size; i++)
		printf("%d", getBitValue(n, size-1-i));
	//printf("\n");
}