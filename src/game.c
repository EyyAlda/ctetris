#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "../include/tetromino.h"

//playing field
char fieldValues[20][10];
/*A field with a Value other than a Tetromino ID letter or 0 means there is a settled Tetromino:
 * 1 = L
 * 2 = J
 * 3 = O
 * 4 = I
 * 5 = S
 * 6 = Z
 * 7 = T*/

int movingTetromino = 0;
int gameFinished = 0;


Tetromino *currentTetrominoPtr = NULL;

//creates a copy of the Tetromino struct to store current Tetromino values
void createCurrentTetromino(){
    currentTetrominoPtr = (Tetromino *)malloc(sizeof(Tetromino));

    if (currentTetrominoPtr == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
}

void gameOver(){

}

void key_handling(){

}



//creates a random new Tetromino
void createTetromino(){
    char possibleTetrominos[] = {'J', 'L', 'O', 'I', 'S', 'Z', 'T'};

    //generate a random number between 0 and 6
    srand((unsigned int)time(NULL));
    int min = 0;
    int max = 6;
    int randomTetromino = min + rand() % (max - min + 1);

    createCurrentTetromino();
    
    //set the default values, including starting position, for each possible tetromino
    switch(possibleTetrominos[randomTetromino]){
        case 'J':
            pthread_mutex_lock(&currentTetrominoPtr->lock);
            currentTetrominoPtr->y1 = 0;
            currentTetrominoPtr->y2 = 1;
            currentTetrominoPtr->y3 = 2;
            currentTetrominoPtr->y4 = 2;
            currentTetrominoPtr->x1 = 5;
            currentTetrominoPtr->x2 = 5;
            currentTetrominoPtr->x3 = 5;
            currentTetrominoPtr->x4 = 4;
            currentTetrominoPtr->fieldValue = 'J';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            pthread_mutex_unlock(&currentTetrominoPtr->lock);
            break;
        case 'L':
            pthread_mutex_lock(&currentTetrominoPtr->lock);
            currentTetrominoPtr->y1 = 0;
            currentTetrominoPtr->y2 = 1;
            currentTetrominoPtr->y3 = 2;
            currentTetrominoPtr->y4 = 2;
            currentTetrominoPtr->x1 = 5;
            currentTetrominoPtr->x2 = 5;
            currentTetrominoPtr->x3 = 5;
            currentTetrominoPtr->x4 = 6;
            currentTetrominoPtr->fieldValue = 'L';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            pthread_mutex_unlock(&currentTetrominoPtr->lock);
            break;
        case 'O':
            pthread_mutex_lock(&currentTetrominoPtr->lock);
            currentTetrominoPtr->y1 = 0;
            currentTetrominoPtr->y2 = 0;
            currentTetrominoPtr->y3 = 1;
            currentTetrominoPtr->y4 = 1;
            currentTetrominoPtr->x1 = 5;
            currentTetrominoPtr->x2 = 6;
            currentTetrominoPtr->x3 = 5;
            currentTetrominoPtr->x4 = 6;
            currentTetrominoPtr->fieldValue = 'O';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            pthread_mutex_unlock(&currentTetrominoPtr->lock);
            break;
        case 'I':
            pthread_mutex_lock(&currentTetrominoPtr->lock);
            currentTetrominoPtr->y1 = 0;
            currentTetrominoPtr->y2 = 1;
            currentTetrominoPtr->y3 = 2;
            currentTetrominoPtr->y4 = 3;
            currentTetrominoPtr->x1 = 5;
            currentTetrominoPtr->x2 = 5;
            currentTetrominoPtr->x3 = 5;
            currentTetrominoPtr->x4 = 5;
            currentTetrominoPtr->fieldValue = 'I';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            pthread_mutex_unlock(&currentTetrominoPtr->lock);
            break;
        case 'S':
            pthread_mutex_lock(&currentTetrominoPtr->lock);
            currentTetrominoPtr->y1 = 0;
            currentTetrominoPtr->y2 = 1;
            currentTetrominoPtr->y3 = 1;
            currentTetrominoPtr->y4 = 2;
            currentTetrominoPtr->x1 = 5;
            currentTetrominoPtr->x2 = 5;
            currentTetrominoPtr->x3 = 6;
            currentTetrominoPtr->x4 = 6;
            currentTetrominoPtr->fieldValue = 'J';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            pthread_mutex_unlock(&currentTetrominoPtr->lock);
            break;
        case 'Z':
            pthread_mutex_lock(&currentTetrominoPtr->lock);
            currentTetrominoPtr->y1 = 0;
            currentTetrominoPtr->y2 = 1;
            currentTetrominoPtr->y3 = 1;
            currentTetrominoPtr->y4 = 2;
            currentTetrominoPtr->x1 = 5;
            currentTetrominoPtr->x2 = 5;
            currentTetrominoPtr->x3 = 4;
            currentTetrominoPtr->x4 = 4;
            currentTetrominoPtr->fieldValue = 'Z';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            pthread_mutex_unlock(&currentTetrominoPtr->lock);
            break;
        case 'T':
            pthread_mutex_lock(&currentTetrominoPtr->lock);
            currentTetrominoPtr->y1 = 0;
            currentTetrominoPtr->y2 = 1;
            currentTetrominoPtr->y3 = 2;
            currentTetrominoPtr->y4 = 2;
            currentTetrominoPtr->x1 = 5;
            currentTetrominoPtr->x2 = 5;
            currentTetrominoPtr->x3 = 5;
            currentTetrominoPtr->x4 = 4;
            currentTetrominoPtr->fieldValue = 'J';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            pthread_mutex_unlock(&currentTetrominoPtr->lock);
            break;
        default:
            printf("Err: failed to create Tetromino!");
            free(currentTetrominoPtr);
            exit(1);
            break;
    }

}

void showPlayingField(){





}

void tetrominoSettled(){
    switch(currentTetrominoPtr->fieldValue) {
        case 'L':
            fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = '1';
            fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = '1';
            fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = '1';
            fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = '1';
            break;
        case 'J':
            fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = '2';
            fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = '2';
            fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = '2';
            fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = '2';
            break;
        case 'O':
            fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = '3';
            fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = '3';
            fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = '3';
            fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = '3';
            break;
        case 'I':
            fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = '4';
            fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = '4';
            fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = '4';
            fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = '4';
            break;
        case 'S':
            fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = '5';
            fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = '5';
            fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = '5';
            fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = '5';
            break;
        case 'Z':
            fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = '6';
            fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = '6';
            fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = '6';
            fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = '6';
            break;
        case 'T':
            fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = '7';
            fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = '7';
            fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = '7';
            fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = '7';
            break;
        default:
            fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = '1';
            fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = '1';
            fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = '1';
            fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = '1';
            break;
    }
    free(currentTetrominoPtr);
}

//checks if an about to be placed tetromino can be placed. If the space is taken it returns 0
int checkForSpace(){
    if (fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] == '0') {
        if (fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] == '0') {
            if (fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] == '0') {
                if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] == '0') {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void placeTetromino(){ 
    fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = currentTetrominoPtr->fieldValue;
    fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = currentTetrominoPtr->fieldValue;
    fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = currentTetrominoPtr->fieldValue;
    fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = currentTetrominoPtr->fieldValue;
}

void clearTetromino(){
    fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = '0';
    fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = '0';
    fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = '0';
    fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = '0';

}

void moveLeft(){
    if (currentTetrominoPtr->x1 > 0 && currentTetrominoPtr->x2 > 0 && currentTetrominoPtr->x3 > 0 && currentTetrominoPtr->x4 > 0) {
        int canMove = 1;
        for (int y = 0; y < sizeof(fieldValues)/sizeof(char); y++){
            for (int x = 0; x < (int)sizeof(fieldValues[y])/(int)sizeof(char); x++) {
                if (fieldValues[y][x] == currentTetrominoPtr->fieldValue) {
                    if (fieldValues[y][x - 1] != '0' && fieldValues[y][x - 1] != currentTetrominoPtr->fieldValue) {
                        canMove = 0;
                    }
                }
            }
        }
        if (canMove){
            clearTetromino();
            currentTetrominoPtr->x1--;
            currentTetrominoPtr->x2--;
            currentTetrominoPtr->x3--;
            currentTetrominoPtr->x4--;
            placeTetromino();
        }
    }
}

void moveRight(){
    if (currentTetrominoPtr->x1 < 9 && currentTetrominoPtr->x2 < 9 && currentTetrominoPtr->x3 < 9 && currentTetrominoPtr->x4 < 9) {
        int canMove = 1;
        for (int y = 0; y < sizeof(fieldValues)/sizeof(char); y++){
            for (int x = 0; x < (int)sizeof(fieldValues[y])/(int)sizeof(char); x++) {
                if (fieldValues[y][x] == currentTetrominoPtr->fieldValue) {
                    if (fieldValues[y][x + 1] != '0' && fieldValues[y][x + 1] != currentTetrominoPtr->fieldValue) {
                        canMove = 0;
                    }
                }
            }
        }
        if (canMove){
            clearTetromino();
            currentTetrominoPtr->x1++;
            currentTetrominoPtr->x2++;
            currentTetrominoPtr->x3++;
            currentTetrominoPtr->x4++;
            placeTetromino();
        }
    }
}

void moveDown(){
    if (currentTetrominoPtr->y1 < 19 && currentTetrominoPtr->y2 < 19 && currentTetrominoPtr->y3 < 19 && currentTetrominoPtr->y4 < 19) {
        int canMove = 1;
        for (int y = 0; y < sizeof(fieldValues)/sizeof(char); y++){
            for (int x = 0; x < (int)sizeof(fieldValues[y])/(int)sizeof(char); x++) {
                if (fieldValues[y][x] == currentTetrominoPtr->fieldValue) {
                    if (fieldValues[y + 1][x] != '0' && fieldValues[y + 1][x] != currentTetrominoPtr->fieldValue) {
                        canMove = 0;
                    }
                }
            }
        }
        if (canMove){
            clearTetromino();
            currentTetrominoPtr->y1++;
            currentTetrominoPtr->y2++;
            currentTetrominoPtr->y3++;
            currentTetrominoPtr->y4++;
            placeTetromino();
        } else {
            tetrominoSettled();
        }
    }
}

void rotate_tetromino(){
    switch(currentTetrominoPtr->fieldValue){
        case 'L':
            switch(currentTetrominoPtr->rotation){
                case '1':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 - 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->x4 -= 2;

                                currentTetrominoPtr->rotation = 2;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case '2':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->y4 -= 2;

                                currentTetrominoPtr->rotation = 3;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case '3':
                    if (fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 - 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 + 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 + 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->x4 += 2;

                                currentTetrominoPtr->rotation = 3;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case '4':


                    currentTetrominoPtr->rotation = 1;
                    break;
            }
            break;
        case 'J':
            switch(currentTetrominoPtr->rotation){
                case '1':
                    

                    currentTetrominoPtr->rotation = 2;
                    break;
                case '2':


                    currentTetrominoPtr->rotation = 3;
                    break;
                case '3':


                    currentTetrominoPtr->rotation = 4;
                    break;
                case '4':


                    currentTetrominoPtr->rotation = 1;
                    break;
            }
            break;
        case 'I':
            switch(currentTetrominoPtr->rotation){
                case '1':
                    

                    currentTetrominoPtr->rotation = 2;
                    break;
                case '2':


                    currentTetrominoPtr->rotation = 3;
                    break;
                case '3':


                    currentTetrominoPtr->rotation = 4;
                    break;
                case '4':


                    currentTetrominoPtr->rotation = 1;
                    break;
            }
            break;
        case 'Z':
            switch(currentTetrominoPtr->rotation){
                case '1':
                    

                    currentTetrominoPtr->rotation = 2;
                    break;
                case '2':


                    currentTetrominoPtr->rotation = 3;
                    break;
                case '3':


                    currentTetrominoPtr->rotation = 4;
                    break;
                case '4':


                    currentTetrominoPtr->rotation = 1;
                    break;
            }
            break;
        case 'S':
            switch(currentTetrominoPtr->rotation){
                case '1':
                    

                    currentTetrominoPtr->rotation = 2;
                    break;
                case '2':


                    currentTetrominoPtr->rotation = 3;
                    break;
                case '3':


                    currentTetrominoPtr->rotation = 4;
                    break;
                case '4':


                    currentTetrominoPtr->rotation = 1;
                    break;
            }
            break;
        case 'T':
            switch(currentTetrominoPtr->rotation){
                case '1':
                    

                    currentTetrominoPtr->rotation = 2;
                    break;
                case '2':


                    currentTetrominoPtr->rotation = 3;
                    break;
                case '3':


                    currentTetrominoPtr->rotation = 4;
                    break;
                case '4':


                    currentTetrominoPtr->rotation = 1;
                    break;
            }
            break;
        default:
            break;
    }
}


void prepare(){
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            fieldValues[i][j] = '0';
        }
    }
}

void gameLoop(){
    prepare();
    while (!gameFinished) {

    }
    if (currentTetrominoPtr != NULL) free(currentTetrominoPtr);
}


