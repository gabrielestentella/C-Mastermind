#include "manageCode.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void createComb(char pos[][4]) //creates all the possible combinations made up of 4 colors among the 6 available
{
    char alfabeto[] = "RGBYOP"; // available colours

    int len = 6; //number of colours
    int index[len];
    int gen[4];
    unsigned int n = 0;

    
    for (int i = 0; i < len; i++){
        index[i]=i;
    }
    
    for (int col = 0; col < 4; col++){
        gen[col] = 0;
    }
    
    char conc[5] = {0};
    do{
        for (int col = 0; col < 4; col++){
            conc[col]=alfabeto[gen[col]];
        }
        for(int i = 0; i < 4; i++){
            pos[n][i] = conc[i];
        }
        n++;

        gen[3]++;
        for (int col = 3; col > 0; col--){
            if (gen[col] == len){
                gen[col] = 0;
                gen[col-1]++;
            }
        }
    }while (gen[0] < len);
}

void makeCode(char* secretCode) //creates a random code
{
    int i, randColor;
    srand((unsigned)time(NULL));
    
    char colors [6] = {'R', 'G', 'B', 'Y', 'O', 'P'};
    
    for(i = 0; i < 4; i++){
        randColor = rand() % 6;
        secretCode[i] = colors[randColor];
    }
}

void guess(char guessCode[])
{
    printf("\nInserisci il tuo tentativo:\n");
    fflush(stdin);
    scanf("%c%c%c%c", &guessCode[0], &guessCode[1], &guessCode[2], &guessCode[3]);
}

void codeCheck(char* secretCode, char* guessCode, int *blackPeg, int *whitePeg)
{
    /*verification of the entered code (comparison with the secret code), it returns the number of correct colors
     in the right position (blackPeg) and the number of correct colors but in the wrong position (whitePeg)*/
    
    int i, j, checkSecret[4] = {1,1,1,1}, checkGuess[4] = {1,1,1,1};
    *blackPeg = *whitePeg = 0;

    for(i=0; i<4; i++)
        if(guessCode[i] == secretCode[i])
        {
            ++*blackPeg;
            checkSecret[i] = checkGuess[i] = 0;
        }

    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
            if(secretCode[j] == guessCode[i] &&  checkGuess[i]  &&  checkSecret[j]  &&  i != j)
            {
                ++*whitePeg;
                checkSecret[j] = checkGuess[i] = 0;
            }
}

void displayGuess(char guessCode[4], int blackPeg, int whitePeg)
{
    int i;
    printf("\n---------------------------------------\n");
    printf("Guess\t\t\t\t\tScore\n");
    for(int i = 0; i < 4; i++)
        printf("%c", guessCode[i]);
    printf("\t\t\t\t\t\t");
    for(i=0; i < blackPeg; i++)
        printf("B ");
    for(i=0; i < whitePeg; i++)
        printf("W ");
    printf("\n---------------------------------------\n");
    printf("\n\n");
}
