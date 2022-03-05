#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void createComb(char pos[][4]);
void makeCode(char* secretCode);
void guess(char guessCode[]);
void codeCheck(char* secretCode, char* guessCode, int *blackPeg, int *whitePeg);
void displayGuess(char guessCode[4], int blackPeg, int whitePeg);
