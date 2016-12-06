#ifndef BATTLESHIP_H
#define BATTLESHIP_H

int findpoints(char *input, int *points);
int boardinit(char board[8][8]);
void display(char board[8][8]);
int setship(char board[8][8], char ship);

#endif
