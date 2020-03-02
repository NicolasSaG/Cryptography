//valores obtenidos de k al hacerle la permutacion y compresion y shifts circulares;
int k1;
int k2;

char encodeDESSimplified(unsigned char c, int n, int initialPermutation[n]);
void findKn(int k, int n, int permutation[n]);
int circularOneLeftShift(int k);
int permutateDataBitLevel(int n, int permutation[n], int data);
int permutationCompression(int n, int permutation[n], int data, int pos);
int getBitValue(int data, int bit);