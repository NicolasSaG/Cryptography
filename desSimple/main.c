#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DESLibrary.h"

//gcc main.c DESLibrary.c -o main

int main(int argc, char const *argv[]){
	int p10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
	int k, i;
	FILE * in, * out;
	if(argc != 3){
		printf("Ejecuta el programa como: main archivo.txt 0|1\n");
		printf("0: cifrar el archivo\n");
		printf("1: descifrar el archivo\n");
		exit(0);
	}

	if(memcmp(argv[2], "0", 1) == 0){ // cifrar con sdes
		unsigned char buffer[1024*20];
		char c;
		char newName[64];
		k = 5; //generar pseudo aleatoriamente
		//Encontrar k1 y k2 i guardar en globales
		findKn(k, 10, p10);
		//leer archivo a cifrar y guardarlo en buffer
		in = fopen(argv[1], "r");
		i = 0;
		while((c = fgetc(in)) != EOF){
			buffer[i] = c;
			i++;
		}
		buffer[i] = '\0';
		printf("buffer size:%d\n", strlen(buffer));
		int auxSize = strlen(buffer);
		//printf("Buffer: %s\n", buffer);
		printf("Cifrando con OM CBC...\n");
		int iv = 100; //generar aleatoriamente
		operationModeEncryptCBC(buffer, iv);

		//guardar cifrado en archivo
		strcpy(newName, argv[1]);
		strcat(newName, ".sdes");
		out = fopen(newName, "w");
		i = 0;
		while(i < auxSize){
			fprintf(out, "%.2x ", buffer[i]);
			i++;
		}
		printf("El texto cifrado se ha guardado en %s\n", newName);
	}else{

	}
	// int p10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
	// int k = 642; //1010000010
	// int i;
	// for(i = 0; i < 10; i ++)
	// 	printf("%d ", getBitValue(k, 9-i));
	// printf("\n");
	// //abrir archivo pasado por consola
	// //FILE * in = fopen(argv[1], "r");
	// //crear archivo res de cifrar o descifrar
	// //File * out = fopen("archivo.sdes", "w");
	
	// //Encontrar k1 y k2 i guardar en globales
	// findKn(k, 10, p10);
	// printf("k1= %d, k2=%d\n", k1, k2);

	// //cifrar con s-des
	// //if(*argv[2] == '0'){
	// 	//printf("Cifrando %s...\n", argv[1]);
	// printf("cifrando...\n");
	// unsigned char c = 189;
	// printf("Letra A: ");
	// printBinary(c, 8);
	// //c = encodeDESSimplified(c);
	// //printf("Cifrada: \n");
	// //printBinary(c, 8);
	// c = 117;
	// printBinary(c, 8);
	
	
	// unsigned char m = decodeDESSimplified(c);
	// printf("Descifrada: \n");
	// printBinary(m, 8);
	// 	//printf("Archivo cifrado\n");
	// //}
	return 0;
}