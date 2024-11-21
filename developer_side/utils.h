#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOAD_DIR "upload/" // Directory where uploaded files are stored
#define MAX_FILENAME 256

void list_files();
void display_file_content();
void compile_copy_content();

#endif

