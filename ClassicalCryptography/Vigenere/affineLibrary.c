#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alphabet.h"
#include "affineLibrary.h"


int validateAffineKey(int a, int n){
	//la llave es valida si mcd(a, n) = 1
	if(gcd(a, n) == 1){ //son coprimos
		return 1;
	}else{
		return -1;
	}
}

//ci = (a*mi + b)modn
char * encodeAffine(char * plaintext, int a, int b){
	char * ciphertext  = malloc(sizeof(char) * (strlen(plaintext) + 1));
	int i = 0;
	int valuePlainText, result;

	while(plaintext[i] != '\0'){
		//recorrer el abecedario hasta encontrar la letra de plaintext multiplicar el valor por a y sumarle b
		//despues se le hace mod por el tam del alfabeto
		valuePlainText = findValueBySymbol(plaintext[i]);
		if(valuePlainText == -1){
			ciphertext[i] = plaintext[i];
		}else{
			result = ((valuePlainText*a) + b) % alphabetSize_GLOBAL;
			ciphertext [i] = findSymbolByValue(result);
		}
		i++;
	}
	return ciphertext;
}
//mi = a^-1(ci - b)modn
char * decodeAffine(char * ciphertext, int a, int b){
	char * plaintext  = malloc(sizeof(char) * (strlen(ciphertext) + 1));
	int i = 0;
	int valueCipherText, result;
	int inverse = inverseModularAritmethic(a, alphabetSize_GLOBAL);
	while(ciphertext[i] != '\0'){
		//recorrer el abecedario hasta encontrar la letra de plaintext multiplicar el valor por a y sumarle b
		//despues se le hace mod por el tam del alfabeto
		valueCipherText = findValueBySymbol(ciphertext[i]);
		if(valueCipherText == -1){
			plaintext[i] = ciphertext[i];
		}else{
			//aprovechando la propiedad de aritmetica modular
			//(a*b)modn = (amodn *bmodn)modn
			result = findValueBySymbol(ciphertext[i]) - b;
			if(result < 0)
				result = alphabetSize_GLOBAL + result;

			result = result % alphabetSize_GLOBAL;
			result = (result * inverse) % alphabetSize_GLOBAL;
			plaintext [i] = findSymbolByValue(result);

		}
		i++;
	}
	return plaintext;
}

int generateAffineARandomKey(int n){
	int a = 0, i;
	time_t t;
	srand((unsigned) time(&t));
	//error checar a no sale coprima de n
	while(1){
		a = rand() % n;
		if(gcd(a, n) == 1 && a != 0){
			break;
		}
	}
	return a;
}

int generateAffineBRandomKey(int n){
	time_t t;
	srand((unsigned) time(&t));
	int b = rand() % n;
	return b; 
}

int inverseModularAritmethic(int a, int n){
	int quotient, aux;
	//int remainder, previousRemainder = a;
	int auxInverse = 0; int inverse = 1;
  int t = 1; int old_t = 0;
  int result = n; int previousResult = a;
	
  //printf("s=%d, t=%d, result=%d, olds=%d, oldt=%d, oldresult=%d,\n", s,t,result, inverse, old_t, previousResult);
	while(result > 0){ // result tambien nos indica si al final es igual a 1 que a y n son coprimos
		quotient = previousResult / result;
		
		aux = result;
		result = previousResult - quotient*result;
		previousResult = aux;

		aux = auxInverse;
		auxInverse = inverse - (quotient * auxInverse);
		inverse = aux;

		aux = t;
		t = old_t - (quotient * t);
		old_t = aux;
		//printf("cociente:%d, s=%d, t=%d, result=%d, olds=%d, oldt=%d, oldresult=%d,\n", quotient, s,t,result, inverse, old_t, previousResult);
	}

	if(inverse < 0)
		inverse = n + inverse;

	return inverse;
}

int gcd(int a, int b){
	if(a < b){
		return gcd(b, a);
	}
	else if(a %b == 0){
		return b;
	}else{
		return gcd(b, a%b);
	}
}