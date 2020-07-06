/*
 * Author: Karthikeyan Venkatram
 *
 * Description: simple example UDP server
 * usage: uftp_server <port>
 */

#include <stdio.h>      // i/o (fprintf, fopen, ect)
#include <stdlib.h> 
#include <string.h>     // bzero
#include <unistd.h>     // POSIX (fork, read, write, and other system calls)
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>      // getaddrinfo
#include <arpa/inet.h>

#define BUFSIZE 2000

/*
 * error - wrapper for perror
 */
void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char **argv) {
    int sockfd; /* socket */
    int portno; /* port to listen on */
    int clientlen; /* byte size of client's address */
    struct sockaddr_in serveraddr; /* server's addr */
    struct sockaddr_in clientaddr; /* client addr */
    struct hostent *hostp; /* client host info */
    char *hostaddrp; /* dotted decimal host addr string */
    int optval; /* flag value for setsockopt */
    int n; /* message byte size */
    char recv_buf[BUFSIZE]; /*recieving buffer*/
    char send_buf[BUFSIZE]; /*sending buffer*
	

    /* check cmd line args */
	if (argc != 2){
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
	}
	portno = atoi(argv[1]);

	/* socket: create the parent socke t*/
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0){
		error("ERROR opening socket");
	}
	
	/* setsockopt: Handy debugging trick that lets 
    * us rerun the server immediately after we kill it; 
    * otherwise we have to wait about 20 secs. 
    * Eliminates "ERROR on binding: Address already in use" error. 
    */
    optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(const void *)&optval , sizeof(int));
        
    

    
    // build the server's Internet address
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)portno);
    
     
    // bind: associate the parent socket with a port 
    if (bind(sockfd, (struct sockaddr *) &serveraddr,sizeof(serveraddr)) < 0){
        error("ERROR on binding");
    }

    clientlen = sizeof(clientaddr);

    // loop and wait for connection
    while(1){
        // recieve UPD datagram
        bzero(recv_buf, BUFSIZE);
        n = recvfrom(sockfd, recv_buf, BUFSIZE, 0, (struct sockaddr *) &clientaddr, &clientlen);
        
        // extract client information
        hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        if (hostp == NULL){
            error("ERROR on gethostbyaddr");
        }
        hostaddrp = inet_ntoa(clientaddr.sin_addr);
        if (hostaddrp == NULL){
            error("ERROR on inet_ntoa\n");
        }
        printf("server received datagram from %s (%s)\n",hostp->h_name, hostaddrp);
        printf("server received %ld/%d bytes: %s\n", strlen(recv_buf), n, recv_buf);


        // send response
        bzero(send_buf, BUFSIZE);

        strcpy(send_buf, "Hello ");
        strcat(send_buf, recv_buf);

        n = sendto(sockfd, send_buf, strlen(send_buf), 0, (struct sockaddr *) &clientaddr, sizeof(clientaddr));
        if (n < 0){
            error("Error in sendto");
        }
        printf("Sent Message\n");
    }

}

