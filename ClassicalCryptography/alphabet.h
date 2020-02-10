char * alphabet_GLOBAL;
int alphabetSize_GLOBAL;

char * addAlphabet(FILE * f);
int alphabetSize(FILE * f);
void printAlphabet();
int findValueBySymbol(char c);
char findSymbolByValue(int c);

//todos los caracteres de la palabra estan en el alfabeto
int validWord(char * word); 