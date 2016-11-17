#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>

#include <netdb.h>

int* find points(char *input){
        int i;
        int points[2];

        if(strlen(input)==3){

            for(i=0;i<strlen(input);i++){
                
                if(i==0){
                    switch (input[i]) {
                       /* case '0':
                            points[0]=0;
                            break;*/
                        case '1':
                            points[0]=0;
                            break;
                        case '2':
                            points[0]=1;
                            break
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
                            break
                        case '7':
                            points[0]=6;
                            break
                        case '8':
                            points[0]=7;
                            break;
                        case '9':
                            points[0]=8;
                            break;
                        default:

                            points[0]=99;
                            break;

                    }
              }
              else if(i==1&&input[i]!='-'){
                           points[0]=99;
                           points[1]=99;
                           return points;
                    }

              }
              else if(i==2){
                    switch (buffer[i]) {
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
                            break
                        case 'h':
                            points[1]=7;
                            break;
                        default:
                            points[1]=99;
                            break;
                    }

              }
         }  
    }
    else {
        points[0]=99;
        points[1]=99;
    }
    return points;            
}
