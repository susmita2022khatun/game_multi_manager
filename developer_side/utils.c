#include "utils.h"

void list_files() {
    printf("\nListing files in '%s' directory:\n", UPLOAD_DIR);
    system("ls " UPLOAD_DIR);
}

void display_file_content() {
    char filename[MAX_FILENAME];
    char filepath[MAX_FILENAME + sizeof(UPLOAD_DIR)];
    char command[MAX_FILENAME + sizeof(UPLOAD_DIR) + 20];

    printf("\nEnter the filename to display: ");
    scanf("%s", filename);

    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);
    printf("\nDisplaying content of '%s':\n", filepath);

    snprintf(command, sizeof(command), "cat %s", filepath);
    int result = system(command);

    if (result != 0) {
        printf("Error: Could not display file. Ensure the file exists and you have read permissions.\n");
    }
}


void compile_copy_content() {
   
        printf("Compilation successful. Executing './copy_content'...\n");
        int exec_result = system("cd games && ./a.out");
        if (exec_result != 0) {
            printf("Error: Execution of './copy_content' failed. Please check your code.\n");
        }
    
}



