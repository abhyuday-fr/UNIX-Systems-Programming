#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  char buffer[128];

  printf("Write a command: ");
  fgets(buffer, sizeof(buffer), stdin);

  errno = 0;

  if (system(buffer) != 0) {
    printf("Error: %s", strerror(errno));
  }
}
