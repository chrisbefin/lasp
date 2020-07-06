/*
 * Author: Karthikeyan Venkatram
 *
 * Description: simple UDP client example
 * usage: uftp_client <host> <port>
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

#define MSGSIZE   1024
#define INPUTSIZE 1024

void error(char *msg) {
    perror(msg);
    exit(0);
}


int main(int argc, char **argv){
    // Declare Vars
    int sockfd, portno, n;
    int serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;
    char input_buf[INPUTSIZE];
    char recv_buf[MSGSIZE];

    // Check command line args
    if (argc != 3){
        fprintf(stderr, "usage: %s <hostname <port>\n", argv[0]);
        exit(0);
    }


    hostname = argv[1];
    portno = atoi(argv[2]);

    // create a socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket:");
    }

    // gethostbyname: get the server's DNS entry
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0);
    }
 
    // build the server's Internet address
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);
    serverlen = sizeof(serveraddr);


    // Ask for user message
    bzero(input_buf, INPUTSIZE);
    printf("Please enter a message\n");
    fgets(input_buf, INPUTSIZE, stdin);


    // Send message to the server
    n = sendto(sockfd, input_buf, strlen(input_buf), 0, (const struct sockaddr *) &serveraddr, serverlen);
    if (n < 0){
        error("ERROR in sendto: ");
    }

    // wait to receive message
    bzero(recv_buf, MSGSIZE);
    n = recvfrom(sockfd, recv_buf, MSGSIZE, 0, (struct sockaddr *) &serveraddr, &serverlen);
    printf("\nRecieve message from server:%s", recv_buf);
    printf("\nGoodbye\n");
    close(sockfd);
    
}




