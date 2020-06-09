#include <stdio.h>
//gcc aes.c  -lssl -lcrypto -c
char * base64(unsigned char * input, int length);
FILE * encryptAES256CFB(char * filename, unsigned char * key);
//FILE * decryptAES256CFB(char * filename, unsigned char * key);

void handleErrors();
// int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);
// int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext);