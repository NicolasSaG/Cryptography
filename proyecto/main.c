#include <stdio.h>
#include "primitives/convergent_encryption/keyGen/sha256.h"

//gcc main.c primitives/convergent_encryption/keyGen/sha256.c -lssl -lcrypto -o main


//prueba cifrado convergente
int main(int argc, char *argv[]){

    //calcular hash de archivo
    unsigned char * key = secureSHA256(argv[1]);
    int i;
    for(i = 0; i < 32; i++)
        printf("%02x", key[i]);
    printf("\n");

    //cifrar archivo con cifrado simetrico
    //usando su hash
    
    return 0;
}


