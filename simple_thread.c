#include <pthread.h>
#include <stdio.h>

void * f(void * arg)  
{
    int * x = (int *) arg;
    printf("%d\n", *x);
    return NULL;
}

int main(int argc, char * argv[])
{
    pthread_t thread;
    int a = 10;
    pthread_create(&thread, NULL, f, &a);
    pthread_join(thread, NULL);
    return 0;
}
