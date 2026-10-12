#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ucontext.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {

  int inputFd, outputFd, openFlags;
  mode_t filePerms;
  ssize_t numRead;
  char buf[BUF_SIZE];

  if (argc != 3 || strcmp(argv[1], "--help") == 0) {
    fprintf(stderr, "Usage: %s old-file new-file\n", argv[0]);
    goto L_FAIL;
  }

  inputFd = open(argv[1], O_RDONLY);
  if (inputFd == -1) {
    fprintf(stderr, "couldn't open file %s: %s\n", argv[1], strerror(errno));
    goto L_FAIL;
  }

  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  outputFd = open(argv[2], openFlags, filePerms);
  if (outputFd == -1) {
    fprintf(stderr, "couldn't open file %s: %s\n", argv[2], strerror(errno));
    goto L_FAIL;
  }

  while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
    if (write(outputFd, buf, numRead) != numRead) {
      fprintf(stderr, "couldn't write whole buffer: %s\n", strerror(errno));
    }
  }

  if (numRead == -1) {
    fprintf(stderr, "read error: %s\n", strerror(errno));
    goto L_FAIL;
  }

  if (close(inputFd) == -1) {
    fprintf(stderr, "close input error: %s\n", strerror(errno));
    inputFd = -1;
    goto L_FAIL;
  }
  inputFd = -1;

  if (close(outputFd) == -1) {
    fprintf(stderr, "close output error: %s\n", strerror(errno));
    outputFd = -1;
    goto L_FAIL;
  }
  outputFd = -1;

  goto L_DONE;

L_FAIL:
  if (inputFd != -1)
    close(inputFd);
  if (outputFd != -1)
    close(outputFd);
  exit(EXIT_FAILURE);
L_DONE:
  exit(EXIT_SUCCESS);
}
