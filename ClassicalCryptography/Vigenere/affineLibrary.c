#include "affineLibrary.h"
#include <stdio.h>

int validateAffineKey(int a, int n){
	//la llave es valida si mcd(a, n) = 1
	if(gcd(a, n) == 1){ //son coprimos
		return 1;
	}else{
		return -1;
	}
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