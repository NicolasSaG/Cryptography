#include <stdio.h>

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
	printf("CSPRG\n");
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

	printf("key gwenerator for secret key cryptography\n");
	const int kBits = 1024;
	const int kExp = 3;

	int keylen;
	char *pem_key;

	RSA *rsa = RSA_generate_key(kBits, kExp, 0, 0);

	/* To get the C-string PEM form: */
	BIO *bio = BIO_new(BIO_s_mem());
	PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);

	keylen = BIO_pending(bio);
	pem_key = calloc(keylen+1, 1); /* Null-terminate */
	BIO_read(bio, pem_key, keylen);

	printf("%s", pem_key);

	BIO_free_all(bio);
	RSA_free(rsa);
	free(pem_key);

	char nu [17];
	BIGNUM * b = BN_new(void);
	int a = BN_rand(b, 128, 0, 0);
	BN_bn2dec(nu, b);
	printf("Random number: %s\n", nu);	
	
	BN_free(b);

	return 0;
}