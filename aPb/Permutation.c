#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PermutationLibrary.h"
#include "Sort.h"

//compile: gcc Permutation.c PermutationLibrary.c Sort.c -o Permutation


void cifrarArchivo(FILE * f, int n, int permutation[n]);

int main(int argc, char const *argv[]){
	FILE * in, * out, * permutacion;
	char c, plainText[1024*20];
	int pSize, i = 0, count = 0;

	//ingresar correctamente datos
	if(argc != 4){
		printf("Ejecuta el programa como: Permutation archivo.txt permutacion.txt 0|1\n");
		printf("0: cifrar el archivo\n");
		printf("1: descifrar el archivo\n");
		exit(0);
	}

	//opcion de usuario
	if(memcmp(argv[3], "0", 1) == 0){ // cifrar con permutacion
		printf("Cifrar archivo %s...\n", argv[1]);
		//cargar archivo permutacion
		permutacion = fopen(argv[2], "r");
		//tam de permutacion
		while((c = fgetc(permutacion)) != EOF){
			if(c == ' '){
				i++;
			}
		}
		i++;
		printf("tam per: %d\n", i);
		//cargar permutacion
		pSize = i;
		int permutationArray[i];
		int j;
		for(j = 0; j < i; j++){
			permutationArray[j] = 0;
		}
		rewind(permutacion);
		i = 0;
		while((c = fgetc(permutacion)) != EOF){
			if(c == ' '){
				i++;
				count = 0;
			}else{//convertir permutacion de hasta 2 digitos a decimal
				if(count == 0){
					permutationArray[i] = (c - '0');
					count++;
				} else if(count  == 1){
					permutationArray[i] *= 10;
					permutationArray[i] += (c - '0');
				} else if(count  == 2){
					permutationArray[i] *= 10;
					permutationArray[i] += (c - '0');
				}
				count++;
			}
		}

		printf("Permutacion cargada\n| ");
		for(j = 0; j < i; j++){
			printf("%d | ", permutationArray[j]);
		}
		printf("\n");

		//Cargar archivo a cifrar
		in = fopen(argv[1], "r");
		i = 0;
		while((c = fgetc(in)) != EOF){
			plainText[i] = c;
			i++;
		}
		plainText[i] = '\0';
		printf("Texto cargado: \n");
		printf("%s\n", plainText);

		//obtener texto cifrado con permmutacion
		permuteString(plainText, pSize, permutationArray);
		printf("Texto permutado: \n");
		printf("%s\n", plainText);
		printf("Guardando en archivo...\n");
		char newName[64];
		strcpy(newName, argv[1]);
		strcat(newName, ".per");
		out = fopen(newName, "w");
		fprintf(out, "%s", plainText);
		printf("El texto cifrado se ha guardado en %s\n", newName);
	}else{
		printf("Descrifrar archivo %s...\n", argv[1]);
		permutacion = fopen(argv[2], "r");
		//tam de permutacion
		while((c = fgetc(permutacion)) != EOF){
			if(c == ' '){
				i++;
			}
		}
		i++;
		printf("tam per: %d\n", i);
		//cargar permutacion
		pSize = i;
		int permutationArray[i];
		int j;
		for(j = 0; j < i; j++){
			permutationArray[j] = 0;
		}
		rewind(permutacion);
		i = 0;
		while((c = fgetc(permutacion)) != EOF){
			if(c == ' '){
				i++;
				count = 0;
			}else{//convertir permutacion de hasta 2 digitos a decimal
				if(count == 0){
					permutationArray[i] = (c - '0');
					count++;
				} else if(count  == 1){
					permutationArray[i] *= 10;
					permutationArray[i] += (c - '0');
				} else if(count  == 2){
					permutationArray[i] *= 10;
					permutationArray[i] += (c - '0');
				}
				count++;
			}
		}

		printf("Permutacion cargada\n| ");
		
		//CARCULAR INVERSA DE LA PERMUTACION 
		printf("Calculando permutacion inversa...\n");
		int * inversa = malloc(sizeof(int) * pSize);
		inversa = inversePermutation(pSize, permutationArray);
		for(j = 0; j < i; j++){
			printf("%d | ", inversa[j]);
		}
		printf("\n");
		//Cargar archivo a descifrar
		in = fopen(argv[1], "r");
		i = 0;
		while((c = fgetc(in)) != EOF){
			plainText[i] = c;
			i++;
		}
		plainText[i] = '\0';
		printf("Texto cargado: \n");
		printf("%s\n", plainText);

		//obtener texto descifrado con permmutacion inv
		permuteString(plainText, pSize, permutationArray);
		printf("Texto permutado: \n");
		printf("%s\n", plainText);
		printf("Guardando en archivo...\n");
		char newName[64];
		strcpy(newName, argv[1]);
		strcat(newName, ".per");
		out = fopen(newName, "w");
		fprintf(out, "%s", plainText);
		printf("El texto descifrado se ha guardado en %s\n", newName);
	}

	
	return 0;
}
