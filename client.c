#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "battleship.h"
#include <sys/socket.h>

#include <netdb.h>

/* Default port.  Must be from 1024 to 65536 for normal user */
#define DEFAULT_PORT	31337

#define BUFFER_SIZE	256

/* Default hostname */
#define DEFAULT_HOSTNAME	"127.0.0.1"

int main(int argc, char **argv) {
    int firing_range[72];
	int socket_fd;
      int shots[2];
	int port;
	struct hostent *server;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE];
	int n,temp;
      char player2hit[9][9],player2fire[9][9];

	port=atoi(argv[2]);//convert port string input to int and save as the port input

	/* Open a socket file descriptor */
	/* AF_INET means an IP network socket, not a local (AF_UNIX) one */
	/* There are other types you can open too */
	/* SOCK_STREAM means reliable two-way byte stream (TCP) */
	/* last argument is protocol subset.  We leave at zero */
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd<0) {
		fprintf(stderr,"Error socket: %s\n",
			strerror(errno));
	}

	printf("Connecting to server %s port %d\n",
		argv[1],port);

	/* Look up the server info based on its name */
	server=gethostbyname(argv[1]); //set server as input of argv1
	if (server==NULL) {
		fprintf(stderr,"ERROR!  No such host!\n");
		exit(0);
	}

	/* clear out the server_addr structure and set some fields */
	/* Set it to connect to the address and port of our server */
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;

	memcpy(&server_addr.sin_addr.s_addr,server->h_addr,
		server->h_length);
//something
	/* port should be in "network byte order" (big-endian) so convert */
	/* htons = host to network [byte order] short */
	server_addr.sin_port=htons(port);

	/* Call the connect system call to actually connect to server */
	if (connect(socket_fd,(struct sockaddr *) &server_addr,
		sizeof(server_addr)) < 0) {
		fprintf(stderr,"Error connecting! %s\n",
			strerror(errno));
		return -1;
	}
      restart:
      boardinit(player2hit);
	boardinit(player2fire);
	printf("boards initialized\n");
	display(player2hit);
	setship(player2hit, 'b');
	display(player2hit);
	setship(player2hit, 'C');
	display(player2hit);
	setship(player2hit, 's');
	display(player2hit);
	setship(player2hit, 'd');
	display(player2hit);
	setship(player2hit, 'c');

	/****************************************/
	/* Main client loop 			*/
	/****************************************/
      system("clear");
      display(player2fire);
      printf("--------------------------\n");
      display(player2hit);
	while(1) {


		/* Prompt for a message */
		printf("Enter cordinates to fire: ");
		memset(buffer,0,BUFFER_SIZE);

		/* Read message */
		scanf("%s",buffer);
            while (findpoints(buffer,shots)<0) {
			printf("you're an idiot put in correct cordinates\n");
			memset(buffer,0,BUFFER_SIZE);
			scanf("%s",buffer);
		}

		/* Write to socket using the "write" system call */
		n = write(socket_fd,buffer,strlen(buffer));
		if (n<0) {
			fprintf(stderr,"Error writing socket! %s\n",
				strerror(errno));
		}
            n = read(socket_fd,buffer,(BUFFER_SIZE-1));
            system("clear");
		temp = fire(player2fire,buffer,shots);
		if(temp>0)
		{
			printf("would you like to play again? ");
			memset(buffer,0,BUFFER_SIZE);
			scanf("%s",buffer);
			if (!strncmp(buffer,"yes",3)) goto restart;
			else break;
		}
            display(player2fire);
            printf("--------------------------\n");
            display(player2hit);
            printf("waiting for player 1 to fire");
            n = read(socket_fd,buffer,(BUFFER_SIZE-1));
            printf("\n");
            if (n==0) {
			fprintf(stderr,"Connection to client lost\n\n");
			break;
		}
		else if (n<0) {
			fprintf(stderr,"Error reading from socket %s\n",
				strerror(errno));
		}
            printf("shot from player 1\n");
		findpoints(buffer,shots);
		memset(buffer,0,BUFFER_SIZE);
            system("clear");
		buffer[0] = checkhit(player2hit,shots);
            display(player2fire);
            printf("--------------------------\n");
            display(player2hit);
            if(buffer[0]==4)
		{
			printf("would you like to play again? ");
			memset(buffer,0,BUFFER_SIZE);
			scanf("%s",buffer);
			if (!strncmp(buffer,"yes",3)) goto restart;
			else break;
		}

		/* Send a response */
		n = write(socket_fd,buffer,strlen(buffer));
		if (n<0) {
			fprintf(stderr,"Error writing. %s\n",
				strerror(errno));
		}
	}

	/* All finished, close the socket/file descriptor */
	close(socket_fd);

	return 0;
}
