#include <unistd.h>

int get_char() {
  unsigned char c;

  ssize_t n = read(STDIN_FILENO, &c, 1);

  if (n == 1)
    return c;

  return -1; // EOF or error
}
