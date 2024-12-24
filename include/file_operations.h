#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

void read_file(const char *file_path);
void write_file(const char *file_path, const char *content);
void copy_file(const char *src_path, const char *dest_path);
void move_file(const char *src_path, const char *dest_path);
void delete_file(const char *file_path);

#endif // FILE_OPERATIONS_H