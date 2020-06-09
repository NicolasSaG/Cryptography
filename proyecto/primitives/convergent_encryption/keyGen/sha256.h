

//gcc sha256.c -lssl -lcrypto -o sha256


//tam max archivo 2^64 - 1
//rendimiento Aprox 139 MiB/s
//256 bits
unsigned char * secureSHA256(char * filename);