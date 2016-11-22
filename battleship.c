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

        if(strlen(input)==3){

            for(i=0;i<strlen(input);i++){
                
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
                }
                else if(i==1&&input[i]!='-'){
                           points[0]=-1;
                           points[1]=-1;
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
                        default:
                            points[1]=-1;
                            break;
                    }

              }
         }
    } 
        
    else {
         points[0]=-1;
         points[1]=-1; 
         return 0;    
    }
}


char** boardinit(void)
{
	int i,j;
	char** board = malloc(17*sizeof( char*));
	for(i=0; i<17; i++)
	{
		board[i] = malloc(17*sizeof(char));
	}

	for(i=0; i<17; i++)
	{
		for(j=0; j<17; j++)
		{
			if(i%2 == 1)
			{
				board[i][j]='-';
			}
			else
			{
				if(j%2 == 1) board[i][j]=' ';
				else board[i][j]='|';
			}
		}
	}
	return board;
}

void display(char** board)
{
	int i,j;
	printf("   A B C D E F G H \n");
	for(i=0; i<17; i++)
	{
		if(i%2 == 0) printf("%d ",i/2);
		else printf("  ");
		for(j=0; j<17; j++)
		{
			printf("%c",board[i][j]);
		}
		printf("\n");
     
    }
    return;
}

//char** setship(char **board, char input)
//{
	
//}


    

