 #include <stdio.h>
 #include <string.h>
 #include <openssl/evp.h>




 int main(int argc, char *argv[])
 {
     EVP_MD_CTX *mdctx;
     const EVP_MD *md;
     char mess1[] = "hola mundo";
     unsigned char md_value[EVP_MAX_MD_SIZE];
     unsigned int md_len, i;

     if (argv[1] == NULL) {
         printf("Usage: mdtest digestname\n");
         exit(1);
     }

     md = EVP_get_digestbyname(argv[1]);
     if (md == NULL) {
         printf("Unknown message digest %s\n", argv[1]);
         exit(1);
     }

     mdctx = EVP_MD_CTX_new();
     EVP_DigestInit_ex(mdctx, md, NULL);
     EVP_DigestUpdate(mdctx, mess1, strlen(mess1));
     EVP_DigestFinal_ex(mdctx, md_value, &md_len);
     EVP_MD_CTX_free(mdctx);

     printf("Digest is: ");
     for (i = 0; i < md_len; i++)
         printf("%02x", md_value[i]);
     printf("\n");

     exit(0);
 }



 // unsigned char * calculateSHA256(char * filename){
//     if (!filename) {
//         return NULL;
//     }

//     FILE *fp = fopen(filename, "rb");
//     if (fp == NULL) {
//         return NULL;
//     }

//     unsigned char * sha256_digest = malloc(sizeof(char) * SHA256_DIGEST_LENGTH);
    
//     EVP_MD_CTX * context = EVP_MD_CTX_new();
//     const EVP_MD * md;
//     //md = EVP_get_digestbyname();
//     // if(!EVP_DigestInit_ex(&context))
//     //     return NULL;

//     // unsigned char buf[K_READ_BUF_SIZE];
//     // while (!feof(fp)){
//     //     size_t total_read = fread(buf, 1, sizeof(buf), fp);
//     //     if(!SHA256_Update(&context, buf, total_read)){
//     //         return NULL;
//     //     }
//     // }
//     // fclose(fp);

//     // if(!SHA256_Final(sha256_digest, &context))
//     //     return NULL;

//     return sha256_digest;
// }