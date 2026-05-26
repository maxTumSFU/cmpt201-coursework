// lab 1

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// takes a line of text and separates it by the space characters.

int main() {
  printf("Please enter some text: ");

  char *rawLine = NULL;
  size_t length = 0;

  ssize_t lineSize = getline(&rawLine, &length, stdin);

  if (lineSize == -1) {
    perror("getline failed \n");
    exit(EXIT_FAILURE);
  }

  printf("line size: %zu \n", lineSize);
  printf("line: %s \n", rawLine);
  // print length and raw line that we got.

  // first call
  char *saveptr;
  char *token1 = strtok_r(rawLine, " ", &saveptr);
  while (token1 != NULL)

  {
    // subsequent calls
    printf("%s \n", token1);

    token1 = strtok_r(NULL, " ", &saveptr);
  }

  free(rawLine);

  return 0;
}
