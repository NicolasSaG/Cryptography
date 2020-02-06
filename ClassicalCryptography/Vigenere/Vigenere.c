#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * alphabet_GLOBAL;
int alphabetSize_GLOBAL = 0;


int findValueBySymbol(char c){
	int position = 0;
	while( c != alphabet_GLOBAL[position]){
		position++;
	}
	if(position > alphabetSize_GLOBAL){
		printf("Error: findValueBySymbol(%c) no se encuentra ese caracter en el alfabeto\n", c);
		exit(0);
	}
	return position;
}

char findSymbolByValue(int c){
	return alphabet_GLOBAL[c];
}

//vigenere con solo minusculas de ascii
char * encodeVigenere(char * plaintext, char * key){
	char * ciphertext  = malloc(sizeof(char) * (strlen(plaintext) + 1));
	int i = 0, j = 0, result;
	int srtlenKey = strlen(key);
	while(plaintext[i] != '\0'){
		j =  i % srtlenKey;
		//recorrer el abecedario hasta encontrar la letra de plaintext y  encontrar la de la llave,
		//y despues se suman y se calcula el mod del tam del alfabeto.
		result = (findValueBySymbol(plaintext[i]) + findValueBySymbol(key[j])) % alphabetSize_GLOBAL;
		ciphertext [i] = findSymbolByValue(result);
		i++;
	}
	return ciphertext;
}

char * decodeVigenere(char * ciphertext, char * key){
	char * plaintext  = malloc(sizeof(char) * (strlen(ciphertext) + 1));
	int i = 0, j = 0, result;
	int srtlenKey = strlen(key);
	while(ciphertext[i] != '\0'){
		j =  i % srtlenKey;
		result = (findValueBySymbol(ciphertext[i]) - findValueBySymbol(key[j]));
		if(result < 0)
			result = alphabetSize_GLOBAL + result;
		plaintext [i] = findSymbolByValue(result);
		i++;
	}
	return plaintext;
}

int alphabetSize(FILE * f){
	int size = 0;
	char c;
	while((c = fgetc(f)) != EOF){
		size ++;
	}
	return size;
}0

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

void printAlphabet(){
	int i;
	for (i = 0; i < alphabetSize_GLOBAL-1; i++){
		printf("%c, ", alphabet_GLOBAL[i]);
	}
	printf("%c\n", alphabet_GLOBAL[i]);
	printf("Longitud de alfabeto: %d\n", alphabetSize_GLOBAL);
}

int main(){
	FILE * f = fopen("alphabet.txt", "r");
	addAlphabet(f);

	char * plaintext, * ciphertext, key [32];
	plaintext = malloc(sizeof(char) * 64);
	ciphertext = malloc(sizeof(char) * 64);
	
	printAlphabet();
	printf("Ingresa tu texto plano: ");
	gets(plaintext);
	printf("Ingresa tu llave: ");
	gets(key);
	printf("\nplaintext: |%s|\n", plaintext);
	printf("key: |%s|\n", key);
	printf("Encriptando...\n");
	ciphertext = encodeVigenere(plaintext, key);
	printf("Ciphertext: %s\n", ciphertext);
	
	memset(plaintext, 0, 64);

	printf("Desencriptando...\n");
	plaintext = decodeVigenere(ciphertext, key);
	printf("plaintext nuevo: %s\n", plaintext);
	return 0;
}