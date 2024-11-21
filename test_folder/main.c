#include "developer_side/utils.h"

int main() {
    int choice;

    while (1) {
        printf("\n--- File Operations Menu ---\n");
        printf("1. List uploaded files\n");
        printf("2. Display the content of a file\n");
        printf("3. Compile 'copy_content.c'\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list_files();
                break;
            case 2:
                display_file_content();
                break;
            case 3:
                compile_copy_content();
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
