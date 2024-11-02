#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/get_files_path.h"

#ifdef __unix__
    #include <errno.h>
    #include <sys/stat.h>  // For mkdir and stat functions
#endif

#ifdef WIN64
    #include <windows.h>
    #include <shlobj.h>
#endif

#ifdef __unix__

int does_file_exist(const char * filepath){
    struct stat buffer;
    return (stat(filepath, &buffer) == 0);
}

char* output;

char* return_folders_path(){
    char command[] = "xdg-user-dir DOCUMENTS";
    char buffer[128];
    char directory[] = "/myGames/Jtetris/";

    FILE * pipe = popen(command, "r");
    if (pipe == NULL){
        perror("Running Command Failed");
        return NULL;
    }
    fgets(buffer, sizeof(buffer), pipe);

    for (int i = 0; i < sizeof(buffer)/sizeof(char); i++){
        if (buffer[i] == '\n'){
            buffer[i] = '\0';
        }
    }
    output = (char *)malloc(strlen(buffer) + strlen(directory) + 1);

    strcpy(output, buffer);
    strcat(output, directory);
    fprintf(stdout, "return_folders_path: %s\n", output);

    if (!does_file_exist(output)){
        errno = 2;
        fprintf(stderr, "Path: %s: ", output);
        perror("");
        fprintf(stderr, "\n");
        free(output);
        output = NULL;
    }

    return output;
}

void free_folders_ptr(){
    free(output);
}


#endif

#ifdef WIN64

char* output;

char* return_folders_path() {
    // GUID for the Documents folder
    PWSTR path = NULL;
    HRESULT result = SHGetKnownFolderPath(&FOLDERID_Documents, 0, NULL, &path);

    if (result != S_OK) {
        fprintf(stderr, "Error retrieving the Documents path.\n");
        return NULL;
    }

    // Convert the wide character string to a regular char string
    size_t size = wcslen(path) + 1;
    char *buffer = (char *)malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        CoTaskMemFree(path);
        return NULL;
    }
    wcstombs(buffer, path, size);

    // Directory to append
    char directory[] = "/myGames/Jtetris/";

    // Allocate memory for the combined path
    output = (char *)malloc(strlen(buffer) + strlen(directory) + 1);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(buffer);
        CoTaskMemFree(path);
        return NULL;
    }

    // Create the final path
    strcpy(output, buffer);
    strcat(output, directory);

    // Print the result for debugging
    fprintf(stdout, "return_folders_path: %s\n", output);

    // Free allocated memory for `path` and `buffer`
    free(buffer);
    CoTaskMemFree(path);

    return output;
}

void free_folders_ptr(){
    free(output);
}

int does_file_exist(const char * filepath){
// Windows-specific method
    DWORD attributes = GetFileAttributesA(filepath);
    return (attributes != INVALID_FILE_ATTRIBUTES && 
            !(attributes & FILE_ATTRIBUTE_DIRECTORY));
}
#endif
