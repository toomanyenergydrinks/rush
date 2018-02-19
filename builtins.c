#include <stdio.h>

extern char history[10][255];

int rush_history(char **args) {
  int x;
  for (x=0;x<3;x++) {
    printf("%s\n", history[x]);
  }
  return 1;
}

int rush_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "rush: expected argument to 'cd'\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("rush");
    }
  }
  return 1;
}

int rush_help(char **args) {
  int i;
  printf("AHHHH HELP ME\r\n");
  return 1;
}

int rush_exit(char **args) {
  return 0;
}
