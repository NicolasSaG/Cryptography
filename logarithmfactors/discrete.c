#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openssl/bn.h>

BIGNUM * discreteLogarithm(BIGNUM * a, BIGNUM * m, BIGNUM * res);
void printBN(BIGNUM * b);
BIGNUM * str2bn(char * s);

int main(int argc, char const *argv[]){
    char * aString = "11";
    char * mString = "1009";
    char * resString = "400";
    
    BIGNUM * a = str2bn(aString);
    BIGNUM * m = str2bn(mString);
    BIGNUM * res = str2bn(resString);
    BIGNUM * i = BN_new();
    
    i = discreteLogarithm(a, m, res);

    return 0;
}

BIGNUM * discreteLogarithm(BIGNUM * a, BIGNUM * m, BIGNUM * res){
    char * zeroString [2] = "0";
    char * oneString [2] = "1";
    BIGNUM * zero = str2bn(zeroString);
    BIGNUM * one = str2bn(oneString);
    BN_CTX * contexto = BN_CTX_new();

    BIGNUM * potencia = BN_new();
    BIGNUM * iBN = BN_new(), * jBN = BN_new();
    BIGNUM * n = BN_new();
    BN_mod_sqr(n, m, contexto);
    BN_add(n, n, one);

    BIGNUM * arr [];
    long i, j;
    for(iBN = BN_copy(iBN, zero), i = 0; BN_cmp(iBN, n) == -1;  BN_add(iBN, iBN, one), i++){
        BIGNUM * aux = BN_new();
        BN_mul(aux, iBN, n, contexto);

        arr[i] = BN_new();
        BN_mod_exp(arr[i], a, aux, m, contexto);
    }       

    for(j = 0; j < i; j++){
        printBN(arr[i]);
        printf("\n");
    }
    // for(i = n; i >= 1 ; i--){
    //     arr[i-1] = powmod (a, i * n, m);
    // }

    // for (j = 0; j < n; j++) { 
    //     // Calculate (a ^ j) * b and check 
    //     // for collision 
    //     int cur = (powmod (a, j, m) * res) % m; 
  
    //     // If collision occurs i.e., LHS = RHS 
    //     for(i = 0; i < n; i++){
    //        if(cur == arr[i]){
    //             potencia = (i+1) * n - j;
    //             // Check whether ans lies below m or not 
    //             if (potencia < m){
    //                 BN_CTX_free(contexto);
    //                 return potencia; 
    //     }
    //             }
    //        } 
    // } 
    return one;
}

//imprimir en decimal un bignum
void printBN(BIGNUM * b){
    char * s;
    s = BN_bn2dec(b);
    printf("%s", s);
}

BIGNUM * str2bn(char * s){
    BIGNUM * b;
    b = BN_new();
    BN_dec2bn(&b, s);
    return b;
}

