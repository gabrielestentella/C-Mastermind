/*Gabriele Stentella
* UniMi
* a.a. 2021/22
*/

#include "manageCode.h"

#define NCOM 1296 //1296 = 6^4 = numbeer of possible combination
int main(int argc, const char * argv[])
{
    int option=1, blackPeg, whitePeg, wrongGuess, end = 0, score[NCOM], pun;
    char secretCode[4], guessCode[4], poss[NCOM][4];
    
    while(!end)
    {
        printf("\nMENU \nPress 1 to begin the game \nPress 2 to start the automatic solver \nPress 0 to exit\n\nColors available: [R]ed, [G]reen, [B]lue, [Y]ellow, [O]range, [P]urple\n\n");
        scanf("%d", &option);
        if(option == 1)
        {
            makeCode(secretCode);
            for(wrongGuess=1; wrongGuess<=15; wrongGuess++)
            {
                guess(guessCode);
                codeCheck(secretCode, guessCode, &blackPeg, &whitePeg);
                displayGuess(guessCode, blackPeg, whitePeg);
                if(blackPeg == 4)
                {
                    printf("You won!\n\n\n\n");
                    wrongGuess = 17;
                }
            }
            if(wrongGuess == 16)
                printf("\nYou lost!\nRight code: %s\n\n\n\n\n", secretCode);
        }
        
        else if(option == 2){
            
            printf("Insert a 4 colors code:\n");
            fflush(stdin);
            scanf("%c%c%c%c", &secretCode[0], &secretCode[1], &secretCode[2], &secretCode[3]);
            createComb(poss);
            
            guessCode [0] = 'R';
            guessCode [1] = 'R';
            guessCode [2] = 'G';
            guessCode [3] = 'G';
            
            for(wrongGuess=1; wrongGuess<=8; wrongGuess++)
            {
                codeCheck(secretCode, guessCode, &blackPeg, &whitePeg);
                displayGuess(guessCode, blackPeg, whitePeg);
                if(blackPeg == 4)
                {
                    printf("You won!\n\n\n\n");
                    wrongGuess = 10;
                }
                pun = blackPeg * 10 + whitePeg;
                
                for(int i = 0; i < NCOM; i++){
                    if(poss[i][0] == 'x')
                        continue;
                    codeCheck(guessCode, poss[i], &blackPeg, &whitePeg);
                    score[i] = blackPeg * 10 + whitePeg;
                }
                
                for(int i = 0; i < NCOM; i++){
                    /*I delete (marking with x) all the codes that would give a different score from the actual code if the actual code were the guess code (Knuth algorithm)*/
                    if(score[i] != pun){
                        poss[i][0] = 'x';
                        score[i] = -1;
                    }
                }
                
                guessCode[0] = 'a';
                
                for(int i = 0; i < NCOM && guessCode[0] == 'a'; i++){
                    if(score[i] != -1){
                        for(int j = 0; j < 4; j++){
                            guessCode[j] = poss[i][j];
                        }
                    }
                }
            }
            if(wrongGuess == 9){
                printf("\nYou lost!\nRight code:\n");
                for(int i = 0; i < 4; i++)
                    printf("%c", secretCode[i]);
            }
            
        }else{
            printf("Thanks for playing\n");
            end = 1;
        }
    }
    return 0;
}
