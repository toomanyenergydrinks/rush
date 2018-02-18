#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define RUSH_RL_BUFSIZE 64
#define HISTORY_SIZE 5
#define RUSH_TOK_BUFSIZE 64
#define RUSH_TOK_DELIM " \t\r\n\a"

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char**argv) {

  // load config files, if any

  input_loop();

  return EXIT_SUCCESS;

}

char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &rush_cd,
  &rush_help,
  &rush_exit
};

int rush_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
};

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
    status = launch(args);
    history[history_ptr] = line;
    history_ptr = (history_ptr + 1) % HISTORY_SIZE;
  } while (status);

  free(history);
}

char **split_line(char *line) {

  int bufsize = RUSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;
  if (!tokens) {
    fprintf(stderr, "rush: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, RUSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += RUSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char));
      if (!tokens) {
        fprintf(stderr, "rush: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, RUSH_TOK_DELIM);

  }
  tokens[position] = NULL;
  return tokens;


}

int launch(char **args) {

  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // we're the child process
    if (execvp(args[0], args) == -1) {
      perror("rush");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // something went mad wrong
    perror("error forking");
  } else {
    // we're the parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;

}


char *read_line(void) {
  char *line = NULL;
  ssize_t bufsize = 0;
  getline(&line, &bufsize, stdin);
  return line;
}
