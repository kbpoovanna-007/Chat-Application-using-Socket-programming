    #include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define CONNECTION_PORT 3500

int main()
{
    // create a socket with IPv4 domain and TCP protocol
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // set options for the socket
    int optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
      perror("Couldn't set options");
      exit(EXIT_FAILURE);
    }

    // initialize the server address structure
    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(CONNECTION_PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to the server address and port
    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr)) < 0) {
        perror("Couldn't bind socket");
        exit(EXIT_FAILURE);
    }

    // listen on the socket with a maximum of 4 requests
    if (listen(sockfd, 4) < 0) {
        perror("Couldn't listen for connections");
        exit(EXIT_FAILURE);
    }

    // accept connection signals from the client
    struct sockaddr_in cli_addr = {0};
    socklen_t clilen = sizeof(cli_addr);
    int client_sockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
    if (client_sockfd < 0) {
        perror("Couldn't establish connection with client");
        exit(EXIT_FAILURE);
    }
      char message[100];
       printf("\n\n_____________________\n");
      printf("Server has started...\n");
      printf("_____________________\n\n");

    while(1)
    {
        
    // receive data from the client
    char receive_buffer[100] = {0};
    read(client_sockfd, receive_buffer, sizeof(receive_buffer));

    if(strcmp(receive_buffer,"exit")==0)
    {
        send(client_sockfd, "Thank you", strlen(message), 0);
        break;
    }
    printf("Client: %s\n", receive_buffer);

    printf("You: ");
    // send data to the client
    fgets(message,sizeof(message),stdin);
     send(client_sockfd, message, strlen(message), 0);
     printf("\n");

    }
    printf("\n_____________________\n\n");
    // close all sockets created
    close(sockfd);
    close(client_sockfd);
    return 0;
