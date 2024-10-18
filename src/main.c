#include <stdio.h>
#include "../include/game.h"
#include "../include/ui.h"
#include <pthread.h>


int main(int argc, char *argv[]){
    pthread_t game_thead;
    printf("starting game loop\n");
    int result = pthread_create(&game_thead, NULL, gameLoop, NULL);
    if (result != 0){
        printf("couldnt create thread\n");
    } else {
        create_gui(argc, argv, 0);
    }

    return 0;
}
