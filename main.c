#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define RUSH_RL_BUFSIZE 50
#define HISTORY_SIZE 5

#include <stdio.h>
#include <stdlib.h>

void input_loop(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);

int main(int argc, char**argv) {

  // load config files, if any

  input_loop();

  return EXIT_SUCCESS;

}

void input_loop(void) {
  char *line;
  char **args;
  char **history = malloc(sizeof(char) * RUSH_RL_BUFSIZE * HISTORY_SIZE);
  int history_ptr = 0;
  int status;

  do {
    printf("rush> ");
    line = read_line();
    args = split_line(line);
    status = execute(args);
    history[history_ptr] = line;
    history_ptr = (history_ptr + 1) % HISTORY_SIZE;
  } while (status);

  free(history);
}

char **split_line(char *line) {

  

}

int execute(char **args) {

}


char *read_line(void) {
  int bufsize = RUSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "rush: malloc error");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }

    position++;

    if (position >= bufsize) {
      bufsize += RUSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "rush: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

  }

}
