#define RUSH_RL_BUFSIZE 64
#define RUSH_TOK_BUFSIZE 64
#define RUSH_TOK_DELIM " \t\r\n\a"

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"
#include "builtins.h"

char *read_line(void);

int main(int argc, char**argv) {

  history_init();
  // run main REPL
  input_loop();

  return EXIT_SUCCESS;

}

// builtin_func - table of function pointers to built-in commands
// builtin_str - corresponding names/text triggers for builtin functions

int (*builtin_func[]) (char **) = {
  &rush_cd,
  &rush_help,
  &rush_history,
  &rush_exit
};

char *builtin_str[] = {
  "cd",
  "help",
  "history",
  "exit"
};

int rush_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
};

/* shell_display - determines what to display as a prefix to the command prompt. */

void shell_display() {
    long size = pathconf(".", _PC_PATH_MAX);
    char *cwd = malloc(sizeof(char)*size);

    register struct passwd *pw;  // defined in pwd.h
    register uid_t uid;
    int c;
  
    uid = geteuid ();
    pw = getpwuid (uid);

    getcwd(cwd, size);
    printf("[%s@rush] [%.40s]> ", pw->pw_name, cwd);
    free(cwd);
}

void input_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    shell_display();
    line = read_line();
    args = split_line(line);
    status = execute(args); 
    history_add(line);
  } while (status);

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
      perror(args[0]);
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

int execute(char **args) {

  int i;
  if (args[0] == NULL) {
    return 1;
  }

  for (i=0;i<rush_num_builtins();i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return launch(args);

}
