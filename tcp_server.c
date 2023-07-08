#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Buffer di ricezione
#define BUF_SIZE 100

char buffer[BUF_SIZE];

int main(int argc, char * argv[])
{
  // Creazione del socket
  int fd = socket(PF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    printf("Errore in creazione del socket\n");
    exit(1);
  }

  // Indirizzo su cui ascoltare
  size_t addr_size = sizeof(struct sockaddr_in);
  struct sockaddr_in addr;
  memset(&addr, 0, addr_size);
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_len = addr_size;

  // binding del socket all'indirizzo
  if (bind(fd, (const struct sockaddr *) &addr, addr_size) == -1) {
    printf("Errore in binding del socket\n");
    exit(2);
  }

  // Ci si mette in ascolto sulla porta 8080 di localhost (127.0.0.1)
  if (listen(fd, 1) == -1) {
    printf("Errore nel mettersi in ascolto\n");
    exit(3);
  }

  // Creazione della struttura che conterrà l'indirizzo del client
  struct sockaddr_in conn_addr;
  socklen_t addr_len = (socklen_t) addr_size;
  memset(&conn_addr, 0, addr_size);

  // Accettazione della connessione da parte del server
  int fdclient = accept(fd, (struct sockaddr *) &conn_addr, &addr_len);
  if (fdclient == -1) {
    printf("Errore nell'accettare la connessione\n");
    exit(4);
  }

  // Lettura dei dati
  int rcount = 0;
  rcount = read(fdclient, &buffer, BUF_SIZE-1);
  if (rcount == -1) {
    printf("Errore in lettura\n");
  } else {
    buffer[rcount] = '\0'; // null-termination
    printf("Ricevuto %s\n", buffer);
  }

  // Liberazione delle risorse
  close(fdclient);
  close(fd);
  return 0;
}
