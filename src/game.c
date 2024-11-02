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
int game_over = 0;

Tetromino *currentTetrominoPtr = NULL;

//creates a copy of the Tetromino struct to store current Tetromino values
void createCurrentTetromino(){
    //printf("creating Tetromino\n");
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
    game_over = 1;
}


//checks if an about to be placed tetromino can be placed. If the space is taken it returns 0
int checkForSpace(){
    //printf("checking if space is available\n");
    if (fieldValues[currentTetrominoPtr->y_values[0]][currentTetrominoPtr->x_values[0]] == '0') {
        if (fieldValues[currentTetrominoPtr->y_values[1]][currentTetrominoPtr->x_values[1]] == '0') {
            if (fieldValues[currentTetrominoPtr->y_values[2]][currentTetrominoPtr->x_values[2]] == '0') {
                if (fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3]] == '0') {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void placeTetromino(){ 
    //printf("placing the tetromino\n");
    for (int i = 0; i < 4; i++){
        fieldValues[currentTetrominoPtr->y_values[i]][currentTetrominoPtr->x_values[i]] = currentTetrominoPtr->fieldValue;
    }
}

void clearTetromino(){
    //printf("clearing tetromino\n");
    for (int i = 0; i < 4; i++){
        fieldValues[currentTetrominoPtr->y_values[i]][currentTetrominoPtr->x_values[i]] = '0';
    }
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
    
    //printf("setting default values\n");
    //set the default values, including starting position, for each possible tetromino
    switch(possibleTetrominos[randomTetromino]){
        case 'J':
            currentTetrominoPtr->y_values[0] = 0;
            currentTetrominoPtr->y_values[1] = 1;
            currentTetrominoPtr->y_values[2] = 2;
            currentTetrominoPtr->y_values[3] = 2;
            currentTetrominoPtr->x_values[0] = 4;
            currentTetrominoPtr->x_values[1] = 4;
            currentTetrominoPtr->x_values[2] = 4;
            currentTetrominoPtr->x_values[3] = 3;
            currentTetrominoPtr->fieldValue = 'J';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            break;
        case 'L':
            currentTetrominoPtr->y_values[0] = 0;
            currentTetrominoPtr->y_values[1] = 1;
            currentTetrominoPtr->y_values[2] = 2;
            currentTetrominoPtr->y_values[3] = 2;
            currentTetrominoPtr->x_values[0] = 4;
            currentTetrominoPtr->x_values[1] = 4;
            currentTetrominoPtr->x_values[2] = 4;
            currentTetrominoPtr->x_values[3] = 5;
            currentTetrominoPtr->fieldValue = 'L';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            break;
        case 'O':
            currentTetrominoPtr->y_values[0] = 0;
            currentTetrominoPtr->y_values[1] = 0;
            currentTetrominoPtr->y_values[2] = 1;
            currentTetrominoPtr->y_values[3] = 1;
            currentTetrominoPtr->x_values[0] = 4;
            currentTetrominoPtr->x_values[1] = 5;
            currentTetrominoPtr->x_values[2] = 4;
            currentTetrominoPtr->x_values[3] = 5;
            currentTetrominoPtr->fieldValue = 'O';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            break;
        case 'I':
            currentTetrominoPtr->y_values[0] = 0;
            currentTetrominoPtr->y_values[1] = 1;
            currentTetrominoPtr->y_values[2] = 2;
            currentTetrominoPtr->y_values[3] = 3;
            currentTetrominoPtr->x_values[0] = 4;
            currentTetrominoPtr->x_values[1] = 4;
            currentTetrominoPtr->x_values[2] = 4;
            currentTetrominoPtr->x_values[3] = 4;
            currentTetrominoPtr->fieldValue = 'I';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            break;
        case 'S':
            currentTetrominoPtr->y_values[0] = 0;
            currentTetrominoPtr->y_values[1] = 1;
            currentTetrominoPtr->y_values[2] = 1;
            currentTetrominoPtr->y_values[3] = 2;
            currentTetrominoPtr->x_values[0] = 4;
            currentTetrominoPtr->x_values[1] = 4;
            currentTetrominoPtr->x_values[2] = 5;
            currentTetrominoPtr->x_values[3] = 5;
            currentTetrominoPtr->fieldValue = 'S';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            break;
        case 'Z':
            currentTetrominoPtr->y_values[0] = 0;
            currentTetrominoPtr->y_values[1] = 1;
            currentTetrominoPtr->y_values[2] = 1;
            currentTetrominoPtr->y_values[3] = 2;
            currentTetrominoPtr->x_values[0] = 5;
            currentTetrominoPtr->x_values[1] = 5;
            currentTetrominoPtr->x_values[2] = 4;
            currentTetrominoPtr->x_values[3] = 4;
            currentTetrominoPtr->fieldValue = 'Z';
            currentTetrominoPtr->rotation = 1;
            currentTetrominoPtr->game_over = 0;
            break;
        case 'T':
            currentTetrominoPtr->y_values[0] = 0;
            currentTetrominoPtr->y_values[1] = 1;
            currentTetrominoPtr->y_values[2] = 2;
            currentTetrominoPtr->y_values[3] = 1;
            currentTetrominoPtr->x_values[0] = 5;
            currentTetrominoPtr->x_values[1] = 5;
            currentTetrominoPtr->x_values[2] = 5;
            currentTetrominoPtr->x_values[3] = 4;
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

void move_above_down(int row) {
    //printf("\033[0;36mmoving upper placed tetrominos down\033[0m\n");

    // Clear the current row
    for (int x = 0; x < 10; x++) {
        fieldValues[row][x] = '0';
    }

    // Move all rows above down by one
    for (int y = row - 1; y >= 0; y--) {
        for (int x = 0; x < 10; x++) {
            fieldValues[y + 1][x] = fieldValues[y][x];  // Move row above down
            fieldValues[y][x] = '0';  // Clear the moved row
        }
    }
}

void check_for_full_row() {
    //printf("checking if a row is filled\n");

    // Loop through rows from bottom to top
    for (int y = 19; y >= 0; y--) {
        int spaces_taken = 0;

        // Check if the row is full
        for (int x = 0; x < 10; x++) {
            if (fieldValues[y][x] != '0') {
                spaces_taken++;
            }
        }

        // If the row is full, clear it and move rows down
        if (spaces_taken == 10) {  // A row is full if all 10 spaces are taken
            printf("\033[0;35mfull row at %d\033[0m\n", y);
            move_above_down(y);
            y++;  // Recheck this row after moving above rows down
        }
    }
}


void tetrominoSettled(){
    //printf("setteling tetromino\n");
    switch(currentTetrominoPtr->fieldValue) {
        case 'L':
            for (int i = 0; i < 4; i++){
                fieldValues[currentTetrominoPtr->y_values[i]][currentTetrominoPtr->x_values[i]] = '1';
            }
            break;
        case 'J':
            for (int i = 0; i < 4; i++){
                fieldValues[currentTetrominoPtr->y_values[i]][currentTetrominoPtr->x_values[i]] = '2';
            }
            break;
        case 'O':
            for (int i = 0; i < 4; i++){
                fieldValues[currentTetrominoPtr->y_values[i]][currentTetrominoPtr->x_values[i]] = '3';
            }
            break;
        case 'I':
            for (int i = 0; i < 4; i++){
                fieldValues[currentTetrominoPtr->y_values[i]][currentTetrominoPtr->x_values[i]] = '4';
            }
            break;
        case 'S':
            for (int i = 0; i < 4; i++){
                fieldValues[currentTetrominoPtr->y_values[i]][currentTetrominoPtr->x_values[i]] = '5';
            }
            break;
        case 'Z':
            for (int i = 0; i < 4; i++){
                fieldValues[currentTetrominoPtr->y_values[i]][currentTetrominoPtr->x_values[i]] = '6';
            }
            break;
        case 'T':
            for (int i = 0; i < 4; i++){
                fieldValues[currentTetrominoPtr->y_values[i]][currentTetrominoPtr->x_values[i]] = '7';
            }
            break;
        default:
            for (int i = 0; i < 4; i++){
                fieldValues[currentTetrominoPtr->y_values[i]][currentTetrominoPtr->x_values[i]] = '1';
            }
            break;
    }
    //printf("checking if reached the top row\n");
    if (currentTetrominoPtr->y_values[3] == 0 || currentTetrominoPtr->y_values[2] == 0 || currentTetrominoPtr->y_values[1] == 0 || currentTetrominoPtr->y_values[0] == 0){
        printf("game finished\n");
        gameFinished = 1;
    }
    printf("resetting pointer\n");
    free(currentTetrominoPtr);
    currentTetrominoPtr = NULL;
    check_for_full_row();
    
}




void settle_tetromino(){
    if (currentTetrominoPtr != NULL) {
        //printf("checking if a tetromino should settle\n");
        if (currentTetrominoPtr->y_values[3] >= 19 || currentTetrominoPtr->y_values[2] >= 19 || currentTetrominoPtr->y_values[1] >= 19 || currentTetrominoPtr->y_values[0] >= 19){
            //printf("reached the lowest point\n");
            tetrominoSettled();
        } else {
            int break_loop = 0;
            for (int y = 19; y > 0; y--){
                for (int x = 0; x < 10; x++){
                    if (fieldValues[y][x] == currentTetrominoPtr->fieldValue){
                        if (fieldValues[y + 1][x] != '0' && fieldValues[y + 1][x] != currentTetrominoPtr->fieldValue){
                            //printf("found tetromino below\n");
                            tetrominoSettled();
                            break_loop = 1;
                            break;
                        }
                    }
                }
                if (break_loop) break;
            }

        }
        //printf("after skip_check\n");
    } else {
        createTetromino();
    }
}

void moveLeft(){
    if (currentTetrominoPtr != NULL){
        //printf("\033[0;31mmoving Left\033[0m\n");
        if (currentTetrominoPtr->x_values[0] > 0 && currentTetrominoPtr->x_values[1] > 0 && currentTetrominoPtr->x_values[2] > 0 && currentTetrominoPtr->x_values[3] > 0) {
            int canMove = 1;
            for (int y = 19; y >= 0; y--) {  // Start from the bottom for safe shifting
                for (int x = 0; x < 10; x++) {  // Field has 10 columns
                   if (fieldValues[y][x] == currentTetrominoPtr->fieldValue) {
                        if (fieldValues[y][x - 1] != '0' && fieldValues[y][x - 1] != currentTetrominoPtr->fieldValue) {
                            canMove = 0;
                        }
                    }
                }
            }
            if (canMove){
                clearTetromino();
                currentTetrominoPtr->x_values[0]--;
                currentTetrominoPtr->x_values[1]--;
                currentTetrominoPtr->x_values[2]--;
                currentTetrominoPtr->x_values[3]--;
                placeTetromino();
            }
        }
    }
}

void moveRight(){
    if (currentTetrominoPtr != NULL){
        //printf("\033[0;31mmoving right\033[0m\n");
        if (currentTetrominoPtr->x_values[0] < 9 && currentTetrominoPtr->x_values[1] < 9 && currentTetrominoPtr->x_values[2] < 9 && currentTetrominoPtr->x_values[3] < 9) {
            int canMove = 1;
            for (int y = 19; y >= 0; y--) {  // Start from the bottom for safe shifting
                for (int x = 0; x < 10; x++) {  // Field has 10 columns
                    if (fieldValues[y][x] == currentTetrominoPtr->fieldValue) {
                        if (fieldValues[y][x + 1] != '0' && fieldValues[y][x + 1] != currentTetrominoPtr->fieldValue) {
                            canMove = 0;
                        }
                    }
                }
            }
            if (canMove){
                clearTetromino();
                currentTetrominoPtr->x_values[0]++;
                currentTetrominoPtr->x_values[1]++;
                currentTetrominoPtr->x_values[2]++;
                currentTetrominoPtr->x_values[3]++;
                placeTetromino();
            }
        }
    }
}


void moveDown() {
    if (currentTetrominoPtr != NULL) {
        //printf("after lock\n");

        // Check if any part of the tetromino can move down (i.e., not at the bottom row)
        if (currentTetrominoPtr->y_values[0] < 19 && currentTetrominoPtr->y_values[1] < 19 && currentTetrominoPtr->y_values[2] < 19 && currentTetrominoPtr->y_values[3] < 19) {
            int canMove = 1;

            // Loop over the entire field to check if the tetromino can move down
            for (int y = 19; y >= 0; y--) {  // Start from the bottom for safe shifting
                for (int x = 0; x < 10; x++) {  // Field has 10 columns

                    // Check if this cell belongs to the current tetromino
                    if (fieldValues[y][x] == currentTetrominoPtr->fieldValue) {
                        
                        // Check if the cell below is free or occupied by a different piece
                        if (y + 1 < 20 && fieldValues[y + 1][x] != '0' && fieldValues[y + 1][x] != currentTetrominoPtr->fieldValue) {
                            printf("cannot move\n");
                            canMove = 0;
                        }
                    }
                }
            }

            // If tetromino can move, move it down
            if (canMove) {
                clearTetromino();  // Clear current position of the tetromino
                currentTetrominoPtr->y_values[0]++;
                currentTetrominoPtr->y_values[1]++;
                currentTetrominoPtr->y_values[2]++;
                currentTetrominoPtr->y_values[3]++;
                placeTetromino();  // Place tetromino in the new position
            }

        } else {
            // Reached the bottom or other boundary, handle locking tetromino here if needed
            printf("Tetromino can't move down further.\n");
        }

    } else {
        createTetromino();  // No current tetromino, create a new one
    }
}

int get_lowest_block(){
    int value = 0;
    for (int i = 0; i < 4; i++){
        if (currentTetrominoPtr->y_values[i] >= value) value = currentTetrominoPtr->y_values[i];
    }
    return value;
}
int is_in_boundries(int y, int x){
    if (y < (sizeof(fieldValues)/sizeof(char)) && x < (sizeof(fieldValues[y])/sizeof(char))) {
        return 1;
    } else {
        return 0;
    }
}

void drop() {
    if (currentTetrominoPtr != NULL) {
        int drop_for = 19 - get_lowest_block(); // Start assuming it can drop to y = 19
        int y = get_lowest_block(); // The lowest block of the tetromino
        
        for (int i = y + 1; i < 20; i++) { // Start checking from the row below the lowest block
            int can_drop = 1; // Assume all blocks can drop
            
            for (int j = 0; j < 4; j++) { 
                int new_y = currentTetrominoPtr->y_values[j] + (i - y); // Potential new y position
                int x = currentTetrominoPtr->x_values[j]; // x position remains constant
                
                // Check if the block can be placed at the new position
                if (new_y >= 20 || 
                    (fieldValues[new_y][x] != '0' && 
                     fieldValues[new_y][x] != currentTetrominoPtr->fieldValue)) {
                    can_drop = 0; // If any block cannot move, set flag to false
                    break; // No need to check other blocks if one cannot move
                }
            }

            if (!can_drop) { 
                drop_for = i - 1 - y; // Adjust drop_for to place the tetromino just above the obstruction
                break; // Stop checking further down the field
            }
        }

        // Drop the tetromino by the calculated amount
        clearTetromino();  // Remove the tetromino from its current position
        for (int i = 0; i < 4; i++) {
            currentTetrominoPtr->y_values[i] += drop_for;  // Update the y positions by the drop amount
        }
        placeTetromino();  // Place the tetromino at the new position
        settle_tetromino();
        createTetromino();
    }
}


void rotate_tetromino(){
    //printf("\033[0;31mrotating Tetromino\033[0m\n\n");
    switch(currentTetrominoPtr->fieldValue){
        case 'L':
            //printf("\033[0;32mrotating Tetromino L\033[0m\n\n");
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if (fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] + 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] - 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] - 2] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3], currentTetrominoPtr->x_values[3] - 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->x_values[3] -= 2;

                                currentTetrominoPtr->rotation = 2;
                                placeTetromino();
                            }
                        }
                    }
                    break;

                case 2:
                    if (fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] - 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] + 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3] - 2][currentTetrominoPtr->x_values[3]] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3] - 2, currentTetrominoPtr->x_values[3])){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->y_values[3] -= 2;

                                currentTetrominoPtr->rotation = 3;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                    
                case 3:
                    if (fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] - 1, currentTetrominoPtr->x_values[0] - 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] + 1, currentTetrominoPtr->x_values[2] + 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] + 2] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3], currentTetrominoPtr->x_values[3] + 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->x_values[3] += 2;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;

                case 4:
                    if (fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] - 1, currentTetrominoPtr->x_values[0] + 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] + 1, currentTetrominoPtr->x_values[2] - 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3] + 2][currentTetrominoPtr->x_values[3]] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3] + 2, currentTetrominoPtr->x_values[3])){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->y_values[3] += 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;
            }
            break;
        case 'J':
            //printf("\033[0;32mrotating Tetromino J\033[0m\n\n");
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if (fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] + 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] - 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3] - 2][currentTetrominoPtr->x_values[3]] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3] - 2, currentTetrominoPtr->x_values[3])){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->y_values[3] -= 2;

                                currentTetrominoPtr->rotation = 2;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case 2:
                    if (fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] - 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] + 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] + 2] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3], currentTetrominoPtr->x_values[3] + 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->x_values[3] += 2;

                                currentTetrominoPtr->rotation = 3;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case 3:
                    if (fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] + 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] - 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3] + 2][currentTetrominoPtr->x_values[3]] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3] + 2, currentTetrominoPtr->x_values[3])){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->y_values[3] += 2;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;

                case 4:
                    if (fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] - 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] + 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] - 2] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3], currentTetrominoPtr->x_values[3] - 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->x_values[3] -= 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;
            }
            break;
        case 'I':
            //printf("\033[0;32mrotating Tetromino I\033[0m\n\n");
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if (fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] + 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] - 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3] - 2][currentTetrominoPtr->x_values[3] - 2] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3] - 2, currentTetrominoPtr->x_values[3] - 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->x_values[3] -= 2;
                                currentTetrominoPtr->y_values[3] -= 2;

                                currentTetrominoPtr->rotation = 2;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case 2:
                    if (fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] - 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] + 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3] - 2][currentTetrominoPtr->x_values[3] + 2] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3] - 2, currentTetrominoPtr->x_values[3] + 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->x_values[3] += 2;
                                currentTetrominoPtr->y_values[3] -= 2;

                                currentTetrominoPtr->rotation = 3;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case 3:
                    if (fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] - 1, currentTetrominoPtr->x_values[0] - 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] + 1, currentTetrominoPtr->x_values[2] + 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3] + 2][currentTetrominoPtr->x_values[3] + 2] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3] + 2, currentTetrominoPtr->x_values[3] + 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->x_values[3] += 2;
                                currentTetrominoPtr->y_values[3] += 2;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;


                case 4:
                    if (fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] - 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] - 1)){
                        if (fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] + 1] == '0' && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] + 1)){
                            if (fieldValues[currentTetrominoPtr->y_values[3] - 2][currentTetrominoPtr->x_values[3] + 2] == '0' && is_in_boundries(currentTetrominoPtr->y_values[3] - 2, currentTetrominoPtr->x_values[3] + 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->x_values[3] -= 2;
                                currentTetrominoPtr->y_values[3] += 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;


            }
            break;
        case 'Z':
            //printf("\033[0;32mrotating Tetromino Z\033[0m\n");
            //printf("\033[0;32m%d\033[0m\n", currentTetrominoPtr->rotation);
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] + 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] - 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3] - 2][currentTetrominoPtr->x_values[3]] == '0' || fieldValues[currentTetrominoPtr->y_values[3] - 2][currentTetrominoPtr->x_values[3]] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[3] - 2, currentTetrominoPtr->x_values[3])){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->y_values[3] -= 2;

                                currentTetrominoPtr->rotation = 2;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case 2:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] - 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] + 1, currentTetrominoPtr->x_values[2] + 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] + 2] == '0' || fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] + 2] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[3], currentTetrominoPtr->x_values[3] + 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->x_values[3] += 2;

                                currentTetrominoPtr->rotation = 3;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case 3:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] - 1, currentTetrominoPtr->x_values[0] - 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] + 1, currentTetrominoPtr->x_values[2] - 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3] + 2][currentTetrominoPtr->x_values[3]] == '0' || fieldValues[currentTetrominoPtr->y_values[3] + 2][currentTetrominoPtr->x_values[3]] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[3] + 2, currentTetrominoPtr->x_values[3])){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->y_values[3] += 2;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case 4:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] - 1, currentTetrominoPtr->x_values[0] + 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] - 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] - 2] == '0' || fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] - 2] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[3], currentTetrominoPtr->x_values[3] - 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->x_values[3] -= 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;
            }
            break;
        case 'S':
            //printf("\033[0;32mrotating Tetromino S\033[0m\n\n");
            //printf("\033[0;32m%d\033[0m\n", currentTetrominoPtr->rotation);
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] + 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] + 1, currentTetrominoPtr->x_values[2] - 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] - 2] == '0' || fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] - 2] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[3], currentTetrominoPtr->x_values[3] - 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->x_values[3] -= 2;

                                currentTetrominoPtr->rotation = 2;
                                placeTetromino();
                            }
                        }
                    }
                    break;

                case 2:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] - 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] - 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3] - 2][currentTetrominoPtr->x_values[3]] == '0' || fieldValues[currentTetrominoPtr->y_values[3] - 2][currentTetrominoPtr->x_values[3]] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[3] - 2, currentTetrominoPtr->x_values[3])){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->y_values[3] -= 2;

                                currentTetrominoPtr->rotation = 3;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case 3:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] - 1, currentTetrominoPtr->x_values[0] - 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] + 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] + 2] == '0' || fieldValues[currentTetrominoPtr->y_values[3]][currentTetrominoPtr->x_values[3] + 2] == currentTetrominoPtr->fieldValue )&& is_in_boundries(currentTetrominoPtr->y_values[3], currentTetrominoPtr->x_values[3] + 2)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->x_values[3] += 2;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case 4:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] - 1, currentTetrominoPtr->x_values[0] + 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] + 1, currentTetrominoPtr->x_values[2] + 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3] + 2][currentTetrominoPtr->x_values[3]] == '0' || fieldValues[currentTetrominoPtr->y_values[3] + 2][currentTetrominoPtr->x_values[3]] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[3] + 2, currentTetrominoPtr->x_values[3])){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->y_values[3] += 2;

                                currentTetrominoPtr->rotation = 1;
                                placeTetromino();
                            }
                        }
                    }
                    break;
            }
            break;

        case 'T':
            //printf("\033[0;32mrotating Tetromino T\033[0m\n\n");
            //printf("\033[0;32m%d\033[0m\n", currentTetrominoPtr->rotation);
            switch(currentTetrominoPtr->rotation){
                case 1:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] + 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] - 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3] - 1][currentTetrominoPtr->x_values[3] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[3] - 1][currentTetrominoPtr->x_values[3] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[3] - 1, currentTetrominoPtr->x_values[3] + 1)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->x_values[3] += 1;
                                currentTetrominoPtr->y_values[3] -= 1;

                                currentTetrominoPtr->rotation = 2;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case 2:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] + 1][currentTetrominoPtr->x_values[0] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] + 1, currentTetrominoPtr->x_values[0] - 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] - 1][currentTetrominoPtr->x_values[2] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] - 1, currentTetrominoPtr->x_values[2] + 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3] + 1][currentTetrominoPtr->x_values[3] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[3] + 1][currentTetrominoPtr->x_values[3] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[3] + 1, currentTetrominoPtr->x_values[3] + 1)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] += 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] -= 1;
                                currentTetrominoPtr->x_values[3] += 1;
                                currentTetrominoPtr->y_values[3] += 1;

                                currentTetrominoPtr->rotation = 3;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case 3:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] - 1, currentTetrominoPtr->x_values[0] + 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] + 1, currentTetrominoPtr->x_values[2] - 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3] + 1][currentTetrominoPtr->x_values[3] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[3] + 1][currentTetrominoPtr->x_values[3] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[3] + 1, currentTetrominoPtr->x_values[3] - 1)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] -= 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] += 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->y_values[3] += 1;
                                currentTetrominoPtr->x_values[3] -= 1;

                                currentTetrominoPtr->rotation = 4;
                                placeTetromino();
                            }
                        }
                    }
                    break;
                case 4:
                    if ((fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] + 1] == '0' || fieldValues[currentTetrominoPtr->y_values[0] - 1][currentTetrominoPtr->x_values[0] + 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[0] - 1, currentTetrominoPtr->x_values[0] + 1)){
                        if ((fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[2] + 1][currentTetrominoPtr->x_values[2] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[2] + 1, currentTetrominoPtr->x_values[2] - 1)){
                            if ((fieldValues[currentTetrominoPtr->y_values[3] - 1][currentTetrominoPtr->x_values[3] - 1] == '0' || fieldValues[currentTetrominoPtr->y_values[3] - 1][currentTetrominoPtr->x_values[3] - 1] == currentTetrominoPtr->fieldValue) && is_in_boundries(currentTetrominoPtr->y_values[3] - 1, currentTetrominoPtr->x_values[3] - 1)){
                                clearTetromino();
                                currentTetrominoPtr->x_values[0] += 1;
                                currentTetrominoPtr->y_values[0] -= 1;
                                currentTetrominoPtr->x_values[2] -= 1;
                                currentTetrominoPtr->y_values[2] += 1;
                                currentTetrominoPtr->x_values[3] -= 1;
                                currentTetrominoPtr->y_values[3] -= 1;

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
}

void free_pointer(){
    free(currentTetrominoPtr);
    currentTetrominoPtr = NULL;
    fprintf(stdout, "pointer freed\n");
}




void prepare(){
    //printf("preparing playing field\n");
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


