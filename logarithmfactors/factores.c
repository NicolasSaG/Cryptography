#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TADPilaDin.h"

#include <openssl/bn.h>
pila * factorizar(BIGNUM * n){
	pila * stack;
	elemento e;

	char numString[2] = "2";
	char numString3[2] = "3";
	BIGNUM * two = BN_new();
	BN_dec2bn(two, numString);

	double i;
	stack = malloc(sizeof(pila));
	Initialize(stack);

	//quitamos los posibles pares del for
	//n%2
	while(1){
		//modulo, 
		BN_nnmod(n, n, two, BN_CTX_new());
		if(BN_is_zero(n)){
			BIGNUM * b = BN_new();
			BN_dec2bn(b, numString);
			e->b = b;
			Push(stack, e);
			BN_div(n, NULL, n, two, BN_CTX_new());
		}else{
			break;
		}
	}

	//Recorremos los impares de 3 a n siempre y cuando el cuadrado de i sea menor igual
	//a n.
	BIGNUM * i = BN_new();
	BIGNUM * ii = BN_new();
	
	//inicializar valores
	BN_dec2bn(i, numString3);
	BN_mul(ii, i, i, BN_CTX_new());
	while(BN_cmp(ii, n) <= 0){
		ii <= n
		while(){

		}
		//i+=2
		BN_add(i, i, two);
	}
	for(i = 3; i * i <= n; i +=2){
		//n%i
		while(fmod(n, i) == zero){//comprobamos que ese mismo numero no sea factor otra vez
			e.n = i;
			Push(stack, e);
			n /= i;
		}
	}

	if(n > 1){//si i*i ya paso a n, y n es mayor a 1 tenemos otro factor ahi primo
		e.n = n;
		Push(stack, e);
	}
	return stack;
}

int main(int argc, char const *argv[]){
	pila * p;
	char num [19] = "250000009000000081";
	BIGNUM * b = BN_new();
	BN_dec2bn(b, num);
	p = factorizar(b);
	printf("factores:\n");
	/*
	100160063
	10006200817
	250035001189
	250000009000000081
	*/

	while(p->tope != NULL){
		elemento e = Pop(p);
		char  * factor = malloc(sizeof(char) * 20);
		factor = BN_bn2dec(e->b);
		printf("%s\n", factor);
		free(num);
	}
	return 0;
}