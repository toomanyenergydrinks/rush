#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

typedef struct process_node {
  pid_t pid;
  bool running;
  struct p_node *next;
} p_node;

typedef struct process_list {
  struct p_node *head;
} p_list_t;

p_list_t processes;
p_node *head;

void process_list_init() {

  head = malloc((p_node*)sizeof(p_node));
  head->pid = getpid();
  head->next = NULL;

}

void add_process(pid_t p) {

  p_node *new_node = NULL;
  new_node = malloc((p_node*)sizeof(p_node));
  new_node->pid = p;
  new_node->next = head;
  head = new_node;

}

void traverse_process_list() {
  p_node *cursor = NULL;
  cursor = head;
  while (cursor != NULL) {
    printf("%d\r\n", cursor->pid);
    cursor = cursor->next;
  }
}

int rush_process(char **args) {

  traverse_process_list();
  return 1;

}
