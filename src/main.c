#include <stdio.h>
#include <string.h>
#include "file_operations.h"
#include "permissions.h"
#include "logger.h"
#include "directory_ops.h"

void display_help() {
    printf("\nAvailable Commands:\n");
    printf("  read <file_path>         - Read the contents of a file.\n");
    printf("  write <file_path> <text> - Write text to a file.\n");
    printf("  copy <src> <dest>        - Copy a file to a new location.\n");
    printf("  move <src> <dest>        - Move a file to a new location.\n");
    printf("  delete <file_path>       - Delete a file.\n");
    printf("  chmod <file_path> <mode> - Change file permissions (e.g., 0777).\n");
    printf("  list <directory_path>    - List the contents of a directory.\n");
    printf("  mkdir <directory_path>   - Create a new directory.\n");
    printf("  rmdir <directory_path>   - Remove an empty directory.\n");
    printf("  search <dir> <file_name> - Search for a file in a directory.\n");
    printf("  exit                     - Exit the program.\n");
    printf("  help                     - Display this help menu.\n");
    printf("\n");
}

int main()
{
    char command[256];
    printf("Terminal File Manager\n");
    printf("Type a command to start:\n");

    while (1)
    {
        printf("> ");
        fgets(command, 256, stdin);
        command[strcspn(command, "\n")] = '\0'; // Remove newline character
        
        if (strncmp(command, "read", 4) == 0)
        {
            char file_path[256];
            sscanf(command + 5, "%s", file_path);
            read_file(file_path);
            log_operation("read", file_path);
        }
        else if (strncmp(command, "write", 5) == 0)
        {
            char file_path[256], content[256];
            sscanf(command + 6, "%s %[^\n]", file_path, content);
            write_file(file_path, content);
            log_operation("write", file_path);
        }
        else if (strncmp(command, "copy", 4) == 0)
        {
            char src_path[256], dest_path[256];
            sscanf(command + 5, "%s %s", src_path, dest_path);
            copy_file(src_path, dest_path);
            log_operation("copy", src_path);
        }
        else if (strncmp(command, "move", 4) == 0)
        {
            char src_path[256], dest_path[256];
            sscanf(command + 5, "%s %s", src_path, dest_path);
            move_file(src_path, dest_path);
            log_operation("move", src_path);
        }
        else if (strncmp(command, "delete", 6) == 0)
        {
            char file_path[256];
            sscanf(command + 7, "%s", file_path);
            delete_file(file_path);
            log_operation("delete", file_path);
        }
        else if (strncmp(command, "chmod", 5) == 0)
        {
            char path[256];
            int mode;
            sscanf(command + 6, "%s %o", path, &mode); // Octal mode input
            change_permissions(path, mode);
            log_operation("chmod", path);
        }
        else if (strncmp(command, "mkdir", 5) == 0)
        {
            char path[256];
            sscanf(command + 6, "%s", path);
            create_directory(path);
            log_operation("mkdir", path);
        }
        else if (strncmp(command, "rmdir", 5) == 0)
        {
            char path[256];
            sscanf(command + 6, "%s", path);
            delete_directory(path);
            log_operation("rmdir", path);
        }
        else if (strncmp(command, "list", 4) == 0)
        {
            char path[256];
            sscanf(command + 5, "%s", path);
            list_directory(path);
            log_operation("list", path);
        }
        else if (strncmp(command, "search", 6) == 0)
        {
            char path[256], filename[256];
            sscanf(command + 7, "%s %s", path, filename);
            search_file(path, filename);
            log_operation("search", filename);
        }
        else if (strcmp(command, "help") == 0) {
            display_help();
            log_operation("help", "Displayed help menu");
        }
        else if (strcmp(command, "exit") == 0)
        {
            log_operation("exit", "Program terminated");
            break;
        }
        else
        {
            printf("Unknown command. Available commands: read, write, copy, move, delete, chmod, exit\n");
        }
    }

    return 0;
}