#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "battleship.h"

//Original code received from Vince Weaver and Modified for our purposes
#define BUFFER_SIZE	256

/* Default port to listen on */
#define DEFAULT_PORT	31337

int main(int argc, char **argv) {
	//FILE *pf;
	//char command[20];

	int socket_fd,new_socket_fd;
	struct sockaddr_in server_addr, client_addr;
	struct addrinfo hints,*server_info;
	int port=DEFAULT_PORT;
	int shots[2],temp;
    	//int points[2];
    //char input[3]={'5','-','a'};
	int n;
	socklen_t client_len;
	char buffer[BUFFER_SIZE];
	int result;
	//char** FiringBoard = NULL;
	char player1fire[9][9],player1hit[9][9];

	printf("Starting server on port %d\n",port);

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	result=getaddrinfo("130.111.248.75","31337",&hints,&server_info);
	if (result<0) {
		fprintf(stderr,"Error getaddrinfo!\n");
		return -1;
	}

	/* Open a socket to listen on */
	/* AF_INET means an IPv4 connection */
	/* SOCK_STREAM means reliable two-way connection (TCP) */
	socket_fd = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
	if (socket_fd<0) {
		fprintf(stderr,"Error opening socket! %s\n",
			strerror(errno));
		return -1;
	}

	/* Set up the server address to listen on */
	memset(&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	/* Convert the port we want to network byte order */
	server_addr.sin_port=htons(port);


	/* Bind to the port */
	if (bind(socket_fd, server_info->ai_addr,server_info->ai_addrlen)) {
		fprintf(stderr,"Error binding! %s\n", strerror(errno));
		return -1;
	}

	/* Tell the server we want to listen on the port */
	/* Second argument is backlog, how many pending connections can */
	/* build up */
	printf("waiting for player 2\n");
	listen(socket_fd,5);

	/* Call accept to create a new file descriptor for an incoming */
	/* connection.  It takes the oldest one off the queue */
	/* We're blocking so it waits here until a connection happens */
	client_len=sizeof(client_addr);
	new_socket_fd = accept(socket_fd,
		(struct sockaddr *)&client_addr,&client_len);
	if (new_socket_fd<0) {
		fprintf(stderr,"Error accepting! %s\n",strerror(errno));
	}
	printf("connected to player 2\n");
	restart:
	//let players setup their boards
	boardinit(player1hit);
	boardinit(player1fire);
	printf("boards initialized\n");
	display(player1hit);
	setship(player1hit, 'b');
	display(player1hit);
	setship(player1hit, 'C');
	display(player1hit);
	setship(player1hit, 's');
	display(player1hit);
	setship(player1hit, 'd');
	display(player1hit);
	setship(player1hit, 'c');
	display(player1hit);
	while(1) {
		//hit round for player 1
		display(player1fire);
            printf("--------------------------\n");
            display(player1hit);
		printf("waiting for player 2 to fire\n");
		/* Someone connected!  Let's try to read BUFFER_SIZE-1 bytes */
		memset(buffer,0,BUFFER_SIZE);
		n = read(new_socket_fd,buffer,(BUFFER_SIZE-1));
		if (n==0) {
			fprintf(stderr,"Connection to client lost\n\n");
			break;
		}
		else if (n<0) {
			fprintf(stderr,"Error reading from socket %s\n",
				strerror(errno));
		}

		/* Print the message we received */
		printf("shot from player 2\n"); //got shot from player
		findpoints(buffer,shots);
		memset(buffer,0,BUFFER_SIZE);
		system("clear"); //clear screen so their isnt multiple screens
		buffer[0] = checkhit(player1hit,shots); //run checkhit to see if we were hit
		display(player1fire); //print display
		printf("--------------------------\n");
		display(player1hit);
		n = write(new_socket_fd,buffer,strlen(buffer));
		if (n<0) {
			fprintf(stderr,"Error writing. %s\n",
				strerror(errno));
		}
		if(buffer[0]==4)
		{ //check to see if we lost
			printf("would you like to play again? ");
			memset(buffer,0,BUFFER_SIZE);
			scanf("%s",buffer);
			if (!strncmp(buffer,"yes",3)) goto restart;
			else break;
		}

		/* Send a response */

		if (n<0) {
			fprintf(stderr,"Error writing. %s\n",
				strerror(errno));
		}
		printf("enter firing cordinates: "); //begining of player 1 firing round
		scanf("%s",buffer);
		while (findpoints(buffer,shots)<0) {
			printf("you're an idiot put in correct cordinates\n");
			memset(buffer,0,BUFFER_SIZE);
			scanf("%s",buffer);
		}
		n = write(new_socket_fd,buffer,strlen(buffer)); //send coordinates
		n = read(new_socket_fd,buffer,(BUFFER_SIZE-1)); //gets back ack
		system("clear");
		temp = fire(player1fire,buffer,shots); //put ack into fire and modify buffer
		if(temp>0)
		{//check to see if player 1 won
			printf("would you like to play again?");
			memset(buffer,0,BUFFER_SIZE);
			scanf("%s",buffer);
			if (!strncmp(buffer,"yes",3)) goto restart;
			else break;
			//loop back to top and repeat until game is over
		}
	}

	printf("Exiting server\n\n");

	/* Try to avoid TIME_WAIT */
	sleep(1);

	/* Close the sockets */
	close(new_socket_fd);
	close(socket_fd);

	return 0;
}
