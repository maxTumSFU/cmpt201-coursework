#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *rawline = NULL;
  size_t length = 0;

  // print last 5 lines that were gotten
  // aka store last 5 lines of input and circulate them when more than 5 are goten.

  char *buffer[5] = {0};
  int lenArr[5] = {0};

  int counter = 0;
  int next = 0;

  while (1) // while the getline doesn't fail
  {

    printf("Input: ");

    if (getline(&rawline, &length, stdin) == -1) {
      printf("error: getline\n");
      break;
    }

    rawline[strcspn(rawline, "\n")] = '\0'; // replace newline with \0

    buffer[next] = strdup(rawline); // creates copy of raw line and stores it
                                    // without duplication, all lines will be the same rawline
    lenArr[next] = strlen(rawline);

    next = (next + 1) % 5; // modulus to make loop easy

    if (counter < 5) // count untill buffer full. then can start calling free()
    {
      counter++;
    }

    if (strcmp(rawline, "print") == 0) {
      int start = (next - counter + 5) % 5;
      // start index has to be 0-4 for the buffer
      // if there are less than 5 in the buffer, next - count = 0
      //   adn print from the first index (0)
      // otherwise, index to print from in next.

      for (int i = 0; i < counter; i++) {
        int index = (start + i) % 5; // given start index loop through what is in buffer

        printf("%s\n", buffer[index]);
      }
    }
  }

  free(rawline);

  return 0;
}
