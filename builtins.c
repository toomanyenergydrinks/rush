#include <stdio.h>

int rush_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "rush: expected argument to 'cd'\n");
  } else {
    perror("rush");
  }
}

int rush_help(char **args) {
  int i;
  printf("AHHHH HELP ME");
}

int rush_exit(char **args) {
  return 0;
}
