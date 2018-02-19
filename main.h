#define HISTORY_SIZE 5

void input_loop(void);
char *read_line(void);
char **split_line(char *line);
int launch(char **args);

int rush_history(char **args);
int rush_cd(char **args);
int rush_help(char **args);
int rush_exit(char **args);
int rush_num_builtins();
