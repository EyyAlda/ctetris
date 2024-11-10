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

void set_show_ghost(int ghost);

void moveDown();

void moveLeft();

void moveRight();

void drop(int ghost);

void rotate_tetromino();

void createTetromino();

void prepare();

void showPlayingField();

extern char fieldValues[20][10];

extern int game_over;

void free_pointer();

void settle_tetromino();

void gameOver();

int checkForSpace();


#endif
