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
        printf("Memory allocation failed!\n");
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
            break;
        case 'L':
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
            break;
        case 'O':
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
            break;
        case 'I':
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
            break;
        case 'S':
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
            break;
        case 'Z':
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
            break;
        case 'T':
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
            break;
        default:
            printf("Err: failed to create Tetromino!\n");
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
        printf("<!");
        for(int x = 0; x < 10; x++){
            printf("%c",fieldValues[y][x]);
        }
        printf("!>\n");
    }
}

void move_above_down(int row){
    printf("\033[0;36mmoving upper placed tetrominos down\033[0m\n");
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
                printf("\033[0;33mspace taken:%d\033[0m\n", y);
                spaces_taken++;
            }
        }
        if (spaces_taken >= 9) {
            printf("\033[0;35mfull row\033[0m\n");
            y = row_is_full;
            move_above_down(y);
        }
            row_is_full = 0;
    }
    showPlayingField();
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
    free(currentTetrominoPtr);
    currentTetrominoPtr = NULL;
    check_for_full_row();
    
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
    if (currentTetrominoPtr->y1 == 19 || currentTetrominoPtr->y2 == 19 || currentTetrominoPtr->y3 == 19 || currentTetrominoPtr->y4 == 19){
        printf("reached the lowest point\n");
        tetrominoSettled();
        goto skip_check;
    }
    int break_loop = 0;
    for (int y = 19; y > 0; y--){
        for (int x = 0; x < 10; x++){
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
    
}

void moveLeft(){
    if (currentTetrominoPtr != NULL){
        printf("\033[0;31mmoving Left\033[0m\n");
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
        showPlayingField();
    }
}

void moveRight(){
    if (currentTetrominoPtr != NULL){
        printf("\033[0;31mmoving right\033[0m\n");
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
        showPlayingField();
    }
}

void moveDown(){
    if (currentTetrominoPtr != NULL){
        printf("after lock\n");
        if (currentTetrominoPtr->y1 < 19 && currentTetrominoPtr->y2 < 19 && currentTetrominoPtr->y3 < 19 && currentTetrominoPtr->y4 < 19) {
            int canMove = 1;
            for (int y = 0; y < sizeof(fieldValues)/sizeof(char); y++){
                for (int x = 0; x < (int)sizeof(fieldValues[y])/(int)sizeof(char); x++) {
                    if (fieldValues[y][x] == currentTetrominoPtr->fieldValue) {
                        if (fieldValues[y + 1][x] != '0' && fieldValues[y + 1][x] != currentTetrominoPtr->fieldValue && y + 1 > 18) {
                            printf("cannot move\n");
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
        showPlayingField();
    } else {
        createTetromino();
    }
}

int is_in_boundries(int y, int x){
    if (y < (sizeof(fieldValues)/sizeof(char)) && x < (sizeof(fieldValues[y])/sizeof(char))) {
        return 1;
    } else {
        return 0;
    }
}


void rotate_tetromino(){
    printf("\033[0;31mrotating Tetromino\033[0m\n\n");
    switch(currentTetrominoPtr->fieldValue){
        case 'L':
            printf("\033[0;32mrotating Tetromino L\033[0m\n\n");
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 + 1)){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 - 1)){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 - 2] == '0' && is_in_boundries(currentTetrominoPtr->y4, currentTetrominoPtr->x4 - 2)){
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

                case 2:
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 - 1)){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 + 1)){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4] == '0' && is_in_boundries(currentTetrominoPtr->y4 - 2, currentTetrominoPtr->x4)){
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
                    
                case 3:
                    if (fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 - 1, currentTetrominoPtr->x1 - 1)){
                        if (fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 + 1, currentTetrominoPtr->x3 + 1)){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 + 2] == '0' && is_in_boundries(currentTetrominoPtr->y4, currentTetrominoPtr->x4 + 2)){
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

                case 4:
                    if (fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 - 1, currentTetrominoPtr->x1 + 1)){
                        if (fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 + 1, currentTetrominoPtr->x3 - 1)){
                            if (fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == '0' && is_in_boundries(currentTetrominoPtr->y4 + 2, currentTetrominoPtr->x4)){
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
            break;
        case 'J':
            printf("\033[0;32mrotating Tetromino J\033[0m\n\n");
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 + 1)){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 - 1)){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4] == '0' && is_in_boundries(currentTetrominoPtr->y4 - 2, currentTetrominoPtr->x4)){
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


                case 2:
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 - 1)){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 + 1)){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 + 2] == '0' && is_in_boundries(currentTetrominoPtr->y4, currentTetrominoPtr->x4 + 2)){
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


                case 3:
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 + 1)){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 - 1)){
                            if (fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == '0' && is_in_boundries(currentTetrominoPtr->y4 + 2, currentTetrominoPtr->x4)){
                                clearTetromino();
                                currentTetrominoPtr->x1 -= 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 += 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->y4 += 2;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;

                case 4:
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 - 1)){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 + 1)){
                            if (fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 - 2] == '0' && is_in_boundries(currentTetrominoPtr->y4, currentTetrominoPtr->x4 - 2)){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->x4 -= 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;
            }
            break;
        case 'I':
            printf("\033[0;32mrotating Tetromino I\033[0m\n\n");
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 + 1)){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 - 1)){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4 - 2] == '0' && is_in_boundries(currentTetrominoPtr->y4 - 2, currentTetrominoPtr->x4 - 2)){
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


                case 2:
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 - 1)){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 + 1)){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4 + 2] == '0' && is_in_boundries(currentTetrominoPtr->y4 - 2, currentTetrominoPtr->x4 + 2)){
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


                case 3:
                    if (fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 - 1, currentTetrominoPtr->x1 - 1)){
                        if (fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 + 1, currentTetrominoPtr->x3 + 1)){
                            if (fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4 + 2] == '0' && is_in_boundries(currentTetrominoPtr->y4 + 2, currentTetrominoPtr->x4 + 2)){
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


                case 4:
                    if (fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0' && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 - 1)){
                        if (fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0' && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 + 1)){
                            if (fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4 + 2] == '0' && is_in_boundries(currentTetrominoPtr->y4 - 2, currentTetrominoPtr->x4 + 2)){
                                clearTetromino();
                                currentTetrominoPtr->x1 += 1;
                                currentTetrominoPtr->y1 -= 1;
                                currentTetrominoPtr->x3 -= 1;
                                currentTetrominoPtr->y3 += 1;
                                currentTetrominoPtr->x4 -= 2;
                                currentTetrominoPtr->y4 += 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;


            }
            break;
        case 'Z':
            printf("\033[0;32mrotating Tetromino Z\033[0m\n");
            printf("\033[0;32m%d\033[0m\n", currentTetrominoPtr->rotation);
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if ((fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0' || fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 + 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0' || fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 - 1)){
                            if ((fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4] == '0' || fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y4 - 2, currentTetrominoPtr->x4)){
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
                case 2:
                    if ((fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0' || fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 - 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 + 1] == '0' || fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 + 1, currentTetrominoPtr->x3 + 1)){
                            if ((fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 + 2] == '0' || fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 + 2] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y4, currentTetrominoPtr->x4 + 2)){
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
                case 3:
                    if ((fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 - 1] == '0' || fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 - 1, currentTetrominoPtr->x1 - 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == '0' || fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 + 1, currentTetrominoPtr->x3 - 1)){
                            if ((fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == '0' || fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y4 + 2, currentTetrominoPtr->x4)){
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
                case 4:
                    if ((fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == '0' || fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 - 1, currentTetrominoPtr->x1 + 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0' || fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 - 1)){
                            if ((fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 - 2] == '0' || fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 - 2] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y4, currentTetrominoPtr->x4 - 2)){
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
            break;
        case 'S':
            printf("\033[0;32mrotating Tetromino S\033[0m\n\n");
            printf("\033[0;32m%d\033[0m\n", currentTetrominoPtr->rotation);
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if ((fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0' || fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 + 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == '0' || fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 + 1, currentTetrominoPtr->x3 - 1)){
                            if ((fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 - 2] == '0' || fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 - 2] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y4, currentTetrominoPtr->x4 - 2)){
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

                case 2:
                    if ((fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0' || fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 - 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0' || fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 - 1)){
                            if ((fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4] == '0' || fieldValues[currentTetrominoPtr->y4 - 2][currentTetrominoPtr->x4] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y4 - 2, currentTetrominoPtr->x4)){
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
                case 3:
                    if ((fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 - 1] == '0' || fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 - 1, currentTetrominoPtr->x1 - 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0' || fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 + 1)){
                            if ((fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 + 2] == '0' || fieldValues[currentTetrominoPtr->y4][currentTetrominoPtr->x4 + 2] == currentTetrominoPtr->fieldValue )&& is_in_boundries(currentTetrominoPtr->y4, currentTetrominoPtr->x4 + 2)){
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
                case 4:
                    if ((fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == '0' || fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 - 1, currentTetrominoPtr->x1 + 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 + 1] == '0' || fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 + 1, currentTetrominoPtr->x3 + 1)){
                            if ((fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == '0' || fieldValues[currentTetrominoPtr->y4 + 2][currentTetrominoPtr->x4] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y4 + 2, currentTetrominoPtr->x4)){
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
            break;

        case 'T':
            printf("\033[0;32mrotating Tetromino T\033[0m\n\n");
            printf("\033[0;32m%d\033[0m\n", currentTetrominoPtr->rotation);
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if ((fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == '0' || fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 + 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == '0' || fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 - 1)){
                            if ((fieldValues[currentTetrominoPtr->y4 - 1][currentTetrominoPtr->x4 + 1] == '0' || fieldValues[currentTetrominoPtr->y4 - 1][currentTetrominoPtr->x4 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y4 - 1, currentTetrominoPtr->x4 + 1)){
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
                case 2:
                    if ((fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == '0' || fieldValues[currentTetrominoPtr->y1 + 1][currentTetrominoPtr->x1 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 + 1, currentTetrominoPtr->x1 - 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == '0' || fieldValues[currentTetrominoPtr->y3 - 1][currentTetrominoPtr->x3 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 - 1, currentTetrominoPtr->x3 + 1)){
                            if ((fieldValues[currentTetrominoPtr->y4 + 1][currentTetrominoPtr->x4 + 1] == '0' || fieldValues[currentTetrominoPtr->y4 + 1][currentTetrominoPtr->x4 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y4 + 1, currentTetrominoPtr->x4 + 1)){
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
                case 3:
                    if ((fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == '0' || fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 - 1, currentTetrominoPtr->x1 + 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == '0' || fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 + 1, currentTetrominoPtr->x3 - 1)){
                            if ((fieldValues[currentTetrominoPtr->y4 + 1][currentTetrominoPtr->x4 - 1] == '0' || fieldValues[currentTetrominoPtr->y4 + 1][currentTetrominoPtr->x4 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y4 + 1, currentTetrominoPtr->x4 - 1)){
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
                case 4:
                    if ((fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == '0' || fieldValues[currentTetrominoPtr->y1 - 1][currentTetrominoPtr->x1 + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y1 - 1, currentTetrominoPtr->x1 + 1)){
                        if ((fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == '0' || fieldValues[currentTetrominoPtr->y3 + 1][currentTetrominoPtr->x3 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y3 + 1, currentTetrominoPtr->x3 - 1)){
                            if ((fieldValues[currentTetrominoPtr->y4 - 1][currentTetrominoPtr->x4 - 1] == '0' || fieldValues[currentTetrominoPtr->y4 - 1][currentTetrominoPtr->x4 - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y4 - 1, currentTetrominoPtr->x4 - 1)){
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
            break;
        default:
            break;
    }
    showPlayingField();
}






void prepare(){
    printf("preparing playing field\n");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            fieldValues[i][j] = '0';
        }
    }
}

/*void* gameLoop(void *arg){
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
    return NULL;
}*/

/*char** get_playing_field() {
    char** playing_field = (char**)malloc(20 * sizeof(char*));  // Correct allocation
    if (playing_field == NULL) return NULL;

    for (int i = 0; i < 20; i++) {
        playing_field[i] = (char*)malloc(10 * sizeof(char));  // Allocate 10 chars for each row
        if (playing_field[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(playing_field[j]);
            }
            free(playing_field);
            return NULL;
        }
    }

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            playing_field[y][x] = fieldValues[y][x];
        }
    }

    return playing_field;
}*/
