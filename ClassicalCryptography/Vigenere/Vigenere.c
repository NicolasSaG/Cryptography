#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alphabet.h"
#include "vigenereLibrary.h"

//compile: gcc Vigenere.c alphabet.c vigenereLibrary.c -o Vigenere

int main(){
	FILE * f = fopen("alphabet.txt", "r");
	addAlphabet(f);

	char * plaintext, * ciphertext,* key2, key [32];
	plaintext = malloc(sizeof(char) * 64);
	ciphertext = malloc(sizeof(char) * 64);
	printAlphabet();
	printf("Ingresa tu texto plano: ");
	gets(plaintext);
	printf("Ingresa tu llave: ");
	gets(key);
	printf("\nplaintext: %s\n", plaintext);
	printf("key: %s\n", key);
	
	printf("Encriptando...\n");
	ciphertext = encodeVigenere(plaintext, key);
	printf("cipher: %s\n", ciphertext);
	
	plaintext = malloc(sizeof(char) * strlen(plaintext));
	printf("Desencriptando...\n");
	plaintext = decodeVigenere(ciphertext, key);
	printf("plaintext nuevo: %s\n", plaintext);
	
	key2 = generateRandomKey();
	printf("Key random:|%s|\n", key2);

	free(key2);
	free(plaintext);
	free(ciphertext);
	return 0;
}