#include <pthread.h>
#include <stdio.h>

void * f(void * arg) 
{
    char * x = (char *) arg;
    for (int i = 0; i < 5000; i++) {
      printf("%c", *x);
    }
    return NULL;
}

int main(int argc, char * argv[])
{
    pthread_t thread[2];
    char a = '_';
    char b = '.';
    pthread_create(&thread[0], NULL, f, &a);
    pthread_create(&thread[1], NULL, f, &b);
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    printf("\n");
    return 0;
}
