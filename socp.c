#include "shell.h"

void ioCopy(int IN, int OUT) {
  int n;
  char buf[BUFFSIZE];
  while ((n = read(IN, buf, BUFFSIZE)) > 0) {
    if (write(OUT, buf, n) != n)
      perror("Erro de escrita!\n");
  }
  if (n < 0)
    perror("Erro de leitura!\n");
}

void socp(char *fonte, char *destino) {
  int fdIN, fdOUT;

  fdIN = open(fonte, FILE_MODE);
  if (fdIN == -1) {
    perror("Erro ao abrir o arquivo de origem");
		exit(1);
  }

  fdOUT = creat(destino, FILE_MODE);
  if (fdOUT == -1) {
    perror("Erro ao abrir o arquivo de destino");
		exit(1);
  }

  ioCopy(fdIN, fdOUT);

  if (close(fdIN) == -1 || close(fdOUT) == -1) {
    perror("Erro ao fechar o arquivo de origem");
		exit(1);
  }
}