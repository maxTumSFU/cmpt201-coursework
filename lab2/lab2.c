

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

  pid_t orig = getpid();
  printf("PID of original: %d\n", orig);

  while (1 == 1) {

    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    printf("Enter programs to run:\n");

    read = getline(&line, &length, stdin);

    if (read > 0 && line[read - 1] == '\n') {
      line[read - 1] = '\0';
    }

    // printf("readline result: [%s]\n", line);
    //  pid_t = getpid();

    pid_t childPID = fork();

    if (childPID == 0) // what the child created by fork runs
    {
      execl(line, line, (char *)NULL);

      printf("Exec failure\n");
      return 0;
    } else // what the parent runs
    {
      int childStatus;
      waitpid(childPID, &childStatus, 0);
    }

    free(line);
  }
}
