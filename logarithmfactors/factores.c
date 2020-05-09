#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TADPilaDin.h"

#include <openssl/bn.h>
// pila * factorizar(double n){
// 	pila * stack;
// 	elemento e;
// 	double i;
// 	stack = malloc(sizeof(pila));
// 	Initialize(stack);
// 	double zero = 0.0;
// 	//quitamos los posibles pares del for
// 	//n%2
// 	while(fmod(n, 2.0) == zero){
// 		BIGNUM * b = BN_new();
// 		e->b = 2;
// 		Push(stack, e);
// 		n /= 2;
// 	}

// 	//Recorremos los impares de 3 a n siempre y cuando el cuadrado de i sea menor igual
// 	//a n.
// 	for(i = 3; i * i <= n; i +=2){
// 		//n%i
// 		while(fmod(n, i) == zero){//comprobamos que ese mismo numero no sea factor otra vez
// 			e.n = i;
// 			Push(stack, e);
// 			n /= i;
// 		}
// 	}

// 	if(n > 1){//si i*i ya paso a n, y n es mayor a 1 tenemos otro factor ahi primo
// 		e.n = n;
// 		Push(stack, e);
// 	}
// 	return stack;
// }

int main(int argc, char const *argv[]){
	pila * p;
	char num [19] = "250000009000000081";
	BIGNUM * b = BN_new();
	BN_dec2bn(b, num);
	int BN_print(0, b);
	//p = factorizar(250000009000000081);
	printf("factores:\n");
	//while(p->tope != NULL){
	//	elemento e = Pop(p);
	//	printf("%.2lf\n", e.n);
	//}
	return 0;
}