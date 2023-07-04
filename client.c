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

    // initialize the server address structure
    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(CONNECTION_PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // connect to the server
    if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Couldn't connect to the server");
        exit(EXIT_FAILURE);
    }
    printf("\n\n__________________________\n");
    printf("Enter exit to end the chat\n");
    printf("__________________________\n\n");
    char message[100];
    while(1)    
    {
        printf("You: ");
    // send data to the server
     fgets(message,sizeof(message),stdin);
     message[strcspn(message, "\n")] = '\0';
     write(sockfd, message, strlen(message));

    // receive data from the server
    char receive_buffer[100] = {0};
    read(sockfd, receive_buffer, sizeof(receive_buffer));
    printf("Server: %s\n", receive_buffer);

    if(strcmp(message,"exit")==0)break;
    }
     printf("\n__________________________\n\n");
    // close the socket connection
    close(sockfd);
    return 0;
}
