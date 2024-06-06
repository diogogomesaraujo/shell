#include "shell.h"

void setx(char *file, char *mode) {
    int new_mode = strtol(mode, NULL, 8);
    if (chmod(file, new_mode) < 0) {
        perror("chmod");
    }
}

void removerl(char *file, char *mode) {
    int new_mode = strtol(mode, NULL, 8);
    if (chmod(file, new_mode) < 0) {
        perror("chmod");
    }
}
