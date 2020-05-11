#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TADPilaDin.h"

#include <openssl/bn.h>
#include <openssl/bio.h>

//gcc factores.c TADPilaDin.c  -lssl -lcrypto -o factores

pila * factorizar(BIGNUM * n);
void printBN(BIGNUM * b);
BIGNUM * str2bn(char * s);

int main(int argc, char const *argv[]){
	pila * p;
	char num [22] = "64";
	BIO *out;
	out = BIO_new_fp(stdout, BIO_NOCLOSE);
	BIGNUM * b = str2bn(num);
	
	//convertir bignum a cadena

	printBN(b);
	printf("\n");

	//imprime en hexadecimal el valor del BIGNUM
	BN_print(out, b);
	//BN_free(b);
	BIO_free(out);
	printf("\n");
	

	p = factorizar(b);
	BN_free(b);
	printf("factores:\n");
	/*
	
	10006200817
	250035001189
	250000009000000081
	*/
	
	while(p->tope != NULL){
		elemento e = Pop(p);
		printBN(e.b);
		printf("\n");
	}
	return 0;
}


pila * factorizar(BIGNUM * n){
	pila * stack;
	elemento e;
	char numString1[2] = "1";
	char numString2[2] = "2";
	char numString3[2] = "3";

	BIGNUM * one = str2bn(numString1);
	BIGNUM * two = str2bn(numString2);
	BIGNUM * aux = BN_new();
	stack = malloc(sizeof(pila));
	Initialize(stack);
	//quitamos los posibles pares del for
	//n%2
	while(1){
		//modulo
		BN_mod(aux, n, two, BN_CTX_new());
		if(BN_is_zero(aux)){
			BIGNUM * b = str2bn(numString2);
			e.b = b;
			Push(stack, e);
			BN_div(n, NULL, n, two, BN_CTX_new());
		}else{
			break;
		}
	}
	
	//Recorremos los impares de 3 a n siempre y cuando el cuadrado de i sea menor igual
	//a n.
	BIGNUM * i = str2bn(numString3);
	BIGNUM * ii = BN_new();
	//inicializar valores
	BN_mul(ii, i, i, BN_CTX_new());
	
	/*
	while(BN_cmp(ii, n) <= 0){
		
		while(1){
			//modulo, 
			BN_nnmod(n, n, i, BN_CTX_new());
			if(BN_is_zero(n)){
				//BIGNUM * b = BN_new();
				e.b = i;
				Push(stack, e);
				BN_div(n, NULL, n, i, BN_CTX_new());
			}else{
				break;
			}
		}
		//i+=2
		BN_add(i, i, two);
	}

	if(BN_cmp(n, one)){
		e.b = n;
		Push(stack, e);
	}
	*/
	return stack;
}


//imprimir en decimal un bignum
void printBN(BIGNUM * b){
	char * s;
	s = BN_bn2dec(b);
	printf("%s", s);
}

BIGNUM * str2bn(char * s){
	BIGNUM * b;
	b = BN_new();
	BN_dec2bn(&b, s);
	return b;
}
