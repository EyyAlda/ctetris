
#ifndef TETROMINO_H
#define TETROMINO_H

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
    pthread_mutex_t lock;
    int game_over;
} Tetromino;

void init_tetromino(Tetromino *tetrominoPtr);


void destroy_tetromino(Tetromino *tetrominoPtr);

#endif
