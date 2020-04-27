#include <stdio.h>
#include <string.h>

//random bytes
#include <openssl/rand.h>
//bignum
#include <openssl/bn.h>


//secret key
#include <openssl/rsa.h>
#include <openssl/pem.h>


//stream ciphers
#include <openssl/evp.h>



//compile: gcc prueba.c -lssl -lcrypto -o prueba

int main(int argc, char const *argv[]){
	unsigned char buffer[128] = "";
	int n = 128;
	
	//CSPRG 
	printf("generador de llaves\n");
	//se almacenan en un  unsigned char *
					  //lugar donde se almacena
							//num de bytes a generar
	int r = RAND_bytes(buffer, n);
	for(int i = 0; i < n; i ++){
		if(i%16 == 0)
			printf("\n");
		printf("%.2x ", buffer[i]);
	}
	printf("\n");
	/*
	printf("key gwenerator for secret key cryptography\n");
	const int kBits = 1024;
	const int kExp = 3;

	int keylen;
	char *pem_key;

	RSA *rsa = RSA_generate_key(kBits, kExp, 0, 0);

	BIO *bio = BIO_new(BIO_s_mem());
	PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);

	keylen = BIO_pending(bio);
	pem_key = calloc(keylen+1, 1); 
	BIO_read(bio, pem_key, keylen);

	printf("%s", pem_key);

	BIO_free_all(bio);
	RSA_free(rsa);
	free(pem_key);
	*/

	char  * nu = malloc(sizeof(char)*16);
	//inicializar
	BIGNUM * b = BN_new();
	//generar random de 128 bits
	int a = BN_rand(b, 128, 0, 0);
	//convertir BIGNUM a string y guardarla en un puntero
	nu = BN_bn2dec(b);
	printf("random number:\n");
	for(int j = 0; j < 16; j++){
		printf("%c", nu[j]);
	}
	printf("\n");
	//liberar memoria de BIGNUM
	BN_free(b);



	//stream cipher
	//solo rc4
	char buf[128] = "hola mundo cifrado con rc4 xd, ya llevame covid-19";
	char descifrado[128];
	unsigned char outbuf[128];
	int outlen, tmplen;
	int desout, destmp;
	//EVP_rc4()
	//key length de 128 bita
	unsigned char key[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char iv[16] = {0,0,0,0,0,0,0,0};
	
	EVP_CIPHER_CTX *ctx;
	ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_rc4(), NULL, key, iv);

	if (!EVP_EncryptUpdate(ctx, outbuf, &outlen, buf, strlen(buf))) {
         /* Error */
         EVP_CIPHER_CTX_free(ctx);
         return 0;
    }

    if (!EVP_EncryptFinal_ex(ctx, outbuf + outlen, &tmplen)) {
        /* Error */
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    outlen += tmplen;
    EVP_CIPHER_CTX_free(ctx);

    //decrypt
    
	ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_rc4(), NULL, key, iv);

    if (!EVP_EncryptUpdate(ctx, descifrado, &desout, outbuf, strlen(outbuf))) {
         /* Error */
         EVP_CIPHER_CTX_free(ctx);
         return 0;
    }
    if (!EVP_EncryptFinal_ex(ctx, descifrado + desout, &destmp)) {
        /* Error */
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    desout += destmp;
    EVP_CIPHER_CTX_free(ctx);



    FILE * out = fopen("enc.rc4", "wb");
    if (out == NULL) {
        return 0;
    }
    for(int k = 0; k< outlen; k++){
    	fprintf(out, "%.2x ", outbuf[k]);	
    }
    fprintf(out, "\n");
    for(int k = 0; k< desout; k++){
    	fprintf(out, "%c", descifrado[k]);	
    }
    
    //fwrite(outbuf, 1, outlen, out);
    
    fclose(out);
    

    //fin CIFRADO RC4
	


	return 0;
}