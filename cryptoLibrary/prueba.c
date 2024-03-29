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


int generateCSPR();

unsigned char * genetareKey(int bytes);
void encryptRC4(char * filenameIn, char * filenameOut);
void decryptRC4(char * filenameIn, char * filenameOut);

void encrypt3DES(char * filenameIn, char * filenameOut);
void decrypt3DES(char * filenameIn, char * filenameOut);

void encryptAES192(char * filenameIn, char * filenameOut);
void decryptAES192(char * filenameIn, char * filenameOut);

int hex2dec(char hex);

int do_crypt(FILE *in, FILE *out, int do_encrypt);

int main(int argc, char const *argv[]){
	//crypto pseudo random
	int r = generateCSPR();
	printf("numero criptografico seguro: %d\n", r);

	//key generator
	unsigned char * key = genetareKey(128);
	for(int i = 0; i < 128; i++){
		if(i%16 == 0)
			printf("\n");
		printf("%.2x ", key[i]);
	}
	printf("\n");

	//STREAM CIPHERS
	//encrypt
	encryptRC4("texto1.txt", "texto1.rc4");
	//decrypt
	decryptRC4("texto1.rc4", "texto1RC4.txt");
	
	//BLOCK CIPHERS
	//3DES 
	FILE * a = fopen("texto1.txt", "rb");
	FILE * b = fopen("texto1.3des", "wb");
	do_crypt(a, b, 0);

	FILE * c = fopen("texto1.3des", "rb");
	FILE * d = fopen("texto13des.txt", "wb");
	do_crypt(c, d, 1);

	//encrypt3DES("texto1.txt", "texto1.3des");
	//decrypt3DES("texto1.3des", "texto13DES.txt");

	//AES192
	//encrypt3DES("texto1.txt", "texto1.aes");
	//decrypt3DES("texto1.aes", "texto1descifradoAES.txt");

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
	    exit(-1);
	}

	if (!EVP_EncryptFinal_ex(ctx, ciphertext + ciphertextLength, &tmpLength)) {
	    /* Error */
	    EVP_CIPHER_CTX_free(ctx);
	    exit(-1);
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
    	exit(-1);
  	}

  	if (!EVP_DecryptFinal_ex(ctx, plaintext + plaintextLength, &tmpLength)) {
    	/* Error */
    	EVP_CIPHER_CTX_free(ctx);
    	exit(-1);
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

void encrypt3DES(char * filenameIn, char * filenameOut){
	FILE * in, * out;
	EVP_CIPHER_CTX *ctx;
	char * plaintext,  c;
	unsigned char * ciphertext;
	long i, inputSize;
	int ciphertextLength, tmpLength;

	unsigned char key[21] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	in = fopen(filenameIn, "r");
	
	if(in == NULL){
		printf("encrypt3DES(): Error al abrir el archivo a cifrar\n");
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
	
	EVP_EncryptInit_ex(ctx, EVP_des_ede3(), NULL, key, NULL);

	if (!EVP_EncryptUpdate(ctx, ciphertext, &ciphertextLength, plaintext, strlen(plaintext))) {
	    /* Error */
	    EVP_CIPHER_CTX_free(ctx);
	}
	if (!EVP_EncryptFinal_ex(ctx, ciphertext + ciphertextLength, &tmpLength)) {
	    /* Error */
	    EVP_CIPHER_CTX_free(ctx);
	    exit(-1);
	}

	ciphertextLength += tmpLength;
	EVP_CIPHER_CTX_free(ctx);

	out = fopen(filenameOut, "wb");

	if (out == NULL) {
  	printf("encrypt3DES(): Error al abrir el archivo donde se guarda el cifrado\n");
	exit(-1);
	}
	for(i = 0; i < ciphertextLength; i++){
		fprintf(out, "%.2x ", ciphertext[i]);	
	}

	free(plaintext);
	free(ciphertext);
	fclose(in);  
  fclose(out);
}

void decrypt3DES(char * filenameIn, char * filenameOut){
	FILE * in, * out;
	EVP_CIPHER_CTX *ctx;
	char * plaintext,  c;
	unsigned char * ciphertext;
	long i, inputSize;
	int plaintextLength, tmpLength;

	unsigned char key[21] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	in = fopen(filenameIn, "r");
	
	if(in == NULL){
		printf("decrypt3DES(): Error al abrir el archivo a descifrar\n");
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
	EVP_CipherInit_ex(ctx, EVP_des_ede3(), NULL, key, NULL, 1);

	
	if (!EVP_CipherUpdate(ctx, plaintext, &plaintextLength, ciphertext, strlen(ciphertext))) {
    	/* Error */
    	EVP_CIPHER_CTX_free(ctx);
    	printf("error 1\n");
    	exit(-1);
  	}


  	if (!EVP_CipherFinal_ex(ctx, plaintext + plaintextLength, &tmpLength)) {
    	/* Error */
    	EVP_CIPHER_CTX_free(ctx);
    	printf("error 2\n");
    	exit(-1);
  	}


  	plaintextLength += tmpLength;
  	EVP_CIPHER_CTX_free(ctx);

  	out = fopen(filenameOut, "wb");
  
  	if (out == NULL) {
    	printf("decrypt3DES(): Error al abrir el archivo donde se guarda el descifrado\n");
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

void encryptAES192(char * filenameIn, char * filenameOut){
	FILE * in, * out;
	EVP_CIPHER_CTX *ctx;
	char * plaintext,  c;
	unsigned char * ciphertext;
	long i, inputSize;
	int ciphertextLength, tmpLength;

	unsigned char key[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	in = fopen(filenameIn, "r");
	
	if(in == NULL){
		printf("encryptAES192(): Error al abrir el archivo a cifrar\n");
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
	EVP_EncryptInit_ex(ctx, EVP_aes_192_ecb(), NULL, key, NULL);

	if (!EVP_EncryptUpdate(ctx, ciphertext, &ciphertextLength, plaintext, strlen(plaintext))) {
	    /* Error */
	    EVP_CIPHER_CTX_free(ctx);
	}
	if (!EVP_EncryptFinal_ex(ctx, ciphertext + ciphertextLength, &tmpLength)) {
	    /* Error */
	    EVP_CIPHER_CTX_free(ctx);
	    exit(-1);
	}

	ciphertextLength += tmpLength;
	EVP_CIPHER_CTX_free(ctx);

	out = fopen(filenameOut, "wb");

	if (out == NULL) {
  	printf("encryptAES192(): Error al abrir el archivo donde se guarda el cifrado\n");
	exit(-1);
	}
	for(i = 0; i < ciphertextLength; i++){
		fprintf(out, "%.2x ", ciphertext[i]);	
	}

	free(plaintext);
	free(ciphertext);
	fclose(in);  
  fclose(out);
}

void decryptAES192(char * filenameIn, char * filenameOut){
	FILE * in, * out;
	EVP_CIPHER_CTX *ctx;
	char * plaintext,  c;
	unsigned char * ciphertext;
	long i, inputSize;
	int plaintextLength, tmpLength;

	unsigned char key[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	in = fopen(filenameIn, "r");
	
	if(in == NULL){
		printf("decryptAES192(): Error al abrir el archivo a descifrar\n");
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
	EVP_DecryptInit_ex(ctx, EVP_aes_192_ecb(), NULL, key, NULL);

	if (!EVP_DecryptUpdate(ctx, plaintext, &plaintextLength, ciphertext, strlen(ciphertext))) {
    	/* Error */
    	EVP_CIPHER_CTX_free(ctx);
    	exit(-1);
  	}

  	if (!EVP_DecryptFinal_ex(ctx, plaintext + plaintextLength, &tmpLength)) {
    	/* Error */
    	EVP_CIPHER_CTX_free(ctx);
    	exit(-1);
  	}

  	plaintextLength += tmpLength;
  	EVP_CIPHER_CTX_free(ctx);

  	out = fopen(filenameOut, "wb");
  
  	if (out == NULL) {
    	printf("decryptAES192(): Error al abrir el archivo donde se guarda el descifrado\n");
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

int hex2dec(char hex){
	int d = 0;
	if(hex >= '0' && hex <= '9'){
		d = hex - '0';
	}else{
		d = hex - 'a' + 10;
	}
	return d;
}

int generateCSPR(){
	int result = 0;
	char  * num = malloc(sizeof(char) * 3);
	//inicializar
	BIGNUM * b = BN_new();
	//generar random de 24 bits
	int a = BN_rand(b, 24, 0, 0);
	//convertir BIGNUM a string y guardarla en un puntero
	num = BN_bn2dec(b);

	for(int j = 0; j < 3; j++){
		result = result * 10 + num[j] - '0';
	}
	//liberar memoria de BIGNUM
	BN_free(b);
	return result;
}

unsigned char * genetareKey(int bytes){
	unsigned char * key = malloc(sizeof(unsigned char) * bytes);
	int r = RAND_bytes(key, bytes);
	return key;
}

int do_crypt(FILE *in, FILE *out, int do_encrypt)
 {
     /* Allow enough space in output buffer for additional block */
     unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
     int inlen, outlen;
     EVP_CIPHER_CTX *ctx;
     /*
      * Bogus key and IV: we'd normally set these from
      * another source.
      */
     unsigned char key[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

     /* Don't set key or IV right away; we want to check lengths */
     ctx = EVP_CIPHER_CTX_new();

     /* Now we can set key and IV */
     EVP_CipherInit_ex(ctx, EVP_des_ede3(), NULL, key, NULL, do_encrypt);

     for (;;) {
         inlen = fread(inbuf, 1, 1024, in);
         if (inlen <= 0)
             break;
         if (!EVP_CipherUpdate(ctx, outbuf, &outlen, inbuf, inlen)) {
             /* Error */
             EVP_CIPHER_CTX_free(ctx);
             return 0;
         }
         fwrite(outbuf, 1, outlen, out);
     }
     if (!EVP_CipherFinal_ex(ctx, outbuf, &outlen)) {
         /* Error */
         EVP_CIPHER_CTX_free(ctx);
         return 0;
     }
     fwrite(outbuf, 1, outlen, out);

     EVP_CIPHER_CTX_free(ctx);
     return 1;
 }