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
  char *line = NULL;
  ssize_t bufsize = 0;
  getline(&line, &bufsize, stdin);
  return line;
}
