#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  pid_t pid = fork();
  if (pid == -1) {
    printf("Fork fallito\n");
  } else if (pid == 0) {
    for (int i = 0; i < 3; i++) {
      printf("Processo figlio: %d\n", i);
      sleep(2);
    }
  } else {
    for (int i = 0; i < 6; i++) {
      printf("Processo padre: %d\n", i);
      sleep(1);
    }
  }
  return 0;
}
