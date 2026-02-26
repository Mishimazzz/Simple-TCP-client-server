#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
  char *ip = "127.0.0.1";
  int port = 8080;

  if (argc >= 2)
    ip = argv[1];
  if (argc >= 3)
    port = atoi(argv[2]);

  //create socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    perror("socket");
    return 1;
  }

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip, &server_addr.sin_addr);

  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("Connection Failed");
    return 1;
  }

  char *msg = "hello from client\n";
  send(sock, msg, strlen(msg), 0);

  char buffer[1024];
  int n = recv(sock, buffer, sizeof(buffer) - 1, 0);
  if (n > 0)
  {
    buffer[n] = '\0';
    printf("Server replied: %s", buffer);
  }

  close(sock);
  return 0;
}