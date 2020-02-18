#include "Sort.h"

void mergeBidimentional(int n, int array[n][2], int l, int m, int r){
	int i, j , k, leftSize, rightSize;
	leftSize = m - l + 1;
	rightSize = r - m;
	//arrays temporales para guardar valores
	int leftArray[leftSize][2];
	int rightArray[rightSize][2];

	//copiar datos en arrays temporales
	for(i = 0; i < leftSize; i++){
		leftArray[i][0] = array[i + l][0];
		leftArray[i][1] = array[i + l][1];
	}

	for(i = 0; i < rightSize; i++){
		rightArray[i][0] = array[m+i+1][0];
		rightArray[i][1] = array[m+i+1][1];
	}

	//merge temporales en original
	i = 0;
	j = 0;
	k = l;

	while(i < leftSize && j < rightSize){
		if(leftArray[i][1] <= rightArray[j][1]){
			array[k][0] = leftArray[i][0];
			array[k][1] = leftArray[i][1];
			i++;
		}else{
			array[k][0] = rightArray[j][0];
			array[k][1] = rightArray[j][1];
			j++;
		}
		k++;
	}

	//checar si queda valores en arrayLeft o Right
	while (i < leftSize){ 
	  array[k][0] = leftArray[i][0];
	  array[k][1] = leftArray[i][1]; 
	  i++; 
	  k++; 
  } 

  while (j < rightSize){ 
	  array[k][0] = rightArray[j][0];
	  array[k][1] = rightArray[j][1];  
	  j++; 
	  k++; 
  } 
}

//[l, ..., r, .... n]
void mergeBidimentionalSort(int n, int array [n][2], int l, int r){
		if(l < r){//solo se cumple para arreglos mayores a 1
			int mid = (l + r) / 2;
			mergeBidimentionalSort(n, array, l, mid); //ordenar mitad izquierda
			mergeBidimentionalSort(n, array, mid + 1, r); //ordenar mitad derecha
			
			mergeBidimentional(n, array, l, mid, r); // unir arreglos
		}
}