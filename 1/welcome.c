#include <stdio.h>
#include <unistd.h>

int main() { printf("Welcome, %s!\n", getlogin()); }
