/*
  httpclient.c

  Example socket client program

  Michael L. Collard
  collard@uakron.edu
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

// destination IP port
const int DEST_PORT = 80;

int main(int argc, char* argv[]) {

  if (argc < 4) {
    fprintf(stderr, "Usage: %s <ip> <host> <path>\n", argv[0]);
    return 1;
  }

  // unpack the parameters
  const char* dest_ip = argv[1];
  const char* url_host = argv[2];
  const char* url_path = argv[3];

  // form the request
  const char* URL_GET_FORMAT = "GET %s HTTP/1.1\nHost: %s\n\n";
  int request_size = snprintf(NULL, 0, URL_GET_FORMAT, url_path, url_host);
  ++request_size;
  char* request = malloc(request_size);
  int actual_size = snprintf(request, request_size, URL_GET_FORMAT, url_path, url_host);
  if (actual_size >= request_size) {
    fprintf(stderr, "Request size is too large\n");
    free(request);
    return 1;
  }

  // create a socket
  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("Unable to create socket");
    return 1;
  }

  // destination info
  struct sockaddr_in dest_addr;
  dest_addr.sin_family = AF_INET;          // host byte order
  dest_addr.sin_port = htons(DEST_PORT);   // short, network port
  dest_addr.sin_addr.s_addr = inet_addr(dest_ip);   // destination address
  memset(&(dest_addr.sin_zero), '\0', 8);           // zero out the rest of the struct

  // connect to the server
  int status = connect(sockfd, (struct sockaddr*) &dest_addr, sizeof(struct sockaddr_in));
  if (status == -1) {
    perror("Unable to connect to the server");
    close(sockfd);
    return 1;
  }

  // send a simple message
  ssize_t sendsize = send(sockfd, request, strlen(request), 0);
  if (sendsize == -1) {
    perror("Unable to send to the server");
    close(sockfd);
    return 1;
  }

  // free up the request
  free(request);
  request = 0;

  while (1) {

    // receive the response
    const int RESPONSE_SIZE = 512;
    char response[RESPONSE_SIZE];
    ssize_t recsize = recv(sockfd, response, RESPONSE_SIZE, 0);
    if (recsize == -1) {
      perror("Unable to recv from the server");
      close(sockfd);
      return 1;
    }

    // output the response
    write(STDOUT_FILENO, response, recsize);

    // partial response means finished
    if (recsize < RESPONSE_SIZE)
      break;
  }
  
  // close the socket
  close(sockfd);

  return 0;
}
