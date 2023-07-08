#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  pid_t pid = fork();
  if (pid == -1) {
    printf("Fork fallito\n");
  } else if (pid == 0) {
    printf("Saluti dal processo figlio\n");
  } else {
    printf("Il processo figlio ha id %d\n", pid);
  }
  return 0;
}
