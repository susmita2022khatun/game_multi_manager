#ifndef GAME_COM_H
#define GAME_COM_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef void (*GameFunc)();
typedef struct {
    char *name;
    GameFunc func;
} GameMap;


void play_game(const char *game_name);
void game_2();


#endif 

