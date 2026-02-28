#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>// for Linux system
#include <arpa/inet.h>// for ip address
#include <sys/socket.h> // socket API
#inclue <sys/types.h>

int main(int argc, char *argv[])
{
  //setting port
  int port = 8080;
  if (argc >= 2) port = atoi(argv[1]);

  // create socket, Creating socket file descriptor
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0)
  {
    perror("socket failed");
    return 1;
  }

  // Forcefully attaching socket to the port 8080
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  //0.0.0.0:port
  if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    perror("bind failed");
    return 1;
  }

  if (listen(server_fd, 5) < 0)
  {
    perror("listen failed");
    return 1;
  }

  printf("Server listening on port %d...\n", port);

  struct sockaddr_in client_addr;
  socklen_t len = sizeof(client_addr);

  // keep accepting new clients
  while(1)
  {
    struct sockaddr_in client_addr;//save client infor
    socklen_t len = sizeof(clent_addr);
    int client_fd = accept(server_fd,(struct sockaddr*) & client_addr,&len);

    if (fork() == 0)
    {
        close(server_fd);

        char buffer[1024];
        int n;

        while ((n = recv(client_fd, buffer, sizeof(buffer), 0)) > 0)
        {
            send(client_fd, buffer, n, 0);   // echo
        }

        close(client_fd);
        exit(0);
    }
    close(client_fd);
  }
  return 0;
}