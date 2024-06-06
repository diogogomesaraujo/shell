#include "shell.h"

char prompt[100];
char *history[MAX_HISTORY];
int history_count = 0;

void add_to_history(char *cmd) {
    if (history_count < MAX_HISTORY) {
        history[history_count++] = strdup(cmd);
    } else {
        free(history[0]);
        for (int i = 1; i < MAX_HISTORY; i++) {
            history[i - 1] = history[i];
        }
        history[MAX_HISTORY - 1] = strdup(cmd);
    }
}

void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

int main() {
    int len;
    char linha[1024]; /* um comando */
    char *args[64];   /* com um maximo de 64 argumentos */

    strcpy(prompt, "SOSHELL: Introduza um comando : prompt>");
    while (1) {
        printf("%s", prompt);
        if (fgets(linha, 1023, stdin) == NULL) {
            printf("\n");
            exit(0);
        }
        len = strlen(linha);
        if (1 == len)
            continue; /* linha é apenas \n */
        if (linha[len - 1] == '\n')
            linha[len - 1] = '\0';

        add_to_history(linha); // Add command to history

        int numargs = parse(linha, args); /* particiona a string em argumentos */

        if (!builtin(args))
            execute(numargs, args); /* executa o comando */
    }
    return 0;
}

int builtin(char **args) {
    /* Toda a funcionalidade embutida deverá devolver 1 */
    if (strcmp(args[0], "sair") == 0) {
        exit(0);
        return 1; /* funcionalidade embutida */
    }
    if (strncmp(args[0], "42", 2) == 0) { // o 2 é o numero de caracteres de 42
        printf("42 is the answer to life the universe and everything\n");
        printf("https://pt.wikipedia.org/wiki/The_Hitchhiker's_Guide_to_the_Galaxy\n");
        return 1; /* funcionalidade embutida */
    }

    if (strcmp(args[0], "obterinfo") == 0) {
        printf("SoShell 2024 Version 1.0\n");
        return 1;
    }

    if (strlen(args[0]) > 4 && strlen(args[0]) < 102 && strncmp(args[0], "PS1=", 4) == 0) {
        strcpy(prompt, args[0] + 4);
        prompt[strlen(args[0] + 4)] = ' ';
        prompt[strlen(args[0] + 4) + 1] = '\0';
        return 1; // comando embutido
    }

    if (0 == strcmp(args[0], "quemsoueu")) {
        system("id");
        return 1; // comando embutido
    }

    if (0 == strcmp(args[0], "cd")) {
        int err;
        if (args[1] == NULL || strcmp(args[1], "~") == 0 || strcmp(args[1], "$HOME") == 0)
            err = chdir(getenv("HOME"));
        else
            err = chdir(args[1]);
        if (err < 0)
            perror(args[1]);
        return 1; // comando embutido
    }

    if (strcmp(args[0], "socp") == 0) {
        if (args[1] == NULL || args[2] == NULL) {
            printf("Usage: socp <SOURCE> <DESTINATION>\n");
        } else {
            socp(args[1], args[2]);
        }
        return 1; // comando embutido
    }

    if (strcmp(args[0], "calc") == 0) {
        calc(args[1], args[2], args[3]);
        return 1; // comando embutido
    }

    if (strcmp(args[0], "aviso") == 0) {
        pthread_t th;
        aviso_t *ptr = (aviso_t *)malloc(sizeof(aviso_t));
        if (ptr == NULL) {
            perror("malloc");
            return 1;
        }
        strcpy(ptr->msg, args[1]);
        ptr->tempo = atoi(args[2]);
        pthread_create(&th, NULL, avisowrapper, (void *)ptr);
        return 1;
    }

    if (strcmp(args[0], "socpth") == 0) {
        if (args[1] == NULL || args[2] == NULL) {
            printf("Usage: socpth <SOURCE> <DESTINATION>\n");
        } else {
            pthread_t th;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

            copiar_t *ptr = (copiar_t *)malloc(sizeof(copiar_t));
            if (ptr == NULL) {
                perror("malloc");
                return 1;
            }
            strcpy(ptr->fonte, args[1]);
            strcpy(ptr->destino, args[2]);

            pthread_create(&th, &attr, socpwrapper, (void *)ptr);
            pthread_attr_destroy(&attr);
        }
        return 1;
    }

    if (strcmp(args[0], "listCopies") == 0) {
        for (int i = 0; i < MAX_LOGS; i++) {
            if (strlen(copyLogs[i]) > 0)
                printf("%s\n", copyLogs[i]);
        }
        return 1;
    }

    if (strcmp(args[0], "bitcalc") == 0) {
        bitcalc(args[1], args[2], args[3]);
        return 1; // comando embutido
    }

    if (strcmp(args[0], "isspeg") == 0) {
        isspeg(args[1]);
        return 1; // comando embutido
    }

    if (strcmp(args[0], "sos") == 0) {
        sos();
        return 1; // comando embutido
    }

    if (strcmp(args[0], "setx") == 0) {
        setx(args[1], args[2]);
        return 1; // comando embutido
    }

    if (strcmp(args[0], "removerl") == 0) {
        removerl(args[1], args[2]);
        return 1; // comando embutido
    }

    if (strcmp(args[0], "historic") == 0) {
        print_history();
        return 1; // comando embutido
    }

    if (args[0][0] == '!' && isdigit(args[0][1])) {
        int index = atoi(args[0] + 1) - 1;
        if (index >= 0 && index < history_count) {
            printf("%s\n", history[index]);
            char *cmd = strdup(history[index]);
            int numargs = parse(cmd, args); /* particiona a string em argumentos */
            if (!builtin(args)) {
                execute(numargs, args); /* executa o comando */
            }
            free(cmd);
        } else {
            printf("Comando histórico inválido\n");
        }
        return 1; // comando embutido
    }

    if (args[1] && strcmp(args[1], "|") == 0) {
        execute_pipe(args);
        return 1; // comando embutido
    }

    return 0;
    return 0;
}