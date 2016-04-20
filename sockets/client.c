// client.c

// Example client socket program

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// destination IP address
const char* DEST_IP = "130.101.10.109";

// destination IP port
const int DEST_PORT = 8080;

// request to send to the destination
const char* REQUEST = "What does the server say?";

int main(int argc, char argv[]) {
  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("Unable to create socket");
    return 1;
  }

  // destination info
  struct sockaddr_in dest_addr;
  dest_addr.sin_family = AF_INET;                 // host byte order
  dest_addr.sin_port = htons(DEST_PORT);          // short, network port
  dest_addr.sin_addr.s_addr = inet_addr(DEST_IP); // destination address
  memset(&(dest_addr.sin_zero), '\0', 8);         // zero out the rest of the struct

  // connect to the server
  int status = connect(sockfd, (struct sockaddr*) &dest_addr, sizeof(struct sockaddr_in));
  if (status == -1) {
    perror("Unable to connect to the server");
    close(sockfd);
    return 1;
  }

  // send a simple message
  ssize_t sendsize = send(sockfd, REQUEST, strlen(REQUEST), 0);
  if (sendsize == -1) {
    perror("Unable to send to the server");
    close(sockfd);
    return 1;
  }

  while(1) {
    // recieve the response
    const int RESPONSE_SIZE = 512;
    char response[RESPONSE_SIZE];
    ssize_t recsize = recv(sockfd, response, RESPONSE_SIZE, 0);
    if (recsize == -1) {
      perror("Unable to recv from the server");
      close(sockfd);
      return 1;
    }

    // output the result
    write(STDOUT_FILENO, response, recsize);

    // partial response means finished
    if (recsize < RESPONSE_SIZE) {
      break;
    }
  }

  printf("Hi, still here!\n");

  // close the socket
  close(sockfd);

  return 0;
}
