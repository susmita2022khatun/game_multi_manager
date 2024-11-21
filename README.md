# Multiplayer Game Project

## Overview

This project is a multiplayer game server-client application that allows users to upload and play games such as Tic-Tac-Toe. The server handles multiple clients simultaneously, managing game uploads and gameplay sessions. 

## Table of Contents

- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation](#installation)
- [Usage](#usage)
- [Game Uploading](#game-uploading)
- [Playing Games](#playing-games)
- [Contributing](#contributing)
- [License](#license)

## Features

- User authentication with username and password.
- Upload custom games written in C++.
- Compile uploaded games on the server.
- Play games in the terminal.
- Handle multiple client connections concurrently.

## Technologies Used

- C/C++
- POSIX Threads (pthread)
- Socket Programming
- Makefile for build automation
- Git for version control

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/susmita2022khatun/multiplayer_game.git
   cd multiplayer_game
   ```

2. **Server**:
   - Navigate to the server directory:
     ```bash
     cd server
     ```
   - Compile the server:
     ```bash
     make
     ```

3. **Client**:
   - Navigate to the client directory:
     ```bash
     cd ../client
     ```
   - Compile the client:
     ```bash
     make
     ```

## Usage

1. **Start the Server**:
   - Navigate to the server directory:
     ```bash
     cd server
     ```
   - Run the server:
     ```bash
     ./server
     ```

2. **Start the Client**:
   - Open another terminal window.
   - Navigate to the client directory:
     ```bash
     cd client
     ```
   - Run the client:
     ```bash
     ./client
     ```

3. **Authentication**:
   - Enter your username and password when prompted.

## Game Uploading

1. After authentication, choose option 1 to upload a game.
2. Enter the name of the C file you wish to upload (e.g., `tic_tac_toe.cpp`).
3. Paste the content of your C game file when prompted.
4. The server will compile the uploaded game. If successful, you'll receive a confirmation message.

## Playing Games

1. After authentication, choose option 2 to play a game.
2. Enter the command to start the game (e.g., `./tic_tac_toe`).
3. The game will start in the terminal, and you can play as prompted.



