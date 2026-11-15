#include "loop.h"
#include "builtin_cmnds.h"
#include "read_line.h"
#include "split_line.h"
#include <stdio.h>

void snitch_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = read_line();
    args = split_line(line);
    status = snitch_execute(args);
  } while (status);
}
