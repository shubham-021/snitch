#include "read_line.h"
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

char *read_line(void) {
  int bufSize = BUF_SIZE;
  int posi = 0;
  char *buffer = malloc(sizeof(char) * bufSize);
  int ch;

  /*
   *   fprintf: a C standard library function used to print formatted output to
   * a specified file stream; Think of it as printf(), but instead of always
   * printing to standard output (stdout), we can choose specified file stream.
   */
  if (!buffer) {
    fprintf(stderr, "Snitch: buffer allocation error\n");
    exit(EXIT_FAILURE);
  }

  /*
   *   getchar() reads a single character from standard input (stdin), whereas
   * scanf() read formatted input according to the format specifier we provide;
   *
   *   Why is the variable int and not char ?
   *   Because getchar returns an int, allowing it to represent:
   *     - all possible unsigned char values.
   *     - a special value called EOF (End of File), indicating no more input or
   * an input error
   */
  while (1) {
    ch = getchar();

    if (ch == EOF || ch == '\n') {
      buffer[posi] = '\0';
      return buffer;
    } else {
      buffer[posi] = ch;
    }

    posi++;

    if (posi >= bufSize) {
      bufSize += BUF_SIZE;
      buffer = realloc(buffer, bufSize);
      if (!buffer) {
        fprintf(stderr, "Snitch: buffer allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}
