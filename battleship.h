#ifndef BATTLESHIP_H
#define BATTLESHIP_H

int findpoints(char *input, int *points);
int boardinit(char board[9][9]);
void display(char board[9][9]);
int setship(char board[9][9], char ship);
int checkhit(char board[9][9], int *coord);
int fire(char board[9][9], char* status, int *coord);

#endif
