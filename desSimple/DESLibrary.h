//valores obtenidos de k al hacerle la permutacion y compresion y shifts circulares;
int k1;
int k2;

unsigned char encodeDESSimplified(unsigned char m);
unsigned char decodeDESSimplified(unsigned char c);
unsigned char changeLtoR(unsigned char c);
int makeRound(unsigned char c, int round);
void findKn(int k, int n, int permutation[n]);
int circularOneLeftShift(int k);
int permutationCompression(int n, int permutation[n], int data, int pos);
int permutationExpansion(int n, int permutation[n], int data, int sizeData);
int permutateDataBitLevel(int n, int permutation[n], int data);
int getBitValue(int data, int bit);
void printBinary(int n, int size);