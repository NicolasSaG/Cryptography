#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alphabet.h"
#include "vigenereLibrary.h"

//compile: gcc Vigenere.c alphabet.c vigenereLibrary.c -o Vigenere
void cargarAlfabeto();
int opciones();
void cifrarVigenere();
void descifrarVigenere();

int main(){
	int opcion = 0;
	//cargar alfabeto
	printf("Session 1: Classical cryptography\n");
	printf("Ingresa la ruta del alfabeto: \n");
	cargarAlfabeto();
	while(1){
		//obtener seleccion
		opcion = opciones();
		switch(opcion){
			case 1:
				printf("Cifrar texto con Vigenere\n");
				cifrarVigenere();
			break;
			case 2:
				printf("Descifrar texto con Vigenere\n");
				descifrarVigenere();
			break;
			case 7:
				printf("Ingrese ruta del alfabeto: \n");
				cargarAlfabeto();
			break;
			case 8:
				printf("Adios :D\n");
				exit(0);
			break;
			default:
				printf("Opcion no valida\n");
			break;
		}
		
	}

	//menu
	/*
		cifrar vigenere
		descifrar vigenere
		validar llave  de cifrado Afin
		calcular inverso de llave valida de cifrado afin
		cifrar afin
		descifrar afin
	*/

	// FILE * f = fopen("alphabet.txt", "r");
	// addAlphabet(f);

	// char * plaintext, * ciphertext,* key2, key [32];
	// plaintext = malloc(sizeof(char) * 64);
	// ciphertext = malloc(sizeof(char) * 64);
	// printAlphabet();
	// printf("Ingresa tu texto plano: ");
	// gets(plaintext);
	// printf("Ingresa tu llave: ");
	// gets(key);
	// printf("\nplaintext: %s\n", plaintext);
	// printf("key: %s\n", key);
	
	// if(validWord(key) == -1){
	// 	printf("No se encontro un caracter de la llave: %s en el alfabeto\n", key);
	// 	exit(0);
	// }
	// printf("Encriptando...\n");
	// ciphertext = encodeVigenere(plaintext, key);
	// printf("cipher: %s\n", ciphertext);
	
	// plaintext = malloc(sizeof(char) * strlen(plaintext));
	// printf("Desencriptando...\n");
	// plaintext = decodeVigenere(ciphertext, key);
	// printf("plaintext nuevo: %s\n", plaintext);
	
	// key2 = generateRandomKey();
	// printf("Key random:|%s|\n", key2);

	// free(key2);
	// free(plaintext);
	// free(ciphertext);
	return 0;
}


void cargarAlfabeto(){
	char ruta [256];
	fflush(stdin);
	gets(ruta);
	FILE * alphabet = fopen(ruta, "r");
	if(alphabet == NULL){
		printf("Error, no se pudo cargar el alfabeto en %s\n", ruta);
		exit(1);
	}

	addAlphabet(alphabet);
	printAlphabet();
	fclose(alphabet);
}

int opciones(){
	int opcion = 0;
	printf("------ Menu ------\n");
	printf("1 Cifrar texto con Vigenere\n");
	printf("2 Descifrar texto con Vigenere\n");
	// validar llave  de cifrado Afin
	// 	calcular inverso de llave valida de cifrado afin
	// 	cifrar afin
	// cargar otro alfabeto
	// 	descifrar afin
	printf("7 Cargar otro alfabeto\n");
	printf("8 Salir\n");
	scanf("%d", &opcion);
	
	return opcion;
}

void cifrarVigenere(){
	FILE * plaintextFile, * ciphertextFile;
	int bufferLength =1024 * 20;
	char fileNameIn[256], fileNameOut[256], buffer[bufferLength], * key, * ciphertext;
	char c;
	int llaveOpcion, i;

	key = malloc(sizeof(char) * 64);
	ciphertext = malloc(sizeof(char) * bufferLength);

	// pedir archivo del texto a cifrar
	printf("Ingresa la ruta del texto a cifrar: ");
	fflush(stdin);
	gets(fileNameIn);
	do{
		plaintextFile = fopen(fileNameIn, "r");
		if (plaintextFile == NULL){
			printf("No se pudo abrir el archivo %s\n", fileNameIn);
			printf("Ingrese una ruta valida: ");
			fflush(stdin);
			gets(fileNameIn);
		}else{
			printf("Archivo con texto a cifrar cargado.\n");
		}
	}while(plaintextFile == NULL);

	//pedir llave o generar random
	while(1){
		printf("\nDesea ingresar una llave (0) o que se genere pseudo aleatoriamente (1)?: ");
		fflush(stdin);
		scanf("%d", &llaveOpcion);
		if(llaveOpcion == 0){
			do{
				printf("\nIngrese la llave: ");
				fflush(stdin);
				gets(key);
				//validar llave
				if(validWord(key) == -1){
					printf("\nIngrese una llave Valida (todos sus caracteres deben estar en el alfabeto): ");
				}else{
					break;
				}
			}while(validWord(key) == -1);
			break;
		}else if(llaveOpcion == 1){
			key = generateRandomKey();
			break;
		}else{
			printf("\nIngrese una opcion valida (0 o 1): ");
		}
	}

	printf("Llave: %s\n", key);
	i = 0;
	//guardar texto de archivo en buffer
	while((c = fgetc(plaintextFile))  != EOF){
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';
	printf("\n");
	printf("Texto: %s\n", buffer);

	//cifrar
	printf("Cifrando texto... \n");
	ciphertext = encodeVigenere(buffer, key);

	//guardar en archivo con el mismo nombre del archivo del texto a cifrar con extension .vig
	printf("Cifrado: %s\n", ciphertext);
	strcpy(fileNameOut, fileNameIn);
	strcat(fileNameOut, ".vig");
	ciphertextFile = fopen(fileNameOut, "w");
	i = 0;
	while(ciphertext[i] != '\0'){
		fprintf(ciphertextFile, "%c", ciphertext[i]);
		i++;
	}
	fprintf(ciphertextFile, "\0");
	fclose(plaintextFile);
	fclose(ciphertextFile);
	//cifrado vigenere terminado matar FILE
}

void descifrarVigenere(){
	FILE * plaintextFile, * ciphertextFile;
	int bufferLength =1024 * 20;
	char fileNameIn[256], fileNameOut[256], * fileNameAux, buffer[bufferLength], * key, * plaintext;
	char c;
	const char extension[5] = "vig";
	int llaveOpcion, i;

	key = malloc(sizeof(char) * 64);
	plaintext = malloc(sizeof(char) * bufferLength);

	// pedir archivo del texto a cifrar
	printf("Ingresa la ruta del texto a descifrar: ");
	fflush(stdin);
	gets(fileNameIn);
	do{
		ciphertextFile = fopen(fileNameIn, "r");
		if (ciphertextFile == NULL){
			printf("No se pudo abrir el archivo %s\n", fileNameIn);
			printf("Ingrese una ruta valida: ");
			fflush(stdin);
			gets(fileNameIn);
		}else{
			printf("Archivo con texto a descifrar cargado.\n");
		}
	}while(ciphertextFile == NULL);

	//pedir llave o generar random
	do{
		printf("\nIngrese la llave: ");
		fflush(stdin);
		gets(key);
		//validar llave
		if(validWord(key) == -1){
			printf("\nIngrese una llave Valida (todos sus caracteres deben estar en el alfabeto): ");
		}else{
			break;
		}
	}while(validWord(key) == -1);

	printf("Llave: %s\n", key);
	i = 0;
	//guardar texto de archivo en buffer
	while((c = fgetc(ciphertextFile))  != EOF){
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';
	printf("\n");
	printf("Texto: %s\n", buffer);

	//cifrar
	plaintext = decodeVigenere(buffer, key);
	//guardar en archivo con el mismo nombre del archivo del texto a cifrar con extension .vig
	printf("Descifrado: %s\n", plaintext);

	//obtener nombre original de archivo cifrado sin .vig
	fileNameAux = strtok(fileNameIn, extension);

	printf("%s\n", fileNameAux);
	plaintextFile = fopen(fileNameAux, "w");
	i = 0;
	while(plaintext[i] != '\0'){
		fprintf(plaintextFile, "%c", plaintext[i]);
		i++;
	}
	fprintf(plaintextFile, "\0");
	fclose(plaintextFile);
	fclose(ciphertextFile);
	//cifrado vigenere terminado matar FILE
}