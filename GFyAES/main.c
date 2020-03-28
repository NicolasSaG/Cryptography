#include "stdio.h"
#include "math.h"
#define GF3 11 	//1011
#define GF4 19 	//10011
#define GF5	37 	//100101
#define GF6	67 	//1000011
#define GF7	131 //10000011
#define GF8 283 //100011011

void setGFPow(int n);
void printGF(int n);
int multiplyGF(int a, int b, int pow);
int getBitValue(int data, int bit);
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

	printf("\t\t");
	for(i= 0; i < size; i++){
		printf("0x%.2x\t", i);
	}
	printf("\n");
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(j == 0){
				printf("0x%.2x\t", i);
			}
			//operaciones
			
			//impresion de multiplicacion i*j abajo

			printf("xff\t\t");
			//printf("xff\t\t", multiplyGF(i, j));
		}
		printf("\n");
	}
}


int multiplyGF(int a, int b, int pow){
	int result, max, i;

	max = pow(2, pow) - 1;

	if(getbitValue(b, pow-1) == 1){
		result = a << 		
	}else{
		result = 0;
	}
	for(i = 1; i < pow; i++){
		if(getbitValue(b, pow-i-1) == 1){
			result = result ^ (a << (pow-i-1));
		}
	}

	if(result > max){
		result = result ^ GF_Global;
	}
	//for 0 to pow
	//res = a << 2 si el bit mas sigfinicativo de b es 1
	//res = res xor a << 1 si el segundo bit mas significativo de b es 1
	//res = res xor a << 0 si el bit menos significativo de b es 1

	//si el bit de b es 0, no hacer nada
	//fin for
	//si res > 255 -> mayor a 11111111
		//hacer xor con el GF_global

	//result = a << 
	return result;
}

int getBitValue(int data, int bit){
	int i = 1 << bit;
	return !!(data & i);
}
/*
GF(2^3)
m(x) = x^3 + x + 1

000 xor m(x) = 000+1011

000*000 = 000 
000*001 = 0000 = 000
...
000*111 = 000


001*000 = 000 
001*001 = 001
001*010 = 010
001*011 = 001*010 xor 001*001 = 010 xor 001 = 011
001*100 = 100
...
001*111 = 001*100 xor 001*010 xor 001*001
			  = 100 xor 010 xor 001 = 111

010*000 = 000
010*001 = 010
010*010 = 100
...
010*100 = 1000 xor 1011 = 0011 = 011

generador de GF(2^3)
rep potencia		rep polyn	bin		hex
0								0					000		0x0
g^0							1						
g^1
g^2
g^3
g^4
g^5
g^6


tabla de Multiplicacion
		000	001	010	011	100	101	111
000 000 000 000 000 000 000 000
001
010
011
100
101
110
111


*/