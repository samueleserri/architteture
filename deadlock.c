#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void * fun1(void * arg)
{
  printf("Fun1 prova a acquisire lock1\n");
  pthread_mutex_lock(&lock1);
  sleep(1);
  printf("Fun1 prova a acquisire lock2\n");
  pthread_mutex_lock(&lock2);
  printf("Fun1 rilascia lock2\n");
  pthread_mutex_unlock(&lock2);
  printf("Fun1 rilascia lock1\n");
  pthread_mutex_unlock(&lock1);
  return NULL;
}

void * fun2(void * arg)
{
  printf("Fun2 prova a acquisire lock2\n");
  pthread_mutex_lock(&lock2);
  sleep(1);
  printf("Fun2 prova a acquisire lock1\n");
  pthread_mutex_lock(&lock1);
  printf("Fun2 rilascia lock1\n");
  pthread_mutex_unlock(&lock1);
  printf("Fun2 rilascia lock2\n");
  pthread_mutex_unlock(&lock2);
  return NULL;
}

int main(int argc, char * argv[])
{
  pthread_t threads[2];
  pthread_mutex_init(&lock1, NULL);
  pthread_mutex_init(&lock2, NULL);
  pthread_create(&threads[0], NULL, fun1, NULL);
  pthread_create(&threads[1], NULL, fun2, NULL);
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  return 0;
}
