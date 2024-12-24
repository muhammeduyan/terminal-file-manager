#ifndef DIRECTORY_OPS_H
#define DIRECTORY_OPS_H

void list_directory(const char *path);
void create_directory(const char *path);
void delete_directory(const char *path);
void search_file(const char *path, const char *filename);

#endif // DIRECTORY_OPS_H