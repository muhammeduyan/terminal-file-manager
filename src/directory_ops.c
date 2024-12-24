#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>   // opendir, readdir
#include <sys/stat.h> // stat
#include <string.h>
#include "directory_ops.h"
#include <inttypes.h> // PRIu64 için
#include <unistd.h> 

void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    struct stat file_stat;
    char full_path[1024];

    printf("Contents of %s:\n", path);
    while ((entry = readdir(dir)) != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &file_stat) == 0) {
            printf("%s\t%" PRIu64 " bytes\t%s\n",
                   S_ISDIR(file_stat.st_mode) ? "DIR" : "FILE",
                   (uint64_t)file_stat.st_size,
                   entry->d_name);
        } else {
            perror("Error retrieving file info");
        }
    }

    closedir(dir);
}


void create_directory(const char *path)
{
    if (mkdir(path, 0755) == 0)
    {
        printf("Directory created: %s\n", path);
    }
    else
    {
        perror("Error creating directory");
    }
}

void delete_directory(const char *path)
{
    if (rmdir(path) == 0)
    {
        printf("Directory deleted: %s\n", path);
    }
    else
    {
        perror("Error deleting directory");
    }
}

void search_file(const char *path, const char *filename) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    char full_path[1024];
    int found = 0;

    printf("Searching for '%s' in '%s':\n", filename, path);
    while ((entry = readdir(dir)) != NULL) {
        // Eğer dosya adı verilen isimle eşleşiyorsa
        if (strstr(entry->d_name, filename) != NULL) {
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            printf("Found: %s\n", full_path);
            found = 1;
        }
    }

    if (!found) {
        printf("No files matching '%s' found in '%s'.\n", filename, path);
    }

    closedir(dir);
}