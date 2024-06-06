// redirects.c
// redirects tratamento dos simbolos por ordem inversa: i) 2> ii) > OU >> iii) <

#include "shell.h"

int redirects(int numargs, char *args[])
{
    // i tratar do redirect do 2>
    if (numargs < 3)
        return numargs; // Guard the following section
    else if (strcmp(args[numargs - 2], "2>") == 0)
    {
        int fd = creat(args[numargs - 1], 0644);
        if (fd < 0)
        {
            perror(NULL);
            exit(1); /*indicar um erro*/
        }
        dup2(fd, STDERR_FILENO);
        close(fd);
        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }
    // ii tratar do redirect do >
    // verificar casos de (>) ou append (>>)
    // tratar do > creat ou >> open O_WRONLY | O_APPEND

    // iii tratar do < open O_RDONLY
    return numargs; // devolver o numero de argumentos a passar para execvp
}