#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

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
	int port,x,y;
	struct hostent *server;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE];
	int n;
	int time_to_exit=0;

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


	/****************************************/
	/* Main client loop 			*/
	/****************************************/

	while(1) {

		/* Prompt for a message */
		printf("Please enter a message to send: ");
		memset(buffer,0,BUFFER_SIZE);

		/* Read message */
		fgets(buffer,BUFFER_SIZE-1,stdin);

		if (!strncmp(buffer,"bye",3)) time_to_exit=1;

		/* Write to socket using the "write" system call */
		n = write(socket_fd,buffer,strlen(buffer));
		if (n<0) {
			fprintf(stderr,"Error writing socket! %s\n",
				strerror(errno));
		}

		/* Clear buffer and read the response from the server */
		memset(buffer,0,BUFFER_SIZE);
		n = read(socket_fd,buffer,BUFFER_SIZE-1);
		if (n<0) {
			fprintf(stderr,"Error reading socket! %s\n",
				strerror(errno));
		 
        }
              
		/* Print the response we got */
		printf("Received back from server: %s\n\n",buffer);

		if (time_to_exit) break;

	}

	/* All finished, close the socket/file descriptor */
	close(socket_fd);

	return 0;
}
int* find points(char *input){
        int i;
        int points[2];

        if(strlen(input)==3){

            for(i=0;i<strlen(buffer);i++){
                
                if(i==0){
                    switch (buffer[i]) {
                        case '1':
                            points[0]=1;
                            break;
                        case '2':
                            points[0]=2;
                            break;
                        case '3':
                            points[0]=3;
                            break
                        case '4':
                            points[0]=4;
                            break;
                        case '5':
                            points[0]=5;
                            break;
                        case '6':
                            points[0]=6;
                            break;
                        case '7':
                            points[0]=7;
                            break
                        case '8':
                            points[0]=8;
                            break
                        case '9':
                            points[0]=9;
                            break;
                        default:
                            points[0]=99;
                            break;

                    }
              }
              else if(i==1&&buffer[i]!='-'){
                                 
                                     
                    }

              }
              else if(i==2){
                    switch (buffer[i]) {


                    }

              }


}
