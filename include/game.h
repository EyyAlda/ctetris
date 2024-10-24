#ifndef GAME_H
#define GAME_H

#include <pthread.h>

typedef struct{	
    int y_values[4];
    int x_values[4];
    int rotation;
    char fieldValue;
    //pthread_mutex_t lock;
    int game_over;
}Tetromino;

//void* gameLoop(void *arg);

void moveDown();

void moveLeft();

void moveRight();

void drop();

void rotate_tetromino();

void createTetromino();

//Tetromino* get_tetromino_ptr();

void prepare();

void showPlayingField();

extern char fieldValues[20][10];

void free_pointer();

void settle_tetromino();

//char** get_playing_field();

#endif
