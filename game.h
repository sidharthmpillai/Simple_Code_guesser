
#ifndef GAME_H
#define GAME_H

void generatesecret(char secret[]);
int validateGuess(char guess[]);
void compareCode(char *secret, char *guess,
                 int *exact, int *wrong);

#endif
