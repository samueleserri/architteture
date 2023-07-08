#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
  // Creazione del socket
  int fd = socket(PF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    printf("Errore in creazione del socket\n");
    exit(1);
  }

  // Indirizzo del server a cui connettersi
  size_t addr_size = sizeof(struct sockaddr_in);
  struct sockaddr_in addr;
  memset(&addr, 0, addr_size);
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_len = addr_size;

  // Connessione al server
  if (connect(fd, (const struct sockaddr *) &addr, (socklen_t) addr_size) == -1) {
    printf("Errore in connessione al server\n");
    exit(1);
  }

  // Invio dei dati
  char data[] = "ciao mondo";
  int data_len = strlen(data);
  write(fd, data, data_len);

  // Liberazione delle risorse
  close(fd);
}
