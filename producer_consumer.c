#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define N_PROD 3
#define N_CONS 2

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

int buffer[BUFFER_SIZE];
int first_free = 0;

void * producer(void * arg)
{
  while (1) {
    sleep(rand()%2 + 1); // sleep di 1 o 2 secondi
    pthread_mutex_lock(&m);
    while (first_free == BUFFER_SIZE) { // La coda è piena
      printf("Il buffer è pieno, attendo\n");
      pthread_cond_wait(&c, &m);
    }
    buffer[first_free] = rand()%10;
    printf("Inserito %d nel buffer\n", buffer[first_free]);
    first_free++;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
  }
  return NULL;
}

void * consumer(void * arg)
{
  while (1) {
    sleep(rand()%2 + 1); // sleep di 1 o 2 secondi
    pthread_mutex_lock(&m);
    while (first_free == 0) { // La coda è vuota
      printf("Il buffer è vuoto, attendo\n");
      pthread_cond_wait(&c, &m);
    }
    first_free--;
    int x = buffer[first_free];
    printf("Letto %d dal buffer\n", x);
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
  }
  return NULL;
}

int main(int argc, char * argv[])
{
  pthread_t producers[N_PROD];
  pthread_t consumers[N_CONS];
  for (int i = 0; i < N_PROD; i++) {
    pthread_create(&producers[i], NULL, producer, NULL);
  }
  for (int i = 0; i < N_CONS; i++) {
    pthread_create(&consumers[i], NULL, consumer, NULL);
  }
  for (int i = 0; i < N_PROD; i++) {
    pthread_join(producers[i], NULL);
  }
  for (int i = 0; i < N_CONS; i++) {
    pthread_join(consumers[i], NULL);
  }
  return 0;
}
