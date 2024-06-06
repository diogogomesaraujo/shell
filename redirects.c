#include "shell.h"

int redirects(int numargs, char *args[]) {
    // i) tratar do redirect do 2>
    if (numargs < 3)
        return numargs; // Guard the following section

    if (strcmp(args[numargs - 2], "2>") == 0) {
        int fd = creat(args[numargs - 1], 0644);
        if (fd < 0) {
            perror(NULL);
            exit(1); /* indicar um erro */
        }
        dup2(fd, STDERR_FILENO);
        close(fd);
        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }

    // ii) tratar do redirect do >
    if (numargs < 3)
        return numargs; // Guard the following section

    if (strcmp(args[numargs - 2], ">") == 0) {
        int fd = creat(args[numargs - 1], 0644);
        if (fd < 0) {
            perror(NULL);
            exit(1); /* indicar um erro */
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }

    // iii) tratar do redirect do >>
    if (numargs < 3)
        return numargs; // Guard the following section

    if (strcmp(args[numargs - 2], ">>") == 0) {
        int fd = open(args[numargs - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (fd < 0) {
            perror(NULL);
            exit(1); /* indicar um erro */
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }

    // iv) tratar do redirect do <
    if (numargs < 3)
        return numargs; // Guard the following section

    if (strcmp(args[numargs - 2], "<") == 0) {
        int fd = open(args[numargs - 1], O_RDONLY);
        if (fd < 0) {
            perror(NULL);
            exit(1); /* indicar um erro */
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }

    return numargs; // devolver o número de argumentos a passar para execvp
}
