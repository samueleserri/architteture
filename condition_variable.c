#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int done = 0;

void * thread1(void * arg)
{
  printf("Attendo un secondo prima di cambiare il valore di \"done\"\n");
  sleep(1);
  pthread_mutex_lock(&m);
  done = 1;
  pthread_cond_signal(&c);
  pthread_mutex_unlock(&m);
  return NULL;
}

void * thread2(void * arg)
{
  pthread_mutex_lock(&m);
  while (done != 1) {
    pthread_cond_wait(&c, &m);
  }
  printf("Ora il valore di \"done\" è cambiato!\n");
  pthread_mutex_unlock(&m);
  return NULL;
}

int main(int argc, char * argv[])
{
  pthread_t threads[2];
  pthread_create(&threads[0], NULL, thread1, NULL);
  pthread_create(&threads[1], NULL, thread2, NULL);
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);  
}
