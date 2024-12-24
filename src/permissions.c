#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // chmod
#include "permissions.h"

void change_permissions(const char *path, int mode) {
    if (chmod(path, mode) == 0) {
        printf("Permissions changed successfully for %s\n", path);
    } else {
        perror("Error changing permissions");
    }
}