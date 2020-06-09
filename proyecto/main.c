#include <stdio.h>
#include "primitives/convergent_encryption/keyGen/sha256.h"

//gcc main.c primitives/convergent_encryption/keyGen/sha256.c -lssl -lcrypto -o main
int main(int argc, char *argv[]){
    unsigned char * digest = secureSHA256(argv[1]);
    int i;
    for(i = 0; i < 32; i++)
        printf("%02x", digest[i]);
    printf("\n");
    
    return 0;
}


