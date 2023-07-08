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

  // dove connettersi
  size_t addr_size = sizeof(struct sockaddr_in);
  struct sockaddr_in addr;
  memset(&addr, 0, addr_size);
  addr.sin_len = addr_size;
  addr.sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
  addr.sin_port = htons(8080);

  if (connect(fd, (const struct sockaddr *) &addr, (socklen_t) addr_size) == -1) {
    printf("Non riusciamo a connetterci al server\n");
    close(fd);
    exit(2);
  }
  // leggere e scrivere su fd
  char data[] = "Ciao Mondo";
  int data_len = strlen(data);
  
  write(fd, data, data_len);

  int rcount = read(fd, &buffer, BUF_LEN - 1);
  if (rcount == -1) {
    printf("Errore in lettura\n");
  } else {
    buffer[rcount] = '\0';
    printf("Ricevuto %s\n", buffer);
  }
  
  close(fd);
  return 0;
}
