#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TADPilaDin.h"
#include "basicos.h"

// Alumno: Sanchez Garcia Francisco Nicolas

int primo(double n){
	double i;
	double zero = 0.0;
	if(n <= 1){
		return 0;
	}
	for(i = 2; i < n; i++){
		//si n es divisible por otro numero entre 2 y n-1 entonces 
		//n no es primo por definicion
		if(fmod(n, i) == zero){
			return 0;
		}
	}
	return 1;
}

//Aprovechamos que ningun factor primo de un numero n puede ser mayor a su raiz
//Esto nos permite comprobar factores entre 2 <= i <= sqrt(n)
pila * factorizar(long long n){
	pila * stack;
	elemento e;
	long long i;
	stack = malloc(sizeof(pila));
	Initialize(stack);
	long long zero = 0;
	//quitamos los posibles pares del for
	//n%2
	while(n % 2 == zero){
		e.n = 2;
		Push(stack, e);
		n /= 2;
	}

	//Recorremos los impares de 3 a n siempre y cuando el cuadrado de i sea menor igual
	//a n.
	for(i = 3; i * i <= n; i +=2){
		//n%i
		while(n % i == zero){//comprobamos que ese mismo numero no sea factor otra vez
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

double gcdWithFactors(double n, double m){
	double gcd = 1.0;
	pila * s1, * s2;
	elemento e1, e2;

	s1 = malloc(sizeof(pila));
	s2 = malloc(sizeof(pila));
	Initialize(s1);
	Initialize(s2);
	//factores de ambos numeros
	s1 = factorizar(n);
	s2 = factorizar(m);
	//las pilas tienen los factores ordenados de mayor a menor
	//(en el tope esta el mayor factor)
	//recorrer pilas
	while(s1->tope != NULL && s2->tope != NULL){
		e1 = Top(s1);
		e2 = Top(s2);
		
		if(e1.n > e2.n){
			e1 = Pop(s1);
		}else if(e2.n > e1.n){
			e2 = Pop(s2);
		}else{ //se encontro un numero igual en ambas pilas
			//Popeamos ambas pilas y el valor lo multiplicamos por el gcd
			e1 = Pop(s1);
			e2 = Pop(s2);
			gcd = gcd * e1.n;
		}
	}

	Destroy(s1);
	Destroy(s2);
	free(s1);
	free(s2);
	return gcd;
}

long long inverseModularAritmethic(long long a, long long n){
	long long quotient, aux;
	//int remainder, previousRemainder = a;
	long long auxInverse = 0; long long inverse = 1;
  long long t = 1; long long old_t = 0;
  long long result = n; long long previousResult = a;
	
  //printf("s=%d, t=%d, result=%d, olds=%d, oldt=%d, oldresult=%d,\n", s,t,result, inverse, old_t, previousResult);
	while(result > 0){ // result tambien nos indica si 
		//al final es igual a 1 que a y n son coprimos
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