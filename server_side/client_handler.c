#include "client_handler.h"
#include <stdbool.h>

// Newly added
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int active_clients = 0;
const int MAX_CLIENTS = 10;

void *handle_connection(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);

    char buffer[BUFSIZE];
    //char response[4000];
    size_t bytes_read;
    FILE *file;
    // Receive the choice from the client
    bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read <= 0) {
        perror("Receive error");
        close(client_socket);
        return NULL;
    }
    buffer[bytes_read] = '\0';
    printf("Request received: %s\n", buffer);

    pthread_mutex_lock(&mutex);
    if (active_clients >= MAX_CLIENTS) {
        printf("...Server unavailable...\n");
        const char *busy_message = "Server is busy. Try again later.\n";
        send(client_socket, busy_message, strlen(busy_message), 0);
        close(client_socket);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }
    active_clients++;
    pthread_mutex_unlock(&mutex);

    if (strcmp(buffer, "1") == 0) {
        // Option 1: Send contents of menu.txt
        const bool dev = false;
        send(client_socket, &dev, sizeof(dev), 0);
        file = fopen("menu.txt", "r");
        if (!file) {
            const char *error_message = "Error: File not found or unable to open.\n";
            send(client_socket, error_message, strlen(error_message), 0);
        } else {
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
                send(client_socket, buffer, bytes_read, 0);
            }
            fclose(file);
        }
        
        
    } else if (strcmp(buffer, "2") == 0) {
        // Option 2: Handle file upload
        const bool dev = true;
        send(client_socket, &dev, sizeof(dev), 0);
        const char *mode = "developer\n";
        send(client_socket, mode, strlen(mode), 0);

    } else {
        // Invalid choice
        const char *invalid_message = "Invalid choice. Please try again.\n";
        send(client_socket, invalid_message, strlen(invalid_message), 0);
    }

    // Close the connection
    close(client_socket);
    printf("Connection closed.\n");

    pthread_mutex_lock(&mutex);
    active_clients--;
    pthread_mutex_unlock(&mutex);

    return NULL;
}


int check(int exp, const char *msg) {
    if (exp == SOCKETERROR) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return exp;
}

int authenticate(const char *username, const char *password) {
    FILE *file = fopen("credentials.txt", "r");
    if (file == NULL) {
        perror("Error opening credentials file");
        exit(EXIT_FAILURE);
    }

    char file_username[50], file_password[50];
    while (fscanf(file, "%s %s", file_username, file_password) == 2) {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

