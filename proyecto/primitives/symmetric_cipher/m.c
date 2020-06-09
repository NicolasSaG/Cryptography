#include <stdio.h>
#include "aes.h"

//gcc m.c aes.c -lssl -lcrypto -o m
int main(int argc, char *argv[]){
    unsigned char *  key = (unsigned char *) "0B894166D3336435C800BEA36FF21B29EAA801A52F584C006C49289A0DCF6E2F";
    FILE * cifrado = encryptAES256CFB(argv[1], key);
    fclose(cifrado);
    printf("todo bien \n");
    return 0;
}
