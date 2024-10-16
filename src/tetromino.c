#include "../include/tetromino.h"
#include <stdio.h>
#include <stdlib.h>

Tetromino* init_tetromino() {
    Tetromino *currentTetrominoPtr = (Tetromino *)malloc(sizeof(Tetromino));

    if (currentTetrominoPtr == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
    return currentTetrominoPtr;
}

void destroy_tetromino(Tetromino *tetrominoPtr) {
    pthread_mutex_destroy(&tetrominoPtr->lock);
}
