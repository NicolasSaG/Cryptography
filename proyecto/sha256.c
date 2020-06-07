#include <stdio.h>
#include <openssl/sha.h>

static const int K_READ_BUF_SIZE = { 1024 * 16 };

int main(int argc, char const *argv[]){
    unsigned char * shaDigest = calculateSHA1("a.txt"); 

    char *sha1hash = (char *)malloc(sizeof(char) * 41);
    sha1hash[41] = '\0';
    int i;
    for (i = 0; i < SHA_DIGEST_LENGTH; i++){
        sprintf(&sha1hash[i*2], "%02x", shaDigest[i]);
    }
    printf("SHA1 HASH: %s\n", sha1hash);
    
    return 0;
}
    //sha1 40 char 459567d3bde4418b7fe302ff9809c4b0befaf7dd
    //sha256 64 char 0b894166d3336435c800bea36ff21b29eaa801a52f584c006c49289a0dcf6e2f

unsigned char * calculateSHA1(char * filename){
    if (!filename) {
        return NULL;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return NULL;
    }

    unsigned char * sha1_digest = malloc(sizeof(char) * SHA_DIGEST_LENGTH);
    SHA_CTX context;

    if(!SHA1_Init(&context))
        return NULL;

    unsigned char buf[K_READ_BUF_SIZE];
    while (!feof(fp)){
        size_t total_read = fread(buf, 1, sizeof(buf), fp);
        if(!SHA1_Update(&context, buf, total_read)){
            return NULL;
        }
    }
    fclose(fp);

    if(!SHA1_Final(sha1_digest, &context))
        return NULL;

    return sha1_digest;
}
