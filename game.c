#include <stdlib.h>
#include <string.h>
#include "game.h"

// Generate secret code
void generatesecret(char secret[])
{
    int digit, i, j, flag;

    for(i = 0; i < 4; i++)
    {
        do
        {
            digit = rand() % 10;
            flag = 0;

            for(j = 0; j < i; j++)
            {
                if(digit + '0' == secret[j])
                {
                    flag = 1;
                    break;
                }
            }

        } while(flag == 1);

        secret[i] = digit + '0';
    }

    secret[4] = '\0';
}

// Validate user guess
int validateGuess(char guess[])
{
    int i, j;

    if(strlen(guess) != 4)
        return 0;

    for(i = 0; i < 4; i++)
    {
        if(guess[i] < '0' || guess[i] > '9')
            return 0;
    }

    for(i = 0; i < 4; i++)
    {
        for(j = i + 1; j < 4; j++)
        {
            if(guess[i] == guess[j])
                return 0;
        }
    }

    return 1;
}

// Compare secret and guess
void compareCode(char *secret, char *guess,
                 int *exact, int *wrong)
{
    char *s;
    int i = 0, j;

    *exact = 0;
    *wrong = 0;

    while(*guess != '\0')
    {
        s = secret;
        j = 0;

        while(*s != '\0')
        {
            if(*guess == *s)
            {
                if(i == j)
                    (*exact)++;
                else
                    (*wrong)++;

                break;
            }

            s++;
            j++;
        }

        guess++;
        i++;
    }
}
