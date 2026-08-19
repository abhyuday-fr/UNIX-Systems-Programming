#include <errno.h>
#include <fcntl.h> // for open
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for close

int main(int argc, char **argv) {

  if (argc != 2) {
    printf("Usage: %s <path>", argv[0]);
    exit(EXIT_FAILURE);
  }
  int fd;
  const char *path = argv[1];

  if ((fd = open(path, O_RDONLY)) < 0) {
    // perror("Unable to open"); // they both output the same
    printf("Unable to open: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  (void)close(fd);

  return 0;
}
