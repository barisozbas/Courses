#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 10000

int network_socket;
struct sockaddr_in client;
int client_s;
char ongoingMessage[250] = ""; // Message from client
char incomingMessage[250] = "";// Message from server

void connectServer() {
    // Connect server in here
    //socket
    network_socket = socket(AF_INET,SOCK_STREAM,0);
    // address of socket
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    client.sin_addr.s_addr = INADDR_ANY;

    client_s = connect(network_socket,(struct sockaddr *) &client,sizeof(client));


}

void handleConnection(int client_s) {
    // Exchange messages with server here
    if (client_s == -1) {
        printf("Failed to connect \n");
    }
    else {
        recv(network_socket, &incomingMessage, sizeof(incomingMessage),0);
        printf("%s\n",incomingMessage);

        recv(network_socket, &incomingMessage, sizeof(incomingMessage),0);
        printf("%s",incomingMessage);

		printf("Enter your answer: ");
        scanf("%s",ongoingMessage);
        printf("Your meal is being prepared... \n");
        send(network_socket, &ongoingMessage, sizeof(ongoingMessage),0);

        recv(network_socket, &incomingMessage, sizeof(incomingMessage),0);
        printf("%s\n",incomingMessage);
    }
}

int main() {
    connectServer();
    handleConnection(client_s);
    close(network_socket);
    exit(0);
}
