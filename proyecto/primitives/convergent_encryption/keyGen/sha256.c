#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

#include "sha256.h"

static const int K_READ_BUF_SIZE = { 1024 * 4 };


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
    unsigned char buf[K_READ_BUF_SIZE];

    //tipo de hash
    md = EVP_sha256();
    if (md == NULL) {
        printf("secureHash256(): error message digest\n");
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

