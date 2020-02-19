#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PermutationLibrary.h"
#include "Sort.h"

//compile: gcc Permutation.c PermutationLibrary.c Sort.c -o Permutation


void cifrarArchivo(FILE * f, int n, int permutation[n]);

int main(){

	int prueba [5] = {3, 5,  2, 1, 4};
	int * x = malloc(sizeof(int) * 5);
	char h [11] = "alh omundo";
	int i;
	//x = inversePermutation(5, prueba);
	//printf("_____________ inversa guardada\n");
	for(i = 0; i< 5; i++){
		printf("%d, ", prueba[i]);
	}

	printf("\nmensaje con prueba a cifrar con no inversa: %s\n", h);

	permuteString(h, 5, prueba);
	
	return 0;
}

void cifrarArchivo(FILE * f, int n, int permutation[n]){
	FILE * plainTextFile, * cipherTextFile;
	char filenameIn[256], filenameOut[256], ciphertext[1024*20], c;
	char buffer[1024 * 20];
	int i;
	// pedir archivo del texto a cifrar
	printf("Ingresa la ruta del texto a cifrar con permutacion por caracteres: ");
	fflush(stdin);
	gets(filenameIn);
	do{
		plainTextFile = fopen(filenameIn, "r");
		if (plainTextFile == NULL){
			printf("No se pudo abrir el archivo %s\n", filenameIn);
			printf("Ingrese una ruta valida: ");
			fflush(stdin);
			gets(filenameIn);
		}else{
			printf("Archivo con texto a cifrar cargado.\n");
		}
	}while(plainTextFile == NULL);

	//generar permutacion tam n random
	//permutation = randomPermutation(n)


	//guardar texto de archivo a cifrar en buffer
	while((c = fgetc(plainTextFile))  != EOF){
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';
	
	//cifrar
	printf("Cifrando texto... \n");
	//permute strings en bloques de tam n
	//ciphertext = permuteString(buffer, n, permutation);
	

	//guardar texto cifrado
	strcpy(filenameOut, filenameIn);
	strcat(filenameOut, ".per");
	cipherTextFile = fopen(filenameOut, "w");
	i = 0;
	while(ciphertext[i] != '\0'){
		fprintf(cipherTextFile, "%c", ciphertext[i]);
		i++;
	}
	fclose(plainTextFile);
	fclose(cipherTextFile);
}