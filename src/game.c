#include <stdio.h>
#include <gdk-pixbuf-2.0/gdk-pixbuf/gdk-pixbuf.h>
#include <gdk/gdk.h>
#include <glib-2.0/glib.h>
#include <gtk-4.0/gtk/css/gtkcss.h>
#include <gtk-4.0/gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "../include/game.h"

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
    printf("creating Tetromino\n");
    currentTetrominoPtr = (Tetromino *)malloc(sizeof(Tetromino));

    if (currentTetrominoPtr == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
}

void gameOver(){
    printf("gameFinished!\n");
    if (currentTetrominoPtr != NULL){
        free(currentTetrominoPtr);
        currentTetrominoPtr = NULL;
    }
    exit(1);
}

void key_handling(){

}

//checks if an about to be placed tetromino can be placed. If the space is taken it returns 0
int checkForSpace(){
    printf("checking if space is available\n");
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



//creates a random new Tetromino
void createTetromino(){
    char possibleTetrominos[] = {'J', 'L', 'O', 'I', 'S', 'Z', 'T'};

    //generate a random number between 0 and 6
    srand((unsigned int)time(NULL));
    int min = 0;
    int max = 6;
    int randomTetromino = min + rand() % (max - min + 1);

    createCurrentTetromino();
    
    printf("setting default values\n");
    //set the default values, including starting position, for each possible tetromino
    switch(possibleTetrominos[randomTetromino]){
        case 'J':
            pthread_mutex_lock(&currentTetrominoPtr->lock);
            currentTetrominoPtr->y1 = 0;
            currentTetrominoPtr->y2 = 1;
            currentTetrominoPtr->y3 = 2;
            currentTetrominoPtr->y4 = 2;
            currentTetrominoPtr->x1 = 4;
            currentTetrominoPtr->x2 = 4;
            currentTetrominoPtr->x3 = 4;
            currentTetrominoPtr->x4 = 3;
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
            currentTetrominoPtr->x1 = 4;
            currentTetrominoPtr->x2 = 4;
            currentTetrominoPtr->x3 = 4;
            currentTetrominoPtr->x4 = 5;
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
            currentTetrominoPtr->x1 = 4;
            currentTetrominoPtr->x2 = 5;
            currentTetrominoPtr->x3 = 4;
            currentTetrominoPtr->x4 = 5;
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
            currentTetrominoPtr->x1 = 4;
            currentTetrominoPtr->x2 = 4;
            currentTetrominoPtr->x3 = 4;
            currentTetrominoPtr->x4 = 4;
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
            currentTetrominoPtr->x1 = 4;
            currentTetrominoPtr->x2 = 4;
            currentTetrominoPtr->x3 = 5;
            currentTetrominoPtr->x4 = 5;
            currentTetrominoPtr->fieldValue = 'S';
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
            currentTetrominoPtr->y4 = 1;
            currentTetrominoPtr->x1 = 5;
            currentTetrominoPtr->x2 = 5;
            currentTetrominoPtr->x3 = 5;
            currentTetrominoPtr->x4 = 4;
            currentTetrominoPtr->fieldValue = 'T';
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
    if (!checkForSpace()){
        printf("not enough Space\n");
        gameOver();
    }

}

void showPlayingField(){
    for(int y = 0; y < 20; y++){
        printf("%d<!", y);
        for(int x = 0; x < 9; x++){
            printf("%c",fieldValues[y][x]);
        }
        printf("!>\n");
    }




}

void tetrominoSettled(){
    printf("setteling tetromino\n");
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
    printf("checking if reached the top row\n");
    if (currentTetrominoPtr->y4 == 0 || currentTetrominoPtr->y3 == 0 || currentTetrominoPtr->y2 == 0 || currentTetrominoPtr->y1 == 0){
        printf("game finished\n");
        gameFinished = 1;
    }
    printf("resetting pointer\n");
    pthread_mutex_unlock(&currentTetrominoPtr->lock);
    free(currentTetrominoPtr);
    currentTetrominoPtr = NULL;
    
}



void placeTetromino(){ 
    printf("placing the tetromino\n");
    fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = currentTetrominoPtr->fieldValue;
    fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = currentTetrominoPtr->fieldValue;
    fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = currentTetrominoPtr->fieldValue;
    fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = currentTetrominoPtr->fieldValue;
}

void clearTetromino(){
    printf("clearing tetromino\n");
    fieldValues[currentTetrominoPtr->y1][currentTetrominoPtr->x1] = '0';
    fieldValues[currentTetrominoPtr->y2][currentTetrominoPtr->x2] = '0';
    fieldValues[currentTetrominoPtr->y3][currentTetrominoPtr->x3] = '0';
    fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4] = '0';

}
void settle_tetromino(){
    printf("checking if a tetromino should settle\n");
    pthread_mutex_lock(&currentTetrominoPtr->lock);
    if (currentTetrominoPtr->y1 == 19 || currentTetrominoPtr->y2 == 19 || currentTetrominoPtr->y3 == 19 || currentTetrominoPtr->y4 == 19){
        printf("reached the lowest point\n");
        tetrominoSettled();
        goto skip_check;
    }
    int break_loop = 0;
    for (int y = 19; y > 0; y--){
        for (int x = 0; x < 9; x++){
            if (fieldValues[y][x] == currentTetrominoPtr->fieldValue){
                if (fieldValues[y + 1][x] != '0' && fieldValues[y + 1][x] != currentTetrominoPtr->fieldValue){
                    printf("found tetromino below\n");
                    tetrominoSettled();
                    break_loop = 1;
                    break;
                }
            }
        }
        if (break_loop) break;
    }
skip_check:
    printf("after skip_check\n");
    if (currentTetrominoPtr != NULL){
        if(pthread_mutex_trylock(&currentTetrominoPtr->lock) == EBUSY) {
            pthread_mutex_unlock(&currentTetrominoPtr->lock);
        } else {
            pthread_mutex_unlock(&currentTetrominoPtr->lock);
        }
    }
}

void moveLeft(){
    pthread_mutex_lock(&currentTetrominoPtr->lock);
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
        pthread_mutex_unlock(&currentTetrominoPtr->lock);
}

void moveRight(){
    pthread_mutex_lock(&currentTetrominoPtr->lock);
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
    pthread_mutex_unlock(&currentTetrominoPtr->lock);
}

void moveDown(){
    pthread_mutex_lock(&currentTetrominoPtr->lock);
    printf("after lock\n");
    if (currentTetrominoPtr->y1 < 19 && currentTetrominoPtr->y2 < 19 && currentTetrominoPtr->y3 < 19 && currentTetrominoPtr->y4 < 19) {
        int canMove = 1;
        for (int y = 0; y < sizeof(fieldValues)/sizeof(char); y++){
            for (int x = 0; x < (int)sizeof(fieldValues[y])/(int)sizeof(char); x++) {
                if (fieldValues[y][x] == currentTetrominoPtr->fieldValue) {
                    if (fieldValues[y + 1][x] != '0' && fieldValues[y + 1][x] != currentTetrominoPtr->fieldValue && y + 1 > 18) {
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
            settle_tetromino();
        }
    }
    pthread_mutex_unlock(&currentTetrominoPtr->lock);
}

void move_above_down(int row){
    printf("moving upper placed tetrominos down\n");
    for (int x = 0; x < 9; x++){
        fieldValues[row][x] = '0';
    }
    for (int y = row - 1; y > 0; y--){
        for (int x = 0; x < 9; x++){
            if (fieldValues[y][x] != '0' && fieldValues[y][x] != 'L' && fieldValues[y][x] != 'J' && fieldValues[y][x] != 'T' && fieldValues[y][x] != 'S' && fieldValues[y][x] != 'Z' && fieldValues[y][x] != 'O' && fieldValues[y][x] != 'I'){
                fieldValues[y + 1][x] = fieldValues[y][x];
                fieldValues[y][x] = '0';
            }
        }
    }
}


void check_for_full_row(){
    printf("checking if a row is filled\n");
    int row_is_full = 0;
    for (int y = 19; y > 0; y--){
        int spaces_taken = 0;
        for (int x = 9; x > 0; x--){
            if (fieldValues[y][x] != '0' && fieldValues[y][x] != 'L' && fieldValues[y][x] != 'J' && fieldValues[y][x] != 'I' && fieldValues[y][x] != 'O' && fieldValues[y][x] != 'S' && fieldValues[y][x] != 'Z' && fieldValues[y][x] != 'T'){
                spaces_taken++;
            }
        }
        if (spaces_taken == 10) {
            y = row_is_full;
            move_above_down(y);
        }
            row_is_full = 0;
    }
    showPlayingField();
}

void rotate_tetromino(){
    printf("rotating Tetromino\n");
    pthread_mutex_lock(&currentTetrominoPtr->lock);
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

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;

                case '4':
                    if (fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->y4 += 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;
            }
        case 'J':
            switch(currentTetrominoPtr->rotation){
                case '1':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->y4 -= 2;

                                currentTetrominoPtr->rotation = 2;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case '2':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 + 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->x4 += 2;

                                currentTetrominoPtr->rotation = 3;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case '3':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->y4 += 2;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;

                case '4':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 - 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->x4 -= 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;
            }
        case 'I':
            switch(currentTetrominoPtr->rotation){
                case '1':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4 - 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->x4 -= 2;
                                currentTetrominoPtr->y4 -= 2;

                                currentTetrominoPtr->rotation = 2;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case '2':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4 + 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->x4 += 2;
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
                            if (fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4 + 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->x4 += 2;
                                currentTetrominoPtr->y4 += 2;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case '4':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4 + 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->x4 += 2;
                                currentTetrominoPtr->y4 -= 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;


            }
        case 'Z':
            switch(currentTetrominoPtr->rotation){
                case '1':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 += 1;
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
                        if (fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 + 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 + 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->x4 += 2;

                                currentTetrominoPtr->rotation = 3;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case '3':
                    if (fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 - 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->y4 += 2;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case '4':
                    if (fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 - 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->x4 -= 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;


            }
        case 'S':
            switch(currentTetrominoPtr->rotation){
                case '1':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 - 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->x4 -= 2;

                                currentTetrominoPtr->rotation = 2;
                                placeTetromino();
                            }
                        }
                    }
                    break;

                case '2':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 -= 1;
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
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 + 2] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->x4 += 2;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case '4':
                    if (fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 + 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->y4 += 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;
            }

        case 'T':
            switch(currentTetrominoPtr->rotation){
                case '1':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 - 1][currentTetrominoPtr->x4 + 1] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->x4 += 1;
                                currentTetrominoPtr->y4 -= 1;

                                currentTetrominoPtr->rotation = 2;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case '2':
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 + 1][currentTetrominoPtr->x4 + 1] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 += 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 -= 1;
                                currentTetrominoPtr->x4 += 1;
                                currentTetrominoPtr->y4 += 1;

                                currentTetrominoPtr->rotation = 3;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case '3':
                    if (fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->y4 += 1;
                                currentTetrominoPtr->x4 -= 1;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case '4':
                    if (fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == '0'){
                        if (fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == '0'){
                            if (fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == '0'){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->x4 -= 1;
                                currentTetrominoPtr->y4 -= 1;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;
            }
        default:
            break;
    }
    pthread_mutex_unlock(&currentTetrominoPtr->lock);
}






void prepare(){
    printf("preparing playing field\n");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            fieldValues[i][j] = '0';
        }
    }
}

void gameLoop(){
    printf("entering the main loop\n");
    prepare();
    while (!gameFinished) {
        if (currentTetrominoPtr == NULL && !gameFinished){
            createTetromino();
        }
        printf("executing moveDown\n");
        moveDown();
        printf("executing showPlayingField\n");
        showPlayingField();
        printf("sleeping for one second\n");
        sleep(1);
        settle_tetromino();
    }
    if (currentTetrominoPtr != NULL){
        free(currentTetrominoPtr);
        currentTetrominoPtr = NULL;
    }
}

Tetromino* get_tetromino_ptr(){
    return currentTetrominoPtr;
}

