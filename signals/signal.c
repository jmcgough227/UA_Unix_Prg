// signal.c

// Notifies user of which signals have been sent

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void handler(int n) {
  printf("Signal : %d\n", n);
}

int main() {
  // setup signal handling
  struct sigaction newact;
  newact.sa_handler = handler;
  newact.sa_flags = 0;
  sigaction(SIGINT, &newact, NULL);
  sigaction(SIGTERM, &newact, NULL);

  // run for a really long time
  while(1) sleep(5);

  return 0;
}
