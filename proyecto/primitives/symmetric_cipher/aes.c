#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "aes.h"

static const int BLOCK_SIZE = { 128 };

char * base64(unsigned char * input, int length){
    BIO * bmem, *b64;
    BUF_MEM * bptr;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char * buf = (char *) malloc(bptr->length);
    memcpy(buf, bptr->data, bptr->length-1);

    buf[bptr->length-1] = 0;
    BIO_free_all(b64);
    return buf;
}

FILE * encryptAES256CFB(char * filename, unsigned char * key){
    //comprobar entradas
    if(key == NULL)
        return NULL;

    if(filename == NULL)
        return NULL;
    
    FILE * m = fopen(filename, "rb");
    FILE * c = fopen("cifrado.aes", "wb");
    if(m == NULL)
        return NULL;
    printf("vamos bien\n");
    EVP_CIPHER_CTX *ctx;
    unsigned char buf[BLOCK_SIZE];
    unsigned char cBuf[BLOCK_SIZE];
    char * cBase64;
    int len, tmplen;
    unsigned char * iv = (unsigned char *) "9D81CEB272BB47EEAA8CA5E31F66642A";
    ctx = EVP_CIPHER_CTX_new();
    printf("vamos bien 2\n");
    //checar ctx
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, key, iv);
    printf("vamos bien 3\n");
    while(!feof(m)){
        printf("vamos bien 4\n");
        size_t total_read = fread(buf, 1, sizeof(buf), m);
        if(!EVP_EncryptUpdate(ctx, cBuf, &len, buf, sizeof(buf))){
            return NULL;
        }
        printf("vamos bien 5\n");
        cBase64 = base64(cBuf, len);
        printf("vamos bien 6\n");
        fwrite(cBase64, 1, len, c);
        printf("vamos bien 7\n");
    }
    printf("vamos bien 8\n");
    if(EVP_EncryptFinal_ex(ctx, cBuf, &tmplen))
    	return NULL;

    printf("vamos bien 9\n");
    cBase64 = base64(cBuf, tmplen);
    fwrite(cBase64, 1, tmplen, c);
    fclose(m);
    EVP_CIPHER_CTX_free(ctx);
    return c;
}

// FILE * decryptAES256CFB(char * filename, unsigned char * key){
    
// }

void handleErrors(){
    ERR_print_errors_fp(stderr);
    abort();
}

// int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext){
//     EVP_CIPHER_CTX *ctx;
//     int len;
//     int ciphertext_len;
//     if(!(ctx = EVP_CIPHER_CTX_new()))
//         handleErrors();
//     if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_192_cfb(), NULL, key, iv))
//         handleErrors();
//     if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
//     	handleErrors();
//     ciphertext_len = len;
//     if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
//     	handleErrors();
//     ciphertext_len += len;
//     EVP_CIPHER_CTX_free(ctx);
//     return ciphertext_len;
// }
	
// int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext){
//     EVP_CIPHER_CTX *ctx;
//     int len;
//     int plaintext_len;
//     if(!(ctx = EVP_CIPHER_CTX_new()))
//         handleErrors();
//     if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_192_cfb(), NULL, key, iv))
//         handleErrors();
//     if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
//         handleErrors();
//     plaintext_len = len;
//     if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
//         handleErrors();
//     plaintext_len += len;
//     EVP_CIPHER_CTX_free(ctx);
//     return plaintext_len;
// }

// int main(int argc, char const *argv[]){
// 	unsigned char *key = (unsigned char *)"F9D387012FA218F75BEFDE20DD8A5F2239FEA60EE7207AC8";
// 	unsigned char *iv = (unsigned char *)"9D81CEB272BB47EEAA8CA5E31F66642A";
// 	unsigned char *plaintext =(unsigned char *)"Kionda kionda? prueba para AES";
// 	unsigned char ciphertext[112400];
// 	unsigned char decryptedtext[112400];
// 	int decryptedtext_len, ciphertext_len;
//     printf("AES 192\n");
// 	ciphertext_len = encrypt(plaintext, strlen ((char *)plaintext), key, iv, ciphertext);
// 	printf("Ciphertext is:\n");
//     printf("%s\n", ciphertext);
//     BIO_dump_fp(stdout, (const char *)ciphertext, ciphertext_len);
//     decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);
//     decryptedtext[decryptedtext_len] = '\0';
//     printf("Decrypted text is:\n");
//     printf("%s\n", decryptedtext);


// 	return 0;
// }
