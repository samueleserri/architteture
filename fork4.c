#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  for (int i = 0; i < 3; i++) {
    pid_t pid = fork();
    if (pid == -1) {
      printf("Fork fallito\n");
    } else if (pid == 0) {
      printf("Processo figlio!\n");
    } else {
      printf("Il processo figlio ha ID %d\n", pid);
    }
  }
  sleep(1);
  return 0;
}
