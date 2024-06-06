#include "shell.h"

int ultimo(int *numargs, char **args) {
    if (args[*numargs - 1][0] == '&') {
        *numargs = *numargs - 1; // Decrementa o número de argumentos
        args[*numargs] = NULL; // Anula o ponteiro para '&'
        return BG; // Retorna BG se for processo em segundo plano
    }
    return FG; // Retorna FG se for processo em primeiro plano
}

void execute(int numargs, char **args) {
    int pid, status;

    int code = ultimo(&numargs, args); // Verifica se é processo em background ou foreground

    if ((pid = fork()) < 0) { // Cria um processo filho
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Processo filho
        numargs = redirects(numargs, args); // Adiciona a chamada ao redirects aqui

        execvp(*args, args); // Executa o comando
        perror(*args);
        exit(1);
    }

    if (code == FG) { // Se for processo em primeiro plano, espera pelo filho
        while (wait(&status) != pid);
    }

    return;
}

void execute_pipe(char **args) {
    int pipefd[2];
    pid_t p1, p2;

    if (pipe(pipefd) < 0) {
        perror("pipe");
        return;
    }
    p1 = fork();
    if (p1 < 0) {
        perror("fork");
        return;
    }
    if (p1 == 0) {
        // Child 1 - executes the left side of the pipe
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execvp(args[0], args);
        perror(args[0]);
        exit(1);
    } else {
        p2 = fork();
        if (p2 < 0) {
            perror("fork");
            return;
        }
        if (p2 == 0) {
            // Child 2 - executes the right side of the pipe
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            execvp(args[2], args + 2);
            perror(args[2]);
            exit(1);
        } else {
            // Parent process
            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);
        }
    }
}
