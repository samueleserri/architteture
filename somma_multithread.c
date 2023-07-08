#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 10000000
#define NUM_THREADS 1

int totale;
pthread_mutex_t lock_totale;

struct sotto_array {
  int * v;
  int inizio;
  int fine;
};

void * somma(void * arg) {
  struct sotto_array * s = (struct sotto_array *) arg;
  int somma_parziale = 0;
  for (int i = s->inizio; i < s->fine; i++) {
    somma_parziale += s->v[i];
  }
  pthread_mutex_lock(&lock_totale);
  totale += somma_parziale;
  pthread_mutex_unlock(&lock_totale);
  return NULL;
}

int * crea_dati()
{
  int * v = (int *) malloc(DATA_SIZE * sizeof(int));
  for (int i = 0; i < DATA_SIZE; i++) {
    v[i] = 1;
  }
  return v;
}

int main(int argc, char * argv[])
{
  pthread_mutex_init(&lock_totale, NULL);
  totale = 0;
  pthread_t threads[NUM_THREADS];
  struct sotto_array pezzi[NUM_THREADS];
  int * v = crea_dati();
  int dimensione = DATA_SIZE / NUM_THREADS;
  int k = 0;
  for (int i = 0; i < NUM_THREADS; i++) {
    pezzi[i].inizio = k;
    pezzi[i].fine = k + dimensione;
    pezzi[i].v = v;
    k += dimensione;
    pthread_create(&threads[i], NULL, somma, &pezzi[i]);
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf("La somma è %d\n", totale);
  return 0;
}
