#ifndef GAME_H
#define GAME_H

#include <pthread.h>

typedef struct{	
    int y1;
    int y2;
    int y3;
    int y4;
    int x1;
    int x2;
    int x3;
    int x4;
    int rotation;
    char fieldValue;
    //pthread_mutex_t lock;
    int game_over;
}Tetromino;

//void* gameLoop(void *arg);

void moveDown();

void moveLeft();

void moveRight();

void rotate_tetromino();

void createTetromino();

//Tetromino* get_tetromino_ptr();

void prepare();

void showPlayingField();

extern char fieldValues[20][10];

//char** get_playing_field();

#endif
