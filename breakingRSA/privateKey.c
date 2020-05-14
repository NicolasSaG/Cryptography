#include <stdio.h>
#include "TADPilaDin.h"
#include "basicos.h"

//gcc privateKey.c basicos.c TADPilaDin.c -o privateKey
int main(int argc, char const *argv[]){
	pila * s;

	long long e;
	long long n;
	//1
	// e = 1283;
	// n = 4258141;
	
	//2
	// e= 188443;
	// n= 944159;
	
	// //3
	// e = 1987;
	// n = 5963;
	
	// //4
	// e = 34567;
	// n = 23264323;
	
	// //5
	e = 233471;
	n = 4510872627967657319;

	//calcular factores n
	printf("n= %lli\n", n);
	s = factorizar(n);
	elemento el;
	long long p, q;


	//primerfactor
	el = Pop(s);
	p = el.n;
	//segundo factor
	el = Pop(s);
	q = el.n;
	printf("p = %lli, q = %lli\n", p, q);

	//calcular phi(n)	
	long long phiN = (p - 1) *(q - 1);
	printf("phi(n) = %lli\n", phiN);

	//calcular inverso de e
	long long inverso = inverseModularAritmethic(e, phiN); 
	printf("d = %lli\n", inverso);
	Destroy(s);	
	return 0;
}