#include "../include/get_files_path.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    char * path = return_folders_path();
    fprintf(stdout, "test_path_reading: %s\n", path);
    free(path);

    return 0;
}
