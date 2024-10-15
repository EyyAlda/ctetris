#include "../include/tetromino.h"

void init_tetromino(Tetromino *tetrominoPtr) {

}

void destroy_tetromino(Tetromino *tetrominoPtr) {
    pthread_mutex_destroy(&tetrominoPtr->lock);
}
