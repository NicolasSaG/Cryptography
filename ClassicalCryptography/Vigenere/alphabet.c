#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alphabet.h"


char * addAlphabet(FILE * f){
	char c;
	int i = 0;
	alphabetSize_GLOBAL = alphabetSize(f);
	alphabet_GLOBAL = malloc(sizeof(char) * alphabetSize_GLOBAL);
	rewind(f);
	while((c = fgetc(f)) != EOF){
		alphabet_GLOBAL[i] = c;
		i++;
	}
}

int alphabetSize(FILE * f){
	int size = 0;
	char c;
	while((c = fgetc(f)) != EOF){
		size ++;
	}
	return size;
}

void printAlphabet(){
	int i;
	for (i = 0; i < alphabetSize_GLOBAL-1; i++){
		printf("%c, ", alphabet_GLOBAL[i]);
	}
	printf("%c\n", alphabet_GLOBAL[i]);
	printf("Longitud de alfabeto: %d\n", alphabetSize_GLOBAL);
}

int findValueBySymbol(char c){
	int position = 0;
	while( c != alphabet_GLOBAL[position]){
		position++;
	}
	if(position > alphabetSize_GLOBAL){
		//printf("Error: findValueBySymbol(%c) no se encuentra ese caracter en el alfabeto\n", c);
		//exit(0);
		return -1;
	}
	return position;
}

char findSymbolByValue(int c){
	return alphabet_GLOBAL[c];
}
