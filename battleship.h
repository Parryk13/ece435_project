#ifndef BATTLESHIP_H
#define BATTLESHIP_H

int findpoints(char *input, int *points);
int boardinit(char** board);
void display(char** board);
int setship(char **board, char ship);

#endif
