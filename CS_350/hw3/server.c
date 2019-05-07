#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "meal.h"
#include <sys/wait.h>

#define PORT 10000

int server_socket;
int client_socket;
struct sockaddr_in server; //Socket to listen connections
char ongoingMessage[250] = "Connected"; // Message from server
char ongoingMessage2[250] = "Your meal is ready!"; // Message from server
char incomingMessage[250] = ""; // Message from client

char MenuMessage[250] = {"Welcome to OzuRest! Please Pick your Order:\n1.Menemen \n2.Chicken Pasta \n3.Beef Steak \n4.Ali Nazik\n"}; //Pre determined message to be sent

void start_server() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    int true = 1;
    setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)); 
    bind(server_socket, (struct sockaddr*) &server, sizeof(server));
    
    listen(server_socket, 5);
}

void orderMeal(char* client_message) { 
   
    pid_t pid = fork();
	
    if (pid == 0) {
        int input = atoi(client_message);
        if(input == 1) {
            static char *argv[] = {"kitchen","0"};
            execv("kitchen",argv);
            exit(127);
        }
        if(input == 2) {
            static char *argv[] = {"kitchen","1"};
            execv("kitchen",argv);
            exit(127);
        }
        if(input == 3) {
            static char *argv[] = {"kitchen","2"};
            execv("kitchen",argv);
            exit(127);
        }
        if(input == 4) {
            static char *argv[] = {"kitchen","3"};
            execv("kitchen",argv);
            exit(127);
        }
    }
	
    else 
		waitpid(pid,0,0);
    
}

void accept_connection() {
	
    client_socket = accept(server_socket, NULL, NULL);
	printf("Server got connection from client\n");
	
}

void handle_connection(int client_socket) {
	
    if(client_socket == -1) {
        printf("Failed to connect \n");
    }
    else {
        send(client_socket, &ongoingMessage, sizeof(ongoingMessage), 0);
        send(client_socket, &MenuMessage, sizeof(MenuMessage), 0);
        recv(client_socket, &incomingMessage, sizeof(incomingMessage),0);
		
		if(incomingMessage == 1)
			printf("Customer wants: Menemen\n");
        
		if(incomingMessage == 2)
			printf("Customer wants: Chicken Pasta\n");
		
		if(incomingMessage == 3)
			printf("Customer wants: Beef Steak\n");
		
		if(incomingMessage == 4)
			printf("Customer wants: Ali Nazik\n");

        orderMeal(incomingMessage);

        send(client_socket, &ongoingMessage2, sizeof(ongoingMessage2), 0);
    }
}

int main() {
    start_server();
    printf("Started the server\n");
    while(1) {
        accept_connection();
        handle_connection(client_socket);
        close(server_socket);
        break;
    }
}