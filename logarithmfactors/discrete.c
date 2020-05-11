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
int main(int argc, char const *argv[]){
    long i;
    long a, m, res;
    a = 3;
    m = 500000009;
    res = 406870124;
    for(i = 0; i < m; i ++){
        if(powmod(a, i, m) == res){
            printf("i = %ld\n", i);
            break;
        }
    }
    printf("%ld^xmod%ld = %ld; x =%ld\n", a, m, res, i);
    return 0;
}
