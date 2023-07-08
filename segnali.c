#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

volatile sig_atomic_t segnale_ricevuto;

void sigint_handler(int sig)
{
  write(0, "Segnale ricevuto\n", 18);
  segnale_ricevuto = 1;
}

int main(int argc, char * argv[])
{
  segnale_ricevuto = 0;
  pid_t pid;
  pid = fork();
  if (pid == 0) { // processo figlio
    if (signal(SIGINT, sigint_handler) == SIG_ERR) { // registriamo il gestore di segnali
      exit(1);
    }
    while (segnale_ricevuto != 1) { // attendiamo che il segnale sia ricevuto
      printf("In attesa di un segnale\n");
      sleep(1);
    }
    printf("Uscito dal gestore del segnale\n");
  } else { // processo padre
    sleep(3);
    kill(pid, SIGINT); // inviamo un segnale SIGINT al processo figlio
  }
  return 0;
}
