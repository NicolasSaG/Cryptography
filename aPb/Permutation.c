#include <stdio.h>

#include "PermutationLibrary.h"

int main(){

	int prueba [2][3] = {{0,1,2},{2,0,1}};
	
	inversePermutation(3, prueba);
	printPermutation(3, prueba);
	return 0;
}