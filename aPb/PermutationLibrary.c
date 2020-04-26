#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sort.h"
#include "PermutationLibrary.h"

int * inversePermutation(int n, int  permutation[n]){
	int * inverse = malloc(sizeof(int)*n);
	int inverseAux[n][2];
	int i;
	int * j;
	 
	//identificar valores
	for(i = 0; i < n; i++){
		inverseAux[i][0] = i;
		inverseAux[i][1] = permutation[i];
	}
	//ordenar los de arriba respecto a la fila de abajo
	printPermutation(n, inverseAux);
	mergeBidimentionalSort(n, inverseAux, 0, n-1);
	printPermutation(n, inverseAux);
	//ordenar valores
	for(i = 0; i < n; i++)
		inverse[i] = inverseAux[i][0] + 1; 
	return inverse;
}


void permuteteBits(char * string, int n, int permutation[n]){
	/*
	printf("Permutada:%s|\n", h);
	for (i = 0; i < 8; i++) {
      printf("%d", !!((65 << i) & 0x80));
  }
  printf("\n|%d|\n", ((65 << 1) & 0x80));
	*/
	return;
}

void permuteString(char * string, int n, int permutation[n]){
	int i, j;
	int sizeString;
	sizeString = strlen(string);


	if(sizeString % n != 0){ 	//con padding
		for(j = 0; j < sizeString - (sizeString % n); j += n){
			char * auxString = malloc(sizeof(char) * n);
			memcpy(auxString + 0, string + j, n);
		 	char c;
		 	for(i = 0; i < n; i++){
				string[i+j] = auxString[permutation[i]-1];
			}
			free(auxString);
		}
		//padding
		char * auxString = malloc(sizeof(char) * n);
		memset(auxString, '|', n);
		memcpy(auxString + 0, string + j, sizeString%n);
		char c;
		for(i = 0; i < n; i++){
			string[i+j] = auxString[permutation[i]-1];
		}
		free(auxString);
	}else{
		for(j = 0; j < sizeString; j += n){
			char * auxString = malloc(sizeof(char) * n);
			memcpy(auxString + 0, string + j, n);
		 	char c;
		 	for(i = 0; i < n; i++){
				string[i+j] = auxString[permutation[i]-1];
			}
			free(auxString);
		}	
	}
}

void printPermutation(int n, int permutation[n][2]){
	int i;
	for(i = 0; i < n; i++){
		printf("%d ", permutation[i][0] +1);
	}
	printf("\n");
	for(i = 0; i < n; i++){
		printf("%d ", permutation[i][1]);
	}
	printf("\n");
}