#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef LIST_H
#define LIST_H

#define MAX_STR_LEN 48
#define LIST_FILE "newlist.txt"

typedef struct node {
    char *task;
    int done;
    struct node *next, *prev;
} *Node_p, Node;

typedef struct list {
    struct node *first, *last;
} List, *List_p;

typedef struct data {
    List_p *list;
    int choice;
} Data;

void initList(List_p *list);
void addTask(List_p *list, const char *new_task, int done);
int printList (List *list);
void readListFromFile(List_p *list);
void markDone(List_p *list, int task_number);
void printListToFile(List_p list);
int menu(List_p *);
void stripTask(char  **);

void userAddTask(List_p *);
void userFinishTask(List_p *);
void userRemoveTask(List_p *);
void freeList(List_p *list);
#endif
