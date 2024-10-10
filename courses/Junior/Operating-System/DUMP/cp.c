#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        // Ensure correct number of arguments (source file, destination file)
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int source_fd, dest_fd;  // File descriptors for source and destination files
    char buffer[BUFFER_SIZE]; // Buffer for reading file data
    ssize_t bytes_read, bytes_written;

    // Open the source file in read-only mode
    source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open the destination file in write-only mode, create it if necessary, set file permissions
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening/creating destination file");
        close(source_fd);
        exit(EXIT_FAILURE);
    }

    // Copy the file contents using a loop
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    // Check if the read operation encountered an error
    if (bytes_read == -1) {
        perror("Error reading source file");
    }

    // Close the file descriptors
    close(source_fd);
    close(dest_fd);

    return 0;
}
