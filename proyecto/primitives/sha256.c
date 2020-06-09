#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

static const int K_READ_BUF_SIZE = { 1024 * 16 };

//gcc sha256.c -lssl -lcrypto -o sha256

//execute ./sha256 file.txt
unsigned char * secureSHA256(char * filename);

int main(int argc, char *argv[]){
    unsigned char * shaDigest = secureSHA256(argv[1]); 
    int i;
    printf("Digest is: ");
    for (i = 0; i < 32; i++)
        printf("%02x", shaDigest[i]);
    printf("\n");
    
    return 0;
}

unsigned char * secureSHA256(char * filename){
    if (!filename) {
        return NULL;
    }
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return NULL;
    }
    EVP_MD_CTX * mdctx;
    const EVP_MD * md;
    unsigned int md_len;
    unsigned char * sha256_digest = malloc(sizeof(unsigned char) * EVP_MAX_MD_SIZE);
    unsigned char buf[1024*4];

    //tipo de hash
    md = EVP_sha256();
    if (md == NULL) {
        printf("secureHash256(): Unknown message digest\n");
        exit(1);
    }
    //inicializar contexto
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    while (!feof(fp)){
        size_t total_read = fread(buf, 1, sizeof(buf), fp);
        if(!EVP_DigestUpdate(mdctx, buf, strlen(buf))){
            return NULL;
        }
    }   
    fclose(fp);

    if(!EVP_DigestFinal_ex(mdctx, sha256_digest, &md_len))
        return NULL;
    
    EVP_MD_CTX_free(mdctx);

    return sha256_digest;
}

