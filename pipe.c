#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
  int pipe_fd[2];
  char buffer[30];
  
  pipe(pipe_fd);

  pid_t pid;

  pid = fork();

  if (pid == 0) {
    printf("Processo figlio: scrittura su pipe\n");
    write(pipe_fd[1], "prova", 6);
    printf("Processo figlio: scrittura completata\n");
  } else {
    printf("Processo padre: lettura da pipe\n");
    read(pipe_fd[0], buffer, 6);
    printf("Processo padre: letto %s\n", &buffer);
    wait(&pid);
  }
  exit(0);
}
