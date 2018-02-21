#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/queue.h>

int rush_history(char **args) {
  history_print();
  return 1;
}

typedef struct node {
  char *command;
  struct node *next;
} node_t;

struct history {
  node_t *head;
};

struct history h;
node_t *head;
node_t *node_create(char *command, node_t *next);

int history_init() {

  head = node_create("rush", NULL);
  
}

node_t* node_create(char *command, node_t *next) {

  node_t *new_node = (node_t*)malloc(sizeof(node_t));
  if (new_node == NULL) {
    perror("rush");
  }
  new_node->command = strdup(command);
  new_node->next = next;
  return new_node;

}

node_t *prepend(node_t *head, char *command) {

  node_t *new_node = node_create(command, head);
  head = new_node;
  return head;

}

node_t append(node_t *head, char *command) {

  node_t *cursor = head;
  while(cursor->next != NULL) {
    cursor = cursor->next;
  }

  node_t *new_node = node_create(command, NULL);
  cursor->next = new_node;
}

void traverse(node_t *head) {

  node_t *cursor = head;
  while (cursor != NULL) {
    printf("%s\r\n", cursor->command);
    cursor = cursor->next;
  }

}

int history_size() {
  node_t *cursor = head;
  int c = 0;
  while (cursor != NULL) {
    c++;
    cursor = cursor->next;
  }
  return 0;
}

int history_add(char *command) {
  append(head, command);
  return 0;
}

void history_print() {
  traverse(head);
  return 0;
}
