#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // open, O_RDONLY, O_WRONLY
#include <unistd.h> // read, write, close
#include <string.h>
#include "file_operations.h"

void read_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

void write_file(const char *file_path, const char *content) {
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        perror("Error creating file");
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
    printf("Content written to %s\n", file_path);
}

void copy_file(const char *src_path, const char *dest_path) {
    int src = open(src_path, O_RDONLY);
    if (src < 0) {
        perror("Error opening source file");
        return;
    }

    int dest = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        perror("Error opening destination file");
        close(src);
        return;
    }

    char buffer[1024];
    ssize_t bytes;
    while ((bytes = read(src, buffer, sizeof(buffer))) > 0) {
        if (write(dest, buffer, bytes) != bytes) {
            perror("Error writing to destination file");
            break;
        }
    }

    if (bytes < 0) {
        perror("Error reading from source file");
    }

    close(src);
    close(dest);
    printf("File copied from %s to %s\n", src_path, dest_path);
}

void move_file(const char *src_path, const char *dest_path) {
    if (rename(src_path, dest_path) == 0) {
        printf("File moved from %s to %s\n", src_path, dest_path);
    } else {
        perror("Error moving file");
    }
}

void delete_file(const char *file_path) {
    if (unlink(file_path) == 0) {
        printf("File deleted: %s\n", file_path);
    } else {
        perror("Error deleting file");
    }
}