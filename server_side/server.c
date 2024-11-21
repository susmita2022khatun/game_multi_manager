#include "client_handler.h"

#define SERVERPORT 8080
#define SOCKETERROR (-1)
typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;


int main() {

    int server_socket, client_socket, addr_size;
    SA_IN server_addr, client_addr;

    char credentials[100];  
    char username[50], password[50];  
    size_t bytes_read;

    // Create the server socket
    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to create socket\n");

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVERPORT);

    // Bind the socket to the address and port
    check(bind(server_socket, (SA*)&server_addr, sizeof(server_addr)), "Failed to bind\n");

    check(listen(server_socket, 10), "Listen failed\n");

    printf("Server started. Waiting for connections...\n");

    while (1) {
        addr_size = sizeof(SA_IN);

        check(client_socket = accept(server_socket, (SA*)&client_addr, (socklen_t*)&addr_size), "Accept failed\n");
        printf("Client connected!\n");

        bytes_read = recv(client_socket, credentials, sizeof(credentials) - 1, 0);
        check(bytes_read, "Receive error");
        credentials[bytes_read] = '\0';

        sscanf(credentials, "%s %s", username, password);
        printf("Received credentials: Username='%s', Password='%s'\n", username, password);

        if (authenticate(username, password)) {
            send(client_socket, "OK", 2, 0);
            printf("User '%s' authenticated.\n", username);
        } else {
            send(client_socket, "Unauthorized", 12, 0);
            printf("Authentication failed for user '%s'.\n", username);
            close(client_socket);
            continue;
        }
        
        
        // Create a new thread to handle the client
        pthread_t thread_id;
        int *socket_ptr = malloc(sizeof(int));
        *socket_ptr = client_socket;
        if (pthread_create(&thread_id, NULL, handle_connection, socket_ptr) != 0) {
            perror("Failed to create thread");
            close(client_socket);
        } else {
            pthread_detach(thread_id);  // Automatically reclaim resources when thread ends
        }

        //handle_connection(client_socket);
    }

    return 0;
}


