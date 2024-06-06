#include "shell.h"

char copyLogs[MAX_LOGS][LOG_LENGTH] = {0};
int logIndex = 0;

void aviso(char *mesg, int tempo)
{
    while (tempo > 0)
    {
        sleep(1);
        tempo--;
    }
    fprintf(stderr, "Aviso : %s\n", mesg);
}

void *avisowrapper(void *args)
{
    aviso_t *ptr = (aviso_t *)args;
    aviso(ptr->msg, ptr->tempo);
    free(ptr);
    return NULL;
}

void *socpwrapper(void *args)
{
    copiar_t *ptr = (copiar_t *)args;
    socp(ptr->fonte, ptr->destino);

    // Log the copy operation
    time_t mytime;
    time(&mytime);
    char *t = ctime(&mytime);
    if (t[strlen(t) - 1] == '\n')
        t[strlen(t) - 1] = '\0';

    snprintf(copyLogs[logIndex], LOG_LENGTH, "%s %s", t, ptr->destino);
    logIndex = (logIndex + 1) % MAX_LOGS;

    free(ptr);
    return NULL;
}