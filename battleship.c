#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <netdb.h>
#include "battleship.h"


int findpoints(char *input, int *points){
        int i;
        if(strlen(input)>=3)
        {

            for(i=0;i<3;i++)
            {

                if(i==0)
                {
                    switch(input[i])
                    {
                        case '1':
                            points[0]=0;
                            break;
                        case '2':
                            points[0]=1;
                            break;
                        case '3':
                            points[0]=2;
                            break;
                        case '4':
                            points[0]=3;
                            break;
                        case '5':
                            points[0]=4;
                            break;
                        case '6':
                            points[0]=5;
                            break;
                        case '7':
                            points[0]=6;
                            break;
                        case '8':
                            points[0]=7;
                            break;
                        case '9':
                            points[0]=8;
                            break;
                        default:
                            return -1;
                            break;

                    }
                }
                else if(i==1&&input[i]!='-'){
                           points[0]=-2;
                           points[1]=-2;
                           return -1;
                }



                else if(i==2){
                    switch (input[i]) {
                        case 'a':
                            points[1]=0;
                            break;
                        case 'b':
                            points[1]=1;
                            break;
                        case 'c':
                            points[1]=2;
                            break;
                        case 'd':
                            points[1]=3;
                            break;
                        case 'e':
                            points[1]=4;
                            break;
                        case 'f':
                            points[1]=5;
                            break;
                        case 'g':
                            points[1]=6;
                            break;
                        case 'h':
                            points[1]=7;
                            break;
                        case 'i':
                            points[1]=8;
                            break;
                        case 'j':
                              points[1]=9;
                              break;
                        default:
                            return -1;
                    }
              }
         }
    }

    else {
         points[0]=-4;
         points[1]=-4;
         return -4;
    }
    return 1;
}


int boardinit(char board[9][9])
{
      //fill the board with ' ' space Characters
	int i,j;
	for(i=0; i<9; i++)
	{
    for(j=0; j<9; j++)
    {
      board[i][j] = ' ';
    }
  }
  return 0;
}

void display(char board[9][9])
{
      //print the board and populate it with the contents of board array
	int i,j;
	printf("   A B C D E F G H I \n");
	for(i=0; i<9; i++)
	{
		printf("%d ",i+1);
		for(j=0; j<9; j++)
		{
			printf("|%c",board[i][j]);
		}
		printf("|\n");

    }
    return;
}
int setship(char board[9][9], char ship)
{
  char input[12];
  char direction[4];
  int point[2];
  int size,k,test;

//Changes the size depending on which ship
  switch (ship)
  {
      case 'd':
          size=2;
           printf("Enter start point for your destroyer, size %d (in form number-letter): ",size);
          break;
      case 's':
          size=3;
           printf("Enter start point for your Submarine, size %d (in form number-letter): ",size);
          break;
      case 'c':
          size=3;
          printf("Enter start point for your cruiser, size %d (in form number-letter): ",size);
          break;
      case 'b':
          size=4;
          printf("Enter start point for your battleship, size %d (in form number-letter): ",size);
          break;
      case 'C':
          size=5;
          printf("Enter start point for your Carrier, size %d (in form number-letter): ",size);
          break;
      default:
          return -1;
  }

  //prompt for start point
 // printf("Enter start point for ship (in form number-letter): ");
  scanf("%s", input);
 // printf("Input:%s\n", input);
  test=findpoints(input,point);
  printf("return value of findpoints:%d\n",test);
  if (test <0)
  {
        printf("Invalid Input\n");
        setship(board,ship);
        return 0;
  }
  //prompt for direction
  printf("Choose a direction (u for up, d for down, l for left, or r for right): ");
  scanf("%s", direction);
  if (direction[0] != 'u' && direction[0] != 'd' && direction[0] != 'l' && direction[0] != 'r')
  {
    printf("Invalid direction, please try again \n");
    setship(board,ship);
    return 0;
}

  switch(direction[0]){
        case 'u':
            //checks that ship size doesn't overflow board
            if (point[0] - (size-1) < 0)
            {
              printf("Invalid placement, please try again \n");
              setship(board,ship);
              return 0;
            }
            //checks that ship placement doesn't overwrite ships
            for (k=0; k<size; k++){
              if(board[point[0] - k][point[1]] != ' '){
                printf("Invalid placement, please try again \n");
                setship(board,ship);
               return 0;
              }
            }
            //sets ships in ascending rows
            for(k=0; k<size; k++)
            {
              board[point[0] - k][point[1]] = ship;
            }
            break;
      case 'd':
            //checks ships don't overflow board
            if (point[0] + (size-1) > 8)
            {
              printf("Invalid placement, please try again \n");
              setship(board,ship);
              return 0;
            }
            //checks that ship placement doesn't overwrite ships
            for (k=0; k<size; k++){
              if(board[point[0] + k][point[1]] != ' '){
                printf("Invalid placement, please try again \n");
                setship(board,ship);
               return 0;
              }
            }
            //ships placed in descending rows
            for(k=0; k<size; k++)
            {
              board[point[0] + k][point[1]] = ship;
            }
            break;
      case 'l':
            //checks that ship placement doesn't overflow board
            if(point[1] - (size-1) < 0)
            {
                  printf("Invalid placement, please try again \n");
                  setship(board,ship);
                 return 0;
            }
            //checks that ship placement doesn't overwrite ships
            for( k=0; k<size; k++)
            {
                  if(board[point[0]][point[1] - k] != ' '){
                        printf("Invalid placement, please try again \n");
                        setship(board,ship);
                        return 0;
                  }
            }
            //sets ships in ascending column
            for( k=0; k<size; k++)
            {
                  board[point[0]][point[1] - k] = ship;
            }
            break;
      case 'r':
            //checks that ship placement doesn't overflow board
            if(point[1] + (size-1) > 8)
            {
                  printf("Invalid placement, please try again \n");
                  setship(board,ship);
                  return 0;
            }
            //checks that ship placement doesn't overwrite ships
            for( k=0; k<size; k++)
            {
                  if(board[point[0]][point[1]+k] != ' '){
                        printf("Invalid placement, please try again \n");
                        setship(board,ship);
                        return 0;
                  }
            }
            //places ships in descending columns
            for( k=0; k<size; k++)
            {
                  board[point[0]][point[1]+k] = ship;
            }
            break;
      }
      return 0;
}

char checkhit(char board[9][9], int *coord){
      int i, j;
      //checks if oponents firing coordinates has an empty space
      if(board[coord[0]][coord[1]] == ' '){
            printf("Miss at [%d][%d]\n", coord[0], coord[1]);
            //play board coordinates are set to miss marker
            board[coord[0]][coord[1]] = 'O';
            //returns "miss" value
            return 1;
      }
      //checks if a hit was already recorded
      else if(board[coord[0]][coord[1]] == 'X'){
            printf("Miss at [%d][%d]\n", coord[0], coord[1]);
            return 2;
      }
      else if(board[coord[0]][coord[1]] == 'O'){
            printf("Miss at [%d][%d]\n", coord[0], coord[1]);
            return 0;
      }
      else{
            //play board coordinates are set to hit marker
            board[coord[0]][coord[1]] = 'X';
            printf("Hit at [%d][%d]\n", coord[0], coord[1]);
            //checks whole board for ship values
            for(i=0; i<9; i++){
                  for(j=0; j<9; j++){
                        //if ship spaces remain, returns hit value
                        if(board[i][j] != 'X' && board[i][j] != 'O' && board[i][j] != ' ') return 3;
                  }
            }
            //if no ship spaces remain, return game over value
            printf("You lost! Get 'em next time\n'");
            return 4;
      }
}

int fire(char board[9][9], char* status, int *coord){
      //if status from checkhit is miss value
      if (status[0] == 1)
      {
            printf("Miss\n\n");
            board[coord[0]][coord[1]] = 'O';
            return 0;
      }
      if (status[0] == 2 || status[0]=0)

      {
            printf("Shot in repeat location\n\n");
            return 0;
      }
      //if status from checkhit is hit value
      if (status[0] == 3)
      {
            printf("Hit!\n\n");
            board[coord[0]][coord[1]] = 'X';
            return 0;
      }
      //if status from checkhit is game over value
      if (status[0] == 4)
      {
            printf("YOU WON!");
            return 1;
      }
      //if status from checkhit doesn't hit any known values
      printf("Status invalid\n\n");
      return -1;
}
