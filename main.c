#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

int main()
{
    char secret[5], guess[10], replay;
    int exact, wrong, attempt, win, hintUsed;

    srand(time(NULL));

    do
    {
        attempt = 0;
        win = 0;
        hintUsed = 0;

        printf("\nWelcome to the Code Guess Game!\n");
        printf("1. Guess the 4-digit secret code.\n");
        printf("2. You have 8 valid attempts.\n");
        printf("3. Repeated digits are not allowed.\n");
        printf("4. Enter H to request a hint (once per game).\n");

        generatesecret(secret);

        while(attempt < 8)
        {
            printf("\nAttempt %d/8\n", attempt + 1);
            printf("Enter your guess : ");

            if(fgets(guess, sizeof(guess), stdin) == NULL)
                return 0;

            if(strchr(guess, '\n') == NULL)
            {
                int ch;
                while((ch = getchar()) != '\n' && ch != EOF);

                printf("Input too long! Try again.\n");
                continue;
            }

            guess[strcspn(guess, "\n")] = '\0';

            // Hint feature
            if(strcmp(guess, "H") == 0 ||
               strcmp(guess, "h") == 0)
            {
                if(!hintUsed)
                {
                    int pos = rand() % 4;

                    printf("Hint: Position %d contains digit %c\n",
                           pos + 1, secret[pos]);

                    hintUsed = 1;
                }
                else
                {
                    printf("You have already used your hint!\n");
                }

                continue;
            }

            // Validate guess
            if(!validateGuess(guess))
            {
                printf("Invalid guess! Try again.\n");
                continue;
            }

            attempt++;

            compareCode(secret, guess, &exact, &wrong);

            printf("Exact matches: %d\n", exact);
            printf("Wrong-position matches: %d\n", wrong);

            if(exact == 4)
            {
                printf("\nCongratulations! You found the code.\n");
                win = 1;
                break;
            }
        }

        if(!win)
            printf("\nYou lost! Secret code was: %s\n", secret);

        // Replay option
        printf("\nWould you like to play again? (Y/N): ");

        if(fgets(guess, sizeof(guess), stdin) == NULL)
            return 0;

        replay = guess[0];

        while(replay != 'Y' && replay != 'y' &&
              replay != 'N' && replay != 'n')
        {
            printf("Invalid choice! Enter Y or N: ");

            if(fgets(guess, sizeof(guess), stdin) == NULL)
                return 0;

            replay = guess[0];
        }

    } while(replay == 'Y' || replay == 'y');

    printf("\nThanks for playing!\n");

    return 0;
}

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

// Validate input
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
