# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra

# Targets
CLIENT_TARGET = client
SERVER_TARGET = server

# Source Files
CLIENT_SOURCES = client_side/client.c client_side/game_upload.c developer_side/utils.c games/game_com.c
SERVER_SOURCES = server_side/queue.c server_side/server.c server_side/client_handler.c

# Build the client
$(CLIENT_TARGET): $(CLIENT_SOURCES)
	$(CC) $(CFLAGS) $(CLIENT_SOURCES) -o $(CLIENT_TARGET)

# Build the server
$(SERVER_TARGET): $(SERVER_SOURCES)
	$(CC) $(CFLAGS) $(SERVER_SOURCES) -o $(SERVER_TARGET)

# Clean build artifacts
clean:
	rm -f $(CLIENT_TARGET) $(SERVER_TARGET)

# Run all targets
all: $(CLIENT_TARGET) $(SERVER_TARGET)

