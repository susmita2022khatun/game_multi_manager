#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void extractFunctionNames(const char *sourceFile, const char *headerFile) {
    FILE *source, *header;
    char line[1024];
    char functionName[100];
    char tempContent[1024 * 50] = "";  
    int currentLine = 0;

    // Open the source file for reading
    source = fopen(sourceFile, "r");
    if (!source) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Read the source file to extract function names
    char extractedFunctions[1024] = "";  // Buffer for new function declarations
    while (fgets(line, sizeof(line), source)) {
        if (strstr(line, "void") && strstr(line, "(")) {
            char *start = strchr(line, ' ');
            char *end = strchr(line, '(');
            if (start && end && end > start) {
                strncpy(functionName, start + 1, end - start - 1);
                functionName[end - start - 1] = '\0';  
                sprintf(extractedFunctions + strlen(extractedFunctions), "void %s();\n", functionName);
            }
        }
    }
    fclose(source); 

    // Read the header file into memory and add new function names at line 6
    header = fopen(headerFile, "r");
    if (!header) {
        perror("Error opening header file");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), header)) {
        currentLine++;
        strcat(tempContent, line);  
        if (currentLine == 6) {
            strcat(tempContent, extractedFunctions);  // Insert the new function names after line 6
        }
    }
    fclose(header);

    // Rewrite the updated content back to the header file
    header = fopen(headerFile, "w");
    if (!header) {
        perror("Error opening header file for writing");
        exit(EXIT_FAILURE);
    }
    fputs(tempContent, header);
    fclose(header);
    printf("Function names successfully added to '%s'.\n", headerFile);
}


void copyContentWithOffsetAndDelete(const char *sourceFile, const char *destFile) {
    FILE *source, *dest;
    char buffer[1024];
    size_t bytesRead;

    // Open the source file for reading
    source = fopen(sourceFile, "r");
    if (!source) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open the destination file for appending
    dest = fopen(destFile, "a");
    if (!dest) {
        perror("Error opening destination file");
        fclose(source);
        exit(EXIT_FAILURE);
    }

    // Add two new lines before writing content
    fprintf(dest, "\n\n");

    // Read content from source and write to destination
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    // Close both files
    fclose(source);
    fclose(dest);

   /* Delete the source file
    if (remove(sourceFile) == 0) {
        printf("Source file '%s' deleted successfully.\n", sourceFile);
    } else {
        perror("Error deleting source file");
    }
*/
    printf("Content successfully copied from '%s' to '%s'.\n", sourceFile, destFile);
}


int count_lines_in_file(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) return 0;

    int lines = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') lines++;
    }

    fclose(file);
    return lines;
}

void construct_menu(const char *sourceFile, const char *destinationFile) {
    FILE *source, *destination;
    char line[1024];
    char functionName[100];

    // Open the source file for reading
    source = fopen(sourceFile, "r");
    if (!source) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open the destination file for appending
    destination = fopen(destinationFile, "a");
    if (!destination) {
        perror("Error opening destination file");
        fclose(source);
        exit(EXIT_FAILURE);
    }

    // Count the current number of lines in the destination file
    int currentLine = count_lines_in_file(destinationFile) + 1;

    // Read the source file to extract function names
    while (fgets(line, sizeof(line), source)) {
        if (strstr(line, "void") && strstr(line, "(")) {
            char *start = strchr(line, ' ');
            char *end = strchr(line, '(');
            if (start && end && end > start) {
                strncpy(functionName, start + 1, end - start - 1);
                functionName[end - start - 1] = '\0';  
                fprintf(destination, "%d. %s\n", currentLine, functionName); // Use line numbers
                currentLine++;
            }
        }
    }

    // Close files
    fclose(source);
    fclose(destination);

    printf("Menu successfully constructed and appended to '%s'.\n", destinationFile);
}


void headerDictionary(const char *sourceFile, const char *headerFile) {
    FILE *source, *header;
    char line[1024];
    char functionName[100];
    char tempContent[1024 * 120] = "";  
    int currentLine = 0;

    // Open the source file for reading
    source = fopen(sourceFile, "r");
    if (!source) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Read the source file to extract function names
    char extractedFunctions[1024] = "";  // Buffer for new function declarations
    while (fgets(line, sizeof(line), source)) {
        if (strstr(line, "void") && strstr(line, "(")) {
            char *start = strchr(line, ' ');
            char *end = strchr(line, '(');
            if (start && end && end > start) {
                strncpy(functionName, start + 1, end - start - 1);
                functionName[end - start - 1] = '\0';  
                snprintf(extractedFunctions + strlen(extractedFunctions),
                         sizeof(extractedFunctions) - strlen(extractedFunctions),
                         "	{ \"%s\", %s },\n", functionName, functionName);
            }
        }
    }
    fclose(source); 

    // Read the header file into memory and add new function names at line 6
    header = fopen(headerFile, "r");
    if (!header) {
        perror("Error opening header file");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), header)) {
        currentLine++;
        strcat(tempContent, line);  
        if (currentLine == 6) {
            strcat(tempContent, extractedFunctions);  // Insert the new function names after line 6
        }
    }
    fclose(header);

    // Rewrite the updated content back to the header file
    header = fopen(headerFile, "w");
    if (!header) {
        perror("Error opening header file for writing");
        exit(EXIT_FAILURE);
    }
    fputs(tempContent, header);
    fclose(header);
    printf("Function names successfully added to dictionary of '%s'.\n", headerFile);
}




int main() {
    const char *sourceFile = "../upload/2.c";
    const char *destFile = "game_com.c";
    const char *headerFile = "game_com.h"; 
    const char *menu_file = "../menu.txt";

    extractFunctionNames(sourceFile, headerFile);
    construct_menu(sourceFile, menu_file);
    copyContentWithOffsetAndDelete(sourceFile, destFile);
    headerDictionary(sourceFile, destFile);

    return 0;
}

