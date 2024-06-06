#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/wait.h>
#include <dirent.h>
#include <time.h>

#define BUFFSIZE 128
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define MAX_LOGS 10
#define LOG_LENGTH 130
#define BG 0
#define FG 1
#define MAX_HISTORY 100

extern char *history[MAX_HISTORY];
extern int history_count;

typedef struct {
    char msg[100];
    int tempo;
} aviso_t;

typedef struct {
    char fonte[100];
    char destino[100];
} copiar_t;

void *avisowrapper(void *args);
void aviso(char *mesg, int tempo);
void calc(char *value1, char *op, char *value2);
int parse(char *ptrLinha, char **args);
void execute(int numargs, char **args);
int builtin(char **args);
void ioCopy(int IN, int OUT);
void socp(char *fonte, char *destino);
void *socpwrapper(void *args);
void bitcalc(char *value1, char *op, char *value2);
void isspeg(char *str);
void sos(void);
void setx(char *file, char *mode);
void removerl(char *file, char *mode);
void execute_pipe(char **args);  // Certifique-se que esta linha está presente
int redirects(int numargs, char *args[]);
int ultimo(int *numargs, char **args);
void add_to_history(char *cmd);
void print_history();

extern char copyLogs[MAX_LOGS][LOG_LENGTH];
extern int logIndex;
