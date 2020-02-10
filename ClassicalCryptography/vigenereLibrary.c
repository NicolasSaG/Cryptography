#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alphabet.h"
#include "vigenereLibrary.h"

char * encodeVigenere(char * plaintext, char * key){
	char * ciphertext  = malloc(sizeof(char) * (strlen(plaintext) + 1));
	int i = 0, j = 0;
	int valuePlainText, valueKey, result;
	int srtlenKey = strlen(key);
	while(plaintext[i] != '\0'){
		//recorrer el abecedario hasta encontrar la letra de plaintext y encontrar la de la llave,
		//y despues se suman y se calcula el mod del tam del alfabeto.
		valuePlainText = findValueBySymbol(plaintext[i]);
		valueKey = findValueBySymbol(key[j]); 
		if(valuePlainText == -1){
			ciphertext[i] = plaintext[i];
		}else{
			result = (valuePlainText + valueKey) % alphabetSize_GLOBAL;
			ciphertext [i] = findSymbolByValue(result);
			j++;
		}
		if(j % srtlenKey == 0)
			j = 0;
		i++;
	}
	ciphertext[i] = '\0';
	return ciphertext;
}

char * decodeVigenere(char * ciphertext, char * key){
	char * plaintext  = malloc(sizeof(char) * (strlen(ciphertext) + 1));
	int i = 0, j = 0;
	int valueCipherText, valueKey, result;
	int srtlenKey = strlen(key);
	while(ciphertext[i] != '\0'){
		//Encontrar valores de los caracteres de llave y texto cifrado
		valueCipherText = findValueBySymbol(ciphertext[i]);
		valueKey = findValueBySymbol(key[j]);

		if(valueCipherText == -1){
			plaintext[i] = ciphertext[i];
		}else{
			result = (valueCipherText - valueKey);
			if(result < 0)
				result = alphabetSize_GLOBAL + result;
			plaintext [i] = findSymbolByValue(result);
			j++;
		}
		if(j % srtlenKey == 0)
			j = 0;
		i++;
	}
	plaintext[i] = '\0';
	return plaintext;
}

char * generateVigenereRandomKey(){
	int i;
	time_t t;
	srand((unsigned) time(&t));
	int r = (rand() % alphabetSize_GLOBAL) + 1;
	char * key = malloc(sizeof(char) * r);
	for(i = 0; i < r; i++){
		key[i] = findSymbolByValue(rand()%alphabetSize_GLOBAL);
	}
	key[i] = '\0';
	return key;
}