#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  pid_t pid = fork();
  if (pid == -1) {
    printf("Fork fallito\n");
  } else if (pid == 0) {
    for (int i = 0; i < 3; i++) {
      printf("Processo figlio: %d\n", i);
      sleep(1);
    }
  } else {
    int status;
    pid_t cpid = wait(&status);
    printf("Un figlio di PID %d è terminato\n", cpid);
  }
  return 0;
}
