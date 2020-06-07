#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

static const int K_READ_BUF_SIZE = { 1024 * 16 };

//gcc sha256.c -lssl -lcrypto -o sha256
unsigned char * calculateSHA1(char * filename);

int main(int argc, char *argv[]){
    unsigned char * shaDigest = calculateSHA256(argv[1]); 

    char *sha256hash = (char *)malloc(sizeof(char) * 65);
    sha256hash[65] = '\0';
    int i;
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++){
        sprintf(&sha256hash[i*2], "%02x", shaDigest[i]);
    }
    printf("SHA256 hash: %s\n", sha256hash);
    
    return 0;
}
    //sha1 40 char 459567d3bde4418b7fe302ff9809c4b0befaf7dd
    //sha256 64 char 0b894166d3336435c800bea36ff21b29eaa801a52f584c006c49289a0dcf6e2f

unsigned char * calculateSHA256(char * filename){
    if (!filename) {
        return NULL;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return NULL;
    }

    unsigned char * sha256_digest = malloc(sizeof(char) * SHA256_DIGEST_LENGTH);
    SHA256_CTX context;

    if(!SHA256_Init(&context))
        return NULL;

    unsigned char buf[K_READ_BUF_SIZE];
    while (!feof(fp)){
        size_t total_read = fread(buf, 1, sizeof(buf), fp);
        if(!SHA256_Update(&context, buf, total_read)){
            return NULL;
        }
    }
    fclose(fp);

    if(!SHA256_Final(sha256_digest, &context))
        return NULL;

    return sha256_digest;
}
