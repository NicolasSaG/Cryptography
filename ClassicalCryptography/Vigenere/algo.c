#include <stdio.h>

void trial_division1(int n) {
    int d;
    for (d = 2; d * d <= n; d++) {
        printf("trial:%d\n", d);
        while (n % d == 0) {
            printf("%d\n", d);
            n /= d;
        }
    }
    if (n > 1)
        printf("%d\n", d);
}

void trial_division2(long long n) {
    int d;
    while (n % 2 == 0) {
        printf("%d\n", 2);
        n /= 2;
    }
    for (d = 3; d * d <= n; d += 2) {
        printf("wheel:%d\n", d);
        while (n % d == 0) {
            printf("%d\n", d);
            n /= d;
        }
    }
    if (n > 1)
        printf("%d\n", n);
}

int multiplicar(int x, int y){
    if(y == 0)
        return 0;
    int z = multiplicar(x, y/2);
    printf("x=%d , y=%d, z =%d\n",x,y, z);
    if(y&1){
        return x + 2*z;
    }else{
        if(y == 34){

            printf("x%d, y%d, z=%d 2z= %d\n",x,y,z, 2*z);
        }
        return 2*z;
    }
}

int main(int argc, char const *argv[])
{
    //printf("trial divsion\n");
    //trial_division1(100);
    //printf("wheel factorization\n");
    //trial_division2(100);
    printf("%d\n", multiplicar(9,34));

    printf("%d\n", multiplicar(9,35));
    return 0;   
}