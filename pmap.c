#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t lock_rand;

struct job {
  float * v;
  int start;
  int end;
  float (*f) (float);
};

void * pmap_thread(void * args)
{
  struct job * s = (struct job *) args;
  for (int i = s->start; i < s->end; i++) {
    s->v[i] = s->f(s->v[i]);
  }
  return NULL;
}

void pmap(float * elems, size_t len, float (*f) (float), int n_threads)
{
  int chunk_size = len/n_threads;
  if (chunk_size*n_threads < len) {
    chunk_size++;
  }
  pthread_t * threads = (pthread_t *) malloc(n_threads * sizeof(pthread_t));
  struct job * chunks = (struct job *) malloc(n_threads * sizeof(struct job));
  int k = 0;
  for (int i = 0; i < n_threads; i++) {
    chunks[i].v = elems;
    chunks[i].start = k;
    k = k + chunk_size;
    if (k > len) {
      k = len;
    }
    chunks[i].end = k;
    chunks[i].f = f;
    pthread_create(&threads[i], NULL, pmap_thread, &chunks[i]);
  }
  for (int i = 0; i < n_threads; i++) {
    pthread_join(threads[i], NULL);
  }
  free(threads);
  free(chunks);
}

float rand_float(float x)
{
  pthread_mutex_lock(&lock_rand);
  int r = rand();
  pthread_mutex_unlock(&lock_rand);
  return ((float) r)/RAND_MAX;
}

float set_to_one(float x)
{
  return 1.0;
}

int main(int argc, char * argv[])
{
  pthread_mutex_init(&lock_rand, NULL);
  time_t now;
  srand((unsigned) time(&now));
  int data_size = 1<<24; // 2^24
  float * v = malloc(data_size * sizeof(float));
  clock_t t;

  printf("Parallel map senza lock\n");
  for (int nt = 1; nt < 13; nt++) {
    t = clock();
    pmap(v, data_size, set_to_one, nt);
    t = clock() - t;
    printf("tempo richiesto (%d threads): %f secondi\n",
	   nt, (float)t/CLOCKS_PER_SEC);
  }
  printf("\n");
  
  //printf("v[10] = %f\n", v[10]);
  printf("Parallel map con lock\n");
  for (int nt = 1; nt < 13; nt++) {
    t = clock();
    pmap(v, data_size, rand_float, nt);
    t = clock() - t;
    printf("tempo richiesto (%d threads): %f secondi\n",
	   nt, (float)t/CLOCKS_PER_SEC);
  }
  //printf("v[10] = %f\n", v[10]);
  return 0;
}
