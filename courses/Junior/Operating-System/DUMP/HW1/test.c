#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int file_exist(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp) {
        fclose(fp);
        return 1; // File exists
    }
    return 0; // File doesn't exist
}

void copyFile(const char *srcPath, const char *destPath) {
    FILE *src = fopen(srcPath, "rb");
    FILE *dest = fopen(destPath, "wb");
    if (!src || !dest) {
        perror("File opening failed");
        if (src) fclose(src);
        exit(EXIT_FAILURE);
    }
    
    int ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }
    fclose(src);
    fclose(dest);
}

void moveFile(const char *source, const char *destination) {
    if (rename(source, destination) != 0) {
        perror("Error moving file");
    } else {
        printf("File moved from '%s' to '%s'.\n", source, destination);
    }
}

int main() {
    char source[100], destination[100];

    // Get source file name
    while (1) {
        printf("Enter source file name (or 'q' to quit): ");
        fgets(source, sizeof(source), stdin);
        if (source[0] == 'q') return 0;
        source[strcspn(source, "\n")] = 0;
        if (file_exist(source)) break;
        printf("File not found. Try again.\n");
    }

    // Get destination file name
    while (1) {
        printf("Enter destination file name: ");
        fgets(destination, sizeof(destination), stdin);
        destination[strcspn(destination, "\n")] = 0;

        if (file_exist(destination)) {
            printf("File exists. (a) New name (b) Overwrite (c) Quit: ");
            char option = getchar();
            getchar(); // Consume newline
            
            if (option == 'a') continue; // Ask for a new destination
            if (option == 'b') {
                // Create a temporary file name
                char tempPath[100];
                snprintf(tempPath, sizeof(tempPath), "%s.tmp", source);
                
                // Copy the source file to the temporary file
                copyFile(source, tempPath);
                
                // Move the temporary file to the destination
                moveFile(tempPath, destination);
                return 0;
            }
            if (option == 'c') return 0; // Quit
        }
        break; // Valid destination
    }

    moveFile(source, destination);
    return 0;
}
