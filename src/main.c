#include <stdio.h>
#include "../include/game.h"
#include "../include/ui.h"
#include <pthread.h>
#include "../include/get_files_path.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int check_for_files(){
    char *base_path = return_folders_path();
    char textures_path[strlen(base_path) + strlen("textures/") + 1];
    char textures_addon[] = "textures/";
    strcpy(textures_path, base_path);
    strcat(textures_path, textures_addon);
    free_folders_ptr();
    if (!does_file_exist(textures_path)){
        errno = 2;
        fprintf(stderr, "Path: %s: ", textures_path);
        perror("");
        return 0;
    } else {
        errno = 0;
        fprintf(stderr, "Path: %s: ", textures_path);
        perror("");
    }

    char tetromino_icons[][9] = {"i.png", "j.png", "l.png", "null.png", "o.png", "s.png", "t.png", "z.png"};
    for (int i = 0; i < 8; i++){
        char path[strlen(textures_path) + strlen(tetromino_icons[i]) + 1]; 
        printf("after path decl.\n");
        printf("1: %s\n", tetromino_icons[i]);
        strcpy(path, textures_path);
        fprintf(stdout, "2: %s\n", path);
        strcat(path, tetromino_icons[i]);
        fprintf(stdout, "3: %s\n", path);
        
        if (!does_file_exist(path)){
            errno = 2;
            fprintf(stderr, "Icon: %s: ", path);
            perror("");
            return 0;
        }
    }
    errno = 0;
    perror("Tetromino Icons found");
    return 1;
}

int main(int argc, char *argv[]){
    int are_files_present = check_for_files();
    create_gui(argc, argv, are_files_present);

    return 0;
}
