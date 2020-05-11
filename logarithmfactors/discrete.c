#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <openssl/bn.h>
long powmod(long x, long y, long p) { 
    long res = 1;  // Initialize result 
  
    x = x % p;  // Update x if it is more than or 
                // equal to p 
    while (y > 0) { 
        // If y is odd, multiply x with result 
        if (y & 1) 
            res = (res*x) % p; 
  
        // y must be even now 
        y = y>>1; // y = y/2 
        x = (x*x) % p; 
    } 
    return res; 
} 

long discreteLogarithm(long a, long m, long res){
    long potencia = 0;
    long i, j;
    long n = sqrt(m) + 1;
    long arr [n];
    for(i = n; i >= 1 ; i--){
        arr[i-1] = powmod (a, i * n, m);
    }

    for (j = 0; j < n; j++) { 
        // Calculate (a ^ j) * b and check 
        // for collision 
        int cur = (powmod (a, j, m) * res) % m; 
  
        // If collision occurs i.e., LHS = RHS 
        for(i = 0; i < n; i++){
           if(cur == arr[i]){
                potencia = (i+1) * n - j;
                // Check whether ans lies below m or not 
                if (potencia < m) 
                    return potencia; 
           } 
        }
    } 
    return 0;
}

int main(int argc, char const *argv[]){
    long i;
    long a, m, res;
    a = 3;
    m = 500000009;
    res = 406870124;
    
    i = discreteLogarithm(a, m, res);

    printf("%ld^xmod%ld = %ld; x =%ld\n", a, m, res, i);
    return 0;
}
