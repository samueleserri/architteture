#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_LEN 100

char buffer[BUF_LEN];

int main(int argc, char * argv[])
{
  int fd = socket(PF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    printf("Errore nella creazione del socket\n");
    exit(1);
  }

   // dove ascoltare
  size_t addr_size = sizeof(struct sockaddr_in);
  struct sockaddr_in addr;
  memset(&addr, 0, addr_size);
  addr.sin_len = addr_size;
  addr.sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
  addr.sin_port = htons(8080);

  if (bind(fd, (const struct sockaddr *) &addr, addr_size) == -1) {
    printf("Impossibile fare bind sulla porta 8080\n");
    close(fd);
    exit(2);
  }

  if (listen(fd, 1) == -1) {
    printf("Non possiamo metterci in ascolto\n");
    close(fd);
    exit(3);
  }

  struct sockaddr conn_addr;
  socklen_t addr_len = (socklen_t) addr_size;
  memset(&conn_addr, 0, addr_size);

  int fdclient = accept(fd, (struct sockaddr *) &conn_addr, &addr_len);
  if (fdclient == -1) {
    printf("Errore nell'accettare la connessione\n");
    close(fd);
    exit(4);
  }

  int rcount = read(fdclient, &buffer, BUF_LEN - 1);
  if (rcount == -1) {
    printf("Errore in lettura\n");
  } else {
    buffer[rcount] = '\0';
    printf("Ricevuto %s\n", buffer);
    for (int i = 0; i < rcount/2; i++) {
      char tmp = buffer[i];
      buffer[i] = buffer[rcount-(i+1)];
      buffer[rcount-(i+1)] = tmp;
    }
    printf("Elaborato come %s\n", buffer);
    write(fdclient, buffer, rcount);
  }
  
  close(fdclient);
  close(fd);
  return 0;
}
