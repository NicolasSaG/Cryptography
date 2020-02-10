#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alphabet.h"
#include "vigenereLibrary.h"
#include "affineLibrary.h"

//compile: gcc ciphers.c alphabet.c vigenereLibrary.c affineLibrary.c -o ciphers
void cargarAlfabeto();
int opciones();
void cifrarVigenere();
void descifrarVigenere();
void validarLlaveAfin();
void calcularInversoLlaveAfin();
void cifrarAfin();
void descifrarAfin();

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
			case 3:
				printf("Validar llave para cifrado Afin\n");
				validarLlaveAfin();
			break;
			case 4:
				printf("Calcular inverso de llave valida k=(a, b) y n\n");
				calcularInversoLlaveAfin();
			break;
			case 5:
				printf("Cifrar texto con Afin\n");
				cifrarAfin();
			break;
			case 6:
				printf("Descifrar texto con Afin\n");
				descifrarAfin();
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
	printf("3 Validar llave de cifrado afin\n");
	printf("4 Calcular inverso de llave valida de cifrado afin\n");
	printf("5 Cifrar texto con Afin\n");
	printf("6 Descifrar texto con Afin\n");
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
			key = generateVigenereRandomKey();
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
	fclose(plaintextFile);
	fclose(ciphertextFile);
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
	fclose(plaintextFile);
	fclose(ciphertextFile);
	//cifrado vigenere terminado matar FILE
}

void validarLlaveAfin(){
	int a, b, n;
	printf("Llave de cifrado afin.  k = (a, b)\n");
	printf("Ingresa la llave de la forma a, b: ");
	printf("\nEjemplo: 23, 45\n");
	scanf("%d, %d", &a, &b);
	printf("Ingrese la longitud del alfabeto n: ");
	scanf("%d", &n);
	printf("Llave ingresada k = (%d, %d), n = %d\n", a, b, n);
	
	//validar llave
	if(validateAffineKey(a, n) == -1){
		printf("Llave no valida, a = %d y n = %d no son coprimos\n", a, n);
	}else{
		printf("-- Llave k =(%d, %d) valida para n = %d -- \n", a, b, n);
	}
}

void calcularInversoLlaveAfin(){
	int a, b, n, inv;
	printf("Ingresa la llave de la forma a, b: ");
	printf("\nEjemplo: 23, 45\n");
	scanf("%d, %d", &a, &b);
	printf("Ingrese la longitud del alfabeto n: ");
	scanf("%d", &n);
	printf("Llave ingresada k = (%d, %d), n = %d\n", a, b, n);
	inv = inverseModularAritmethic(a, n);
	printf("a^-1modn = %d^-1mod%d = %d\n", a, n, inv);
	printf("%d*%dmod%d = 1\n", a, inv , n);
}

void cifrarAfin(){
	FILE * plaintextFile, * ciphertextFile;
	int bufferLength =1024 * 20;
	char fileNameIn[256], fileNameOut[256], buffer[bufferLength], * key, * ciphertext;
	char c;
	int llaveOpcion, i;
	int a, b, inverso;

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
				printf("\nIngrese la llave como :a, b\n");
				fflush(stdin);
				scanf("%d, %d", &a, &b);
				//validar llave
				if(gcd(a, alphabetSize_GLOBAL) != 1){
					printf("\nIngrese una llave Valida (a=%d debe ser coprimo de n=%d): ", a, alphabetSize_GLOBAL);
				}else{
					break;
				}
			}while(gcd(a, alphabetSize_GLOBAL) != 1);
			break;
		}else if(llaveOpcion == 1){
			a = generateAffineARandomKey(alphabetSize_GLOBAL);
			b = generateAffineBRandomKey(alphabetSize_GLOBAL);
			break;
		}else{
			printf("\nIngrese una opcion valida (0 o 1): ");
		}
	}

	printf("Llave: k = (%d, %d)\n", a, b);
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
	ciphertext = encodeAffine(buffer, a, b);

	//guardar en archivo con el mismo nombre del archivo del texto a cifrar con extension .aff
	printf("Cifrado: %s\n", ciphertext);
	strcpy(fileNameOut, fileNameIn);
	strcat(fileNameOut, ".aff");
	ciphertextFile = fopen(fileNameOut, "w");
	i = 0;
	while(ciphertext[i] != '\0'){
		fprintf(ciphertextFile, "%c", ciphertext[i]);
		i++;
	}
	printf("Llave usada para cifrar: (%d, %d)\n", a, b);
	fclose(plaintextFile);
	fclose(ciphertextFile);
}

void descifrarAfin(){
	FILE * plaintextFile, * ciphertextFile;
	int bufferLength =1024 * 20;
	char fileNameIn[256], fileNameOut[256], *fileNameAux, buffer[bufferLength], * key, * plaintext;
	char c;
	char extension[4] = ".";
	int llaveOpcion, i;
	int a, b, inverso;

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
		printf("\nIngrese la llave como :a, b\n");
		fflush(stdin);
		scanf("%d, %d", &a, &b);
		//validar llave
		if(gcd(a, alphabetSize_GLOBAL) != 1){
			printf("\nIngrese una llave Valida (a=%d debe ser coprimo de n=%d): ", a, alphabetSize_GLOBAL);
		}else{
			break;
		}
	}while(gcd(a, alphabetSize_GLOBAL) != 1);
			

	printf("Llave: k = (%d, %d)\n", a, b);
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
	printf("descifrando texto... \n");
	plaintext = decodeAffine(buffer, a, b);

	//guardar en archivo con el mismo nombre del archivo del texto a cifrar con extension .aff
	printf("descifrado: %s\n", plaintext);
	fileNameAux = strtok(fileNameIn, extension);
	strcat(fileNameAux, ".txt");
	printf("%s\n", fileNameAux);
	plaintextFile = fopen(fileNameAux, "w");
	i = 0;
	while(plaintext[i] != '\0'){
		fprintf(plaintextFile, "%c", plaintext[i]);
		i++;
	}
	fclose(plaintextFile);
	fclose(ciphertextFile);
}