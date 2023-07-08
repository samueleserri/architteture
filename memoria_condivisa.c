#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int * crea_memoria_condivisa(int size)
{
  key_t key;
  int shmid;
  int * data;
  int shm_size = sizeof(int) * size;

  key = ftok("memoria_condivisa.c", 'R');
  if (key == -1) {
    printf("Errore nella creazione della chiave\n");
    exit(1);
  }

  shmid = shmget(key, shm_size, 0644 | IPC_CREAT);
  if (shmid == -1) {
    printf("Errore nel creare il segmento di memoria condivisa\n");
    exit(1);
  }

  data = (int *) shmat(shmid, (void *)0, 0);
  if (data == (int *)-1) {
    printf("Errore in shmat\n");
    exit(1);
  }
  return data;
}

int main(int argc, char * argv[])
{
  pid_t pid = fork();
  if (pid == 0) { // processo figlio
    int * data = crea_memoria_condivisa(100);
    printf("Scrittura in memoria condivisa...");
    for (int i = 0; i < 100; i++) {
      data[i] = i;
    }
    printf("completata\n");
    shmdt(data); 
  } else { // processo padre
    int * data = crea_memoria_condivisa(100);
    wait(&pid);
    for (int i = 0; i < 100; i++) {
      printf("%d\n", data[i]);
    }
  }
  exit(0);
}
