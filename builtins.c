#include <stdio.h>

int rush_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "rush: expected argument to 'cd'\n");
  } else {
    perror("rush");
  }
}
