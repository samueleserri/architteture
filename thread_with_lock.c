#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t c_mutex;

void * h(void * args)
{
    printf("%s\n", (char *)args);
    for (int i = 0; i < 10000000; i++)
    {
      pthread_mutex_lock(&c_mutex);
      counter++;
      pthread_mutex_unlock(&c_mutex);
    }
    return NULL;
}

void * g(void * args)
{
    printf("%s\n", (char *)args);
    for (int i = 0; i < 10000000; i++)
    {
      counter++;
    }
    return NULL;
}

int main(int argc, char * argv[])
{
  pthread_mutex_init(&c_mutex, NULL);
  pthread_t t1, t2;
  pthread_create(&t1, NULL, h, "A");
  pthread_create(&t2, NULL, h, "B");

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("Counter = %d\n", counter);
  return 0;
}
