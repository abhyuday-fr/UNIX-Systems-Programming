#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main() {

  int num;
  errno = 0;

  if ((num = sysconf(_SC_OPEN_MAX)) < 0) {
    printf("Error: %s\n", errno);
  } else {
    printf("Defined on this platform\n");
    printf("Value of sysconf is %d", num);
  }

  return 0;
}
