#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char source[100], target[100];
    FILE *src, *tgt;
    char buffer[1024];
    size_t bytes;

    // Get source file name and open it
    printf("Source File: ");
    fgets(source, sizeof(source), stdin);
    source[strcspn(source, "\n")] = '\0'; // Remove newline
    
	if (!(src = fopen(source, "rb"))) {
		printf("Source file not found.\n");
		exit(EXIT_FAILURE);
	}

    // Get tgtination file name and handle existing files
    while (1) {
        printf("Target File: ");
        fgets(target, sizeof(target), stdin);
        target[strcspn(target, "\n")] = '\0';

        // Check if source and target are the same
        if (strcmp(source, target) == 0) {
            printf("Source and target cannot be the same!\n");
            exit(EXIT_FAILURE);
        }

        if (tgt = fopen(target, "rb")) {
            fclose(tgt);
            printf("File exists. (a) Enter new name (b) Overwrite (c) Quit\n");
            char option = getchar();
            getchar(); // To consume newline
            if (option == 'a') continue; // Enter new file name
            if (option == 'c') return 0; // Quit
            // If choosing to overwrite, do nothing and break the loop
        }
        break; // File does not exist or chose to overwrite, break the loop
    }

    // Open target file and copy contents
	if (!(tgt = fopen(target, "wb"))) {
        perror("Error opening target file");
        fclose(src); // Close source file before exiting
        exit(EXIT_FAILURE);
    }

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, tgt);
    }

    printf("File copied successfully!\n");
    fclose(src);
    fclose(tgt);
    return 0;
}
