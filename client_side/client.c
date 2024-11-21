#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "game_upload.h"
#include "../games/game_com.h"
#include "../developer_side/utils.h"


#define SERVERPORT 8080
#define BUFSIZE 4096

int main() {
    char username[50], password[50], credentials[100];
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFSIZE];
    int bytes_received;
    bool dev_received;
    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    
    printf("who are you ?\n 1. client\n2. server_member\n");
    int ch;
    scanf("%d", &ch);
    
    

    if(ch == 1){
    	printf("Enter username: ");
    	scanf("%s", username);
    	printf("Enter password: ");
    	scanf("%s", password);

    	// Send credentials to server
    	sprintf(credentials, "%s %s", username, password);
    	send(client_socket, credentials, strlen(credentials), 0);

    	// Wait for authentication response
    	bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    	if (bytes_received > 0) {
        	buffer[bytes_received] = '\0';
       	 	if (strcmp(buffer, "OK") == 0) {
            		printf("Authenticated successfully!\n");
        	} else {
        	    printf("Authentication failed. Exiting...\n");
           	    close(client_socket);
            	    return 0;
        	}
    	}

    	// Menu selection
  
    	printf("Choices:\n1. Game play (players)\n2. Game upload (developers)\n");
    	printf("Enter your choice: ");
    	while (getchar() != '\n');  
    	fgets(buffer, sizeof(buffer), stdin);
    	buffer[strcspn(buffer, "\n")] = 0;  

    	// Send the choice to the server
    	send(client_socket, buffer, strlen(buffer), 0);
    	
	
    	// Receive and display the server's response
    	recv(client_socket, &dev_received, sizeof(dev_received), 0);
    	bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    	if (bytes_received > 0) {
        	buffer[bytes_received] = '\0';
        	printf("%s\n", buffer);
    	}
    
    	if(dev_received){
    
    		char fileName[128];

    		// Prompt user for the file name
    		printf("Enter the name of the file to upload: \n");
    		scanf("%127s", fileName);

    		// Ensure the upload directory exists
    		if (mkdir(UPLOAD_DIR, 0755) != 0 && errno != EEXIST) {
        		perror("Error creating upload directory");
        		return 1;
    		}

    		// Upload the file
    		uploadFile(fileName);
    
    	}else{
    		bool game_pl = true;
		while(game_pl){
    	
    		char game_name[50]; // Allocate memory for the game name
		int k;
    		printf("Enter the game name: ");
    		scanf("%49s", game_name); // Read up to 49 characters (prevent overflow)

    		play_game(game_name);
    		
    		printf("1. play again \n2. exit\n");
    		scanf("%d", &k);
    		if(k == 2){
    			game_pl = false;
    		}else{
    		
    		FILE *f = fopen("menu.txt", "r"); 
    			if (f == NULL) {
        			perror("Error opening file"); 
        			exit(EXIT_FAILURE);
    			}

    			char ch;
    			printf(" '%s':\n\n", "menu");
    			while ((ch = fgetc(f)) != EOF) { 
        			putchar(ch); 
    			}

    			fclose(f); // Close the file after reading
    			}
    		}
    	}
	
    	// Close the socket
    	close(client_socket);
    	}else{
    	
    		printf("Enter username: ");
    		scanf("%s", username);
    		printf("Enter password: ");
    		scanf("%s", password);

    		if((strcmp(username, "server") == 0)&&(strcmp(password, "123") ==0)){
    			printf(" authorized ... \n");
    			
    			 int choice;

    		while (1) {
        		printf("\n--- File Operations Menu ---\n");
        		printf("1. List uploaded files\n");
        		printf("2. Display the content of a file\n");
        		printf("3. Compile 'copy_content.c'\n");
        		printf("4. Exit\n");
        		printf("Enter your choice: ");
        		scanf("%d", &choice);
	
        		switch (choice) {
        		    case 1:
        		        list_files();
        		        break;
        		    case 2:
        		        display_file_content();
        		        break;
        		    case 3:
        		        compile_copy_content();
        		        break;
        		    case 4:
        		    	printf("Do refresh the server by running make server");
        		        printf("Exiting program.\n");
        		        return 0;
        		    default:
        		        printf("Invalid choice. Please try again.\n");
        		}
    		}
    			
    		}else{
    			printf(" unauthorized ...\n");
    		}
    	
    	}
    return 0;
}

