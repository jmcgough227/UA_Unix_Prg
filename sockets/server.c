// server.c

// Example server program

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// my IP port
const int MY_PORT = 8080;

int main(int argc, char argv[]) {
  //create a socket
  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("Unable to create socket");
    return 1;
  }

  // server info
  struct sockaddr_in my_addr;
  my_addr.sin_family = AF_INET;         // host byte order
  my_addr.sin_port = htons(MY_PORT);    // short, network port
  my_addr.sin_addr.s_addr = INADDR_ANY;
  memset(&(my_addr.sin_zero), '\0', 8); // zero out the rest of the struct

  // bind to a local port
  int bind_status = bind(sockfd, (struct sockaddr*) &my_addr, sizeof(struct sockaddr_in));
  if (bind_status == -1) {
    perror("Unable to bind");
    close(sockfd);
    return 1;
  }

  // listen to the port
  int listen_status = listen(sockfd, 1);
  if (listen_status == -1) {
    perror("Unable to listen");
    close(sockfd);
    return 1;
  }

  // accept calls
  while (1) {
    // accept a call
    struct sockaddr_in client_addr;
    socklen_t sin_size = sizeof(struct sockaddr_in);
    int clientfd = accept(sockfd, (struct sockaddr*) &client_addr, &sin_size);

    //receive the request
    const int REQUEST_SIZE = 512;
    char request[REQUEST_SIZE + 1];
    ssize_t recsize = recv(clientfd, request, REQUEST_SIZE, 0);
    if (recsize == -1) {
      perror("Unable to receive request");
      close(sockfd);
      return 1;
    }

    request[recsize] = '\0';

    close(clientfd);

    // output the request
    fprintf(stdout, "<server>\n");
    fprintf(stdout, "WOOHOO we have a call!\n");
    fprintf(stdout, "<server>\n");
  }

  // close the socket
  close(sockfd);

  return 0;
}
