#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char source[100], destination[100];
    FILE *src, *dest;
    int bytes_copied = 0;

    // Get source file name
    do {
        printf("Enter source file name: ");
        fgets(source, sizeof(source), stdin);
        source[strcspn(source, "\n")] = 0;
        src = fopen(source, "rb");
        if (src == NULL) {
            printf("File not found. Please re-enter or enter 'q' to quit.\n");
        }
    } while (src == NULL && source[0] != 'q');

    if (source[0] == 'q') {
        return 0;
    }

    // Get destination file name
    do {
        printf("Enter destination file name: ");
        fgets(destination, sizeof(destination), stdin);
        destination[strcspn(destination, "\n")] = 0;
        dest = fopen(destination, "rb");
        if (dest != NULL) {
            printf("File already exists. Choose an option:\n");
            printf("(a) Enter a new name (b) Overwrite (c) Quit\n");
            char option;
            scanf(" %c", &option);
            if (option == 'a') {
                continue;
            } else if (option == 'b') {     // can't copy a file onto itself 
                fclose(dest);
                return 0;
            } else {
                return 0;
            }
        } else {
            break;
        }
    } while (1);

    // Open destination file in write mode
    dest = fopen(destination, "wb");

    // Copy file contents in chunks for better performance
    size_t chunk_size = 1024;
    char buffer[chunk_size];
    while ((bytes_copied = fread(buffer, 1, chunk_size, src)) > 0) {
        fwrite(buffer, 1, bytes_copied, dest);
    }

    // Close files
    fclose(src);
    fclose(dest);

    printf("File copied successfully!\n");
    return 0;
}
