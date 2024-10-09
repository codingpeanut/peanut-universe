#include <stdio.h>
#include <stdlib.h>

int file_exist(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp) {
        fclose(fp);
        return 1; // File exists
    }
    return 0; // File doesn't exist
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
        if (source[0] == 'q') return 0;
        printf("File not found. Try again or enter 'q' to quit.\n");
    }

    // Get destination file name and handle existing files
    while (1) {
        printf("Enter destination file name: ");
        fgets(destination, sizeof(destination), stdin);
        destination[strcspn(destination, "\n")] = 0;
        if (file_exist(destination)) {
            printf("File exists. (a) New name (b) Overwrite (c) Quit: ");
            char option = getchar();
            getchar(); // Consume newline
            if (option == 'a') continue; // Ask for a new destination
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
