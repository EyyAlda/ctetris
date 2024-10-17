#ifndef GAME_H
#define GAME_H

#include <pthread.h>
#include <stdlib.h>

typedef struct{
	int x1;
	int x2;
	int x3;
	int x4;
	int y1;
	int y2;
	int y3;
	int y4;
}Tetromino;

void gameLoop();

void moveDown();

void moveLeft();

void moveRight();


#endif
