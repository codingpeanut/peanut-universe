#include <stdio.h>
#include <stdlib.h>

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

void prompt_source_file(char *source) {
    while (1) {
        printf("Enter source file name: ");
        scanf("%s", source);
        if (file_exists(source)) {
            break;
        } else {
            char choice;
            printf("File does not exist. Try again or press 'q' to quit: ");
            scanf(" %c", &choice);
            if (choice == 'q') {
                exit(0);
            }
        }
    }
}

void prompt_destination_file(char *destination) {
    while (1) {
        printf("Enter destination file name: ");
        scanf("%s", destination);
        if (file_exists(destination)) {
            char choice;
            printf("File already exists. Choose an option: (a) Enter another name, (b) Overwrite, (c) Quit: ");
            scanf(" %c", &choice);
            if (choice == 'a') {
                continue;
            } else if (choice == 'b') {
                break;  // Proceed to overwrite
            } else if (choice == 'c') {
                exit(0);
            }
        } else {
            break;  // File doesn't exist, continue
        }
    }
}

void copy_file(const char *source, const char *destination) {
    FILE *src = fopen(source, "rb");
    FILE *dest = fopen(destination, "wb");
    if (!src || !dest) {
        printf("Error opening files.\n");
        exit(1);
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);
    printf("File copied successfully!\n");
}

int main() {
    char source[256], destination[256];

    prompt_source_file(source);
    prompt_destination_file(destination);
    copy_file(source, destination);

    return 0;
}

