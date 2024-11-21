#include "game_upload.h"

void uploadFile(const char *sourceFileName) {
    FILE *sourceFile, *destFile;
    char destFilePath[256];
    char buffer[1024];
    size_t bytesRead;

    // Open the source file for reading
    sourceFile = fopen(sourceFileName, "rb");
    if (!sourceFile) {
        perror("Error opening source file");
        return;
    }

    // Create the destination file path
    snprintf(destFilePath, sizeof(destFilePath), "%s%s", UPLOAD_DIR, sourceFileName);

    // Open the destination file for writing
    destFile = fopen(destFilePath, "wb");
    if (!destFile) {
        perror("Error creating destination file");
        fclose(sourceFile);
        return;
    }

    // Read from source and write to destination
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    // Close files
    fclose(sourceFile);
    fclose(destFile);

    printf("File '%s' successfully uploaded to '%s'.\n", sourceFileName, UPLOAD_DIR);
    printf(" we will let you know once it is rectified ");
}
