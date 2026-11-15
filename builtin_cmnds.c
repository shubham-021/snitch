#include "builtin_cmnds.h"
#include "launch.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *builtin_str[] = {"cd", "help", "exit", "cwd", "clear"};

int (*builtin_func[])(char **) = {&snitch_cd, &snitch_help, &snitch_exit,
                                  &snitch_cwd, &snitch_clear};

int snitch_num_builtins() { return sizeof(builtin_str) / sizeof(char *); }

int snitch_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "Snitch: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("Snitch: chdir");
    }
  }

  return 1;
}

int snitch_cwd(char **args) {
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s\n", cwd);
    return 1;
  }

  fprintf(stderr, "Snitch: cwd");
  return 0;
}

int snitch_help(char **args) {
  int i;
  printf("Snitch\n");
  printf("Type program names and arguments, and hit enter\n");
  printf("The following are built in:\n");

  for (i = 0; i < snitch_num_builtins(); i++) {
    printf(" %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int snitch_clear(char **args) {
  printf("\033[2J\033[H");
  fflush(stdout);
  return 1;
}

int snitch_exit(char **args) { return 0; }

int snitch_execute(char **args) {
  int i;
  if (args[0] == NULL) {
    return 1;
  }

  for (i = 0; i < snitch_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return launch_snitch(args);
}
