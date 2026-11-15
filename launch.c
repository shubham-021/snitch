#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int launch_snitch(char **args) {
  pid_t pid, cpid;
  int status;

  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("snitch: execvp");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("snitch: fork");
  } else {
    do {
      cpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}
