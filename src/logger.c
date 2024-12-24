#include <stdio.h>
#include <time.h>
#include "logger.h"

void log_operation(const char *operation, const char *details) {
    FILE *log_file = fopen("logs/operations.log", "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    // Tarih ve saat bilgisi
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    fprintf(log_file, "[%02d-%02d-%d %02d:%02d:%02d] %s: %s\n",
            local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
            local->tm_hour, local->tm_min, local->tm_sec,
            operation, details);

    fclose(log_file);
}