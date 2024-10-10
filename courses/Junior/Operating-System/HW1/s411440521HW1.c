#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char source[100], destination[100];
    FILE *src, *dest;
    char buffer[1024];
    size_t bytes;

    // Get source file name and open it
    while (1) {
        printf("Enter source file name: ");
        fgets(source, sizeof(source), stdin);
        source[strcspn(source, "\n")] = 0; // Remove newline
        src = fopen(source, "rb");
        if (src) break;
        if (strcmp(source, "q") == 0) return 0;
        printf("File not found. Try again or enter 'q' to quit.\n");
    }

    // Get destination file name and handle existing files
    while (1) {
        printf("Enter destination file name: ");
        fgets(destination, sizeof(destination), stdin);
        destination[strcspn(destination, "\n")] = 0;

        // Check if source and destination are the same
        if (strcmp(source, destination) == 0) {
            printf("Source and destination cannot be the same!\n");
            exit(EXIT_FAILURE);
        }

        dest = fopen(destination, "rb");
        if (dest) {
            fclose(dest);
            printf("File exists. (a) Enter new name (b) Overwrite (c) Quit\n");
            char option = getchar();
            getchar(); // To consume newline
            if (option == 'a') continue; // Enter new file name
            if (option == 'c') return 0; // Quit
            // If choosing to overwrite, do nothing and break the loop
        }
        break; // File does not exist or chose to overwrite, break the loop
    }

    // Open destination file and copy contents
    dest = fopen(destination, "wb");
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);
    printf("File copied successfully!\n");
    return 0;
}
