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

void encryptRC4(char * filenameIn, char * filenameOut){
	FILE * in, * out;
	EVP_CIPHER_CTX *ctx;
	char * plaintext,  c;
	unsigned char * ciphertext;
	long i, inputSize;
	int ciphertextLength, tmpLength;

	unsigned char key[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char iv[16] = {0,0,0,0,0,0,0,0};

	in = fopen(filenameIn, "r");
	
	if(in == NULL){
		printf("encryptRC4(): Error al abrir el archivo a cifrar\n");
		exit(-1);
	}

	inputSize = 0;
	while((c = fgetc(in)) != EOF){
		inputSize++;
	}

	rewind(in);
	plaintext = malloc(sizeof(char)* inputSize);
	i = 0;
	//cargar archivo a cifrar
	while((c = fgetc(in)) != EOF){
		plaintext[i] = c;
		i++;
	}	

	ciphertext = malloc(sizeof(unsigned char)* inputSize);

	ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_rc4(), NULL, key, iv);

	if (!EVP_EncryptUpdate(ctx, ciphertext, &ciphertextLength, plaintext, strlen(plaintext))) {
    /* Error */
    EVP_CIPHER_CTX_free(ctx);
    return 0;
  }

  if (!EVP_EncryptFinal_ex(ctx, ciphertext + ciphertextLength, &tmpLength)) {
    /* Error */
    EVP_CIPHER_CTX_free(ctx);
    return 0;
  }

  ciphertextLength += tmpLength;
  EVP_CIPHER_CTX_free(ctx);

  out = fopen(filenameOut, "wb");
  
  if (out == NULL) {
    printf("encryptRC4(): Error al abrir el archivo donde se guarda el cifrado\n");
		exit(-1);
  }
  for(i = 0; i < ciphertextLength; i++){
  	fprintf(out, "%.2x ", ciphertext[i]);	
  }
  fprintf(out, "\n");
  
  free(plaintext);
  free(ciphertext);
  fclose(in);  
  fclose(out);
}

void decryptRC4(char * filenameIn, char * filenameOut){
	FILE * in, * out;
	EVP_CIPHER_CTX *ctx;
	char * plaintext,  c;
	unsigned char * ciphertext;
	long i, inputSize;
	int plaintextLength, tmpLength;

	unsigned char key[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char iv[16] = {0,0,0,0,0,0,0,0};

	in = fopen(filenameIn, "r");
	
	if(in == NULL){
		printf("decryptRC4(): Error al abrir el archivo a descifrar\n");
		exit(-1);
	}

	inputSize = 0;
	while((c = fgetc(in)) != EOF){
		if(c == ' '){
			inputSize++;	
		}
	}

	rewind(in);
	ciphertext = malloc(sizeof(unsigned char)* inputSize);
	
	unsigned char aux;
	int auxIndex = 0;
	i = 0;
	while((c = fgetc(in)) != EOF){
		if(auxIndex == 0){
			aux = hex2dec(c) << 4;
			ciphertext[i] = aux;
			auxIndex++;
		}else if(auxIndex == 1){
			aux = hex2dec(c);
			ciphertext[i] += aux;
			auxIndex++;
		}else{
			i++;
			auxIndex = 0;
		}
	}	

	plaintext = malloc((sizeof(char) * inputSize) + 1);

	ctx = EVP_CIPHER_CTX_new();
	EVP_DecryptInit_ex(ctx, EVP_rc4(), NULL, key, iv);

	if (!EVP_DecryptUpdate(ctx, plaintext, &plaintextLength, ciphertext, strlen(ciphertext))) {
    /* Error */
    EVP_CIPHER_CTX_free(ctx);
    return 0;
  }

  if (!EVP_DecryptFinal_ex(ctx, plaintext + plaintextLength, &tmpLength)) {
    /* Error */
    EVP_CIPHER_CTX_free(ctx);
    return 0;
  }

  plaintextLength += tmpLength;
  EVP_CIPHER_CTX_free(ctx);

  out = fopen(filenameOut, "wb");
  
  if (out == NULL) {
    printf("decrypt(): Error al abrir el archivo donde se guarda el descifrado\n");
		exit(-1);
  }
  for(i = 0; i < plaintextLength; i++){
  	fprintf(out, "%c", plaintext[i]);	
  }
  
  free(plaintext);
  free(ciphertext);
  fclose(in);  
  fclose(out);	
}