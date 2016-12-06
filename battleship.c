#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <netdb.h>
#include "battleship.h"


int findpoints(char *input,int *points){
        int i;
        if(strlen(input)>=3){

            for(i=0;i<3;i++){

                if(i==0){
                    switch(input[i]){
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
                            points[0]=-1;
                            break;

                    }
                    printf("Point[0] set\n");
                }
                else if(i==1&&input[i]!='-'){
                           points[0]=-2;
                           points[1]=-2;
                           return -1;
                }
                printf("Character - recognized\n");


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
                        default:
                            points[1]=-3;
                            break;
                    }
                  printf("Point[1] set\n");
              }
         }
    }

    else {
         points[0]=-4;
         points[1]=-4;
         return 0;
    }
    return 0;
}


int boardinit(char board[9][9])
{
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
	int i,j;
	printf("   A B C D E F G H I\n");
	for(i=0; i<9; i++)
	{
		printf("%d ",i);
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
  char* input= NULL;
  char *direction = NULL;
  int point[2];
  int size,k;

//Changes the size depending on which ship
  switch(ship){
      case 'd':
          size=2;
          break;
      case 's':
          size=3;
          break;
      case 'c':
          size=3;
          break;
      case 'b':
          size=4;
          break;
      case 'C':
          size=5;
          break;
      default:
          return -1;
  }

  //prompt for start point
  printf("Enter start point for ship (in form letter-number): ");
  scanf("%s", input);
  if(findpoints(input, point) <0)
  {
        printf("Invalid Input");
        return -1;
  }
  //prompt for direction
  printf("Choose a direction (u for up, d for down, l for left, or r for right): ");
  scanf("%c", direction);
  if(*direction != 'u' && *direction != 'd' && *direction != 'l' && *direction != 'r')
  {
    printf("Invalid direction");
    return -1;
  }

  switch(*direction){
        case 'u':
            //checks that ship size doesn't overflow board
            if (point[0] - (size-1) < 0)
            {
              printf("Invalid placement");
              setship(board,ship);
              return 0;
            }
            //checks that ship placement doesn't overwrite ships
            for (k=0; k<size; k++){
              if(board[point[0] - k][point[1]] != ' '){
                printf("Invalid placement");
                setship(board,ship);
               return 0;
              }
            }
            for(k=0; k<size; k++)
            {
              board[point[0] - k][point[1]] = ship;
            }
            break;
      case 'd':
            if (point[0] + (size-1) > 7)
            {
              printf("Invalid placement");
              setship(board,ship);
              return 0;
            }
            //checks that ship placement doesn't overwrite ships
            for (k=0; k<size; k++){
              if(board[point[0] + k][point[1]] != ' '){
                printf("Invalid placement");
                setship(board,ship);
               return 0;
              }
            }
            for(k=0; k<size; k++)
            {
              board[point[0] + k][point[1]] = ship;
            }
            break;
      case 'l':
            if(point[1] - (size-1) < 0)
            {
                  printf("Invalid placement");
                  setship(board,ship);
                 return 0;
            }
            for( k=0; k<size; k++)
            {
                  if(board[point[0]][point[1] - k] != ' '){
                        printf("Invalid placement");
                        setship(board,ship);
                        return 0;
                  }
            }
            for( k=0; k<size; k++)
            {
                  board[point[0]][point[1] - k] = ship;
            }
            break;
      case 'r':
            if(point[1] + (size-1) > 7)
            {
                  printf("Invalid placement");
                  setship(board,ship);
                  return 0;
            }
            for( k=0; k<size; k++)
            {
                  if(board[point[0]][point[1]+k] != ' '){
                        printf("Invalid placement");
                        setship(board,ship);
                        return 0;
                  }
            }
            for( k=0; k<size; k++)
            {
                  board[point[0]][point[1]+k] = ship;
            }
            break;
      }
      return 0;
}
