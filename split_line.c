#include "split_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PARTS_BUFSIZE 64
#define PARTS_DELIM " \t\r\n\a"

char **split_line(char *line) {
  int bufSize = PARTS_BUFSIZE;
  int posi = 0;
  char **parts = malloc(bufSize * sizeof(char *));
  char *part;

  if (!parts) {
    fprintf(stderr, "Snitch: Buffer allocation error\n");
    exit(EXIT_FAILURE);
  }

  part = strtok(line, PARTS_DELIM);
  while (part != NULL) {
    parts[posi] = part;
    posi++;

    if (posi >= bufSize) {
      bufSize += PARTS_BUFSIZE;
      parts = realloc(parts, bufSize * sizeof(char *));
      if (!parts) {
        fprintf(stderr, "Snitch: Buffer allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    part = strtok(NULL, PARTS_DELIM);
  }

  parts[posi] = NULL;
  return parts;
}

/*  strtok(): splits a string into smaller strings (tokens) based on delimiters.
 *
 *  Example:
 *    char str[] = "hello,world,again";
 *    char *token = strtok(str, ",");
 *    while(token != NULL){
 *      printf("%s\n", token);
 *      token = strtok(NULL, ",");
 *    }
 *
 *   Output:
 *    hello
 *    world
 *    again
 *
 *
 *   first call:
 *      char *token = strtok(str, ",");
 *      - Starts scanning str
 *      - Finds the first delimiter ,
 *      - Replaces it with \0
 *      - Returns a pointer to the beginning of the first token
 *
 *   subsequent call:
 *      token = strtok(NULL, ",");
 *      - continues scanning from where the previous call stopped
 *      - finds the next delimiter
 *      - Replaces it with \0
 *      - Returns the next token
 *
 *   Before strtok:
 *    hello,world,again\0
 *
 *   After strtok:
 *    hello\0world\0again\0
 *
 *   Commas have been replaced with null terminators, creating separate strings
 * in the same Buffer
 *
 *   - it modifies the original string
 *   - it maintains internal state: thats why subsequent call use NULL rather
 * than passing the string again
 *   - it treats delimiters as a set of characters
 *   - it is not thread-safe/reentrant in its standard form
 *
 */
