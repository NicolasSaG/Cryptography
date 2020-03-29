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
int getBitValue(int data, int bit);

int multiplyGF(int a, int b, int pot);
void printBinary(int n, int size);
int GF_Global;

int main(int argc, char const *argv[]){
	printf("Tabla de Multiplicacion de 2^%s\n", argv[1]);
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

	printf("\t\t\t");
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
			//printBinary(multiplyGF(i, j, n), n);
			//printf("\t\t");
			//multiplyGF(i, j, n);
			//printf("\n");
			printf("0x%.2x\t", multiplyGF(i, j, n));
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
	//printBinary(result, 8);

	int carryIndex;
	carryIndex = pot * 2 - 2;
	//11111 *10000 = 111110000
	// printf("Valor: ");
	// printBinary(result, pot*2-1);
	// printf("\n");
	while(result > max){
		if(carryIndex == pot - 1)
			break;
		
		if(getBitValue(result, carryIndex) == 1){ // hay carry
			int aux, corrAux;
			//printf("carruy Index= %d\n", carryIndex);
			aux = 1 << carryIndex;
			//printf("\nEncontrado carry en %d:", carryIndex);
			//printBinary(aux, pot*2-1);
			//printf("\n");
			// obtener bit carry
			//obtener corrimiento x^5 = x^3*x^2 (obtener el 2)
			corrAux = carryIndex - pot;
			aux = 1 << carryIndex - corrAux;
			//printf("Es lo mismo que ");
			//printBinary(aux, pot*2-1);
			//printf(" * ");
			//printBinary(1<<corrAux, pot*2-1);
			//printf("\n");
			//aux es lo mismo que (1 << pot ) *(1<< corrAux)
			//printf("carruy Index= %d\n", carryIndex);
			//printf("%d\n", carryIndex-pot); 
			//printBinary(aux, pot*2);
			// printf("A ");
			// printBinary(aux, pot*2-1);
			// printf(" xor ");
			// printBinary(GF_Global, pot*2-1);
			// printf("\n");
			aux = aux ^ GF_Global; //hacerle modulo con el 
			// printf("= ");
			// printBinary(aux, pot*2-1);
			// printf("\n");
			// //aux multiplicarlo por por
			aux = aux << corrAux;
			// printf("Multiplicamos aux por la otra potencia:\naux = ");

			// printBinary(aux, pot*2-1);
			// printf("\n");
			// //result = result ^
			//printf("despues de xor irreducible: "); 
			//printBinary(aux, pot*2);
			//restarle a result 1 << carryIndex y luego xor con aux

			// printf("A result se le resta el bit que es carry: ");
			// printBinary(result, pot*2-1);
			// printf(" - ");
			
			int resto;
			resto = 1 << carryIndex;
			// printBinary(resto, pot*2-1);
			// printf(" = ");
			result = result ^ resto;
			// printBinary(result, pot*2-1);
			// printf("\nresult se hace xor con aux");
			// printf("\naux   = ");
			// printBinary(aux, pot*2-1);
			// printf("\nresult= ");
			// printBinary(result, pot*2-1);
			// printf("\n");
			result = result ^ aux;
			// printBinary(result, 2*pot-1);
			// printf("\n");
			carryIndex--;
		}else{
			carryIndex--;
		}
	}
	//printf("\n");
	// if(result > max){ // hay al menos un carry
	// 	//maximo posible carry esta en 2*pot-2

	// 	printf("Hay al menos un carry carry\n");
	// 	printBinary(result, 5);
	// 	printf(" xor ");
	// 	printBinary(GF_Global, 5);
	// 	result = result ^ GF_Global;
	// 	printf(" = ");
	// 	printBinary(result,5);
	// }
	return result;
}

void printBinary(int n, int size){
	int i;
	for(i=0; i< size; i++)
		printf("%d", getBitValue(n, size-1-i));
	//printf("\n");
}