#include "List.h"

void initList(List_p *list) {
    (*list) = malloc(sizeof(List));
    (*list)->first = NULL;
    (*list)->last = NULL;
}


void addTask(List_p *list, const char *new_task, int done) {
    if (list == NULL || (*list) == NULL)
        initList(list);
    Node_p new_node;
    new_node = (Node_p)malloc(sizeof(Node));
    if (new_node == NULL)
        return;
    new_node->done = done;
    new_node->prev = (*list)->last;
    new_node->next = NULL;
    if ((*list)->first == NULL)
        (*list)->first = new_node;
    if ((*list)->last)
        (*list)->last->next = new_node;
    (*list)->last = new_node;
    new_node->task = malloc(strlen(new_task) + 1);
    strcpy(new_node->task, new_task);
}

int printList (List *list) {
    int i = 0;
    if (list == NULL || list->first == NULL) {
        printf("       LIST IS EMPTY :(\n");
        return 0;
    }
    Node_p iter = list->first;
    i = 1;
    while (iter) {
        printf("%d. %s", i++, iter->task);
        if (iter->done)
            printf("  [X]\n");
        else printf("  [ ]\n");
        iter = iter->next;
    }
    return i - 1;
}

void stripTask(char **task) {
    char *seek = *task;
    while (*seek != '\0' && *seek != '[')
        seek++;
    *seek = '\0';
}

void readListFromFile(List_p *list) {
    FILE *in = fopen(LIST_FILE, "r");
    if (in == NULL)
        return;
    if (list == NULL || (*list) == NULL)
        initList(list);
    char *buf = malloc(MAX_STR_LEN);
    
    while (fgets(buf, MAX_STR_LEN, in)) {
        char *seek = buf;
        int done = 0;
        while (*seek != '[')
            seek++;
        seek++;
        if (*seek == 'X')
            done  = 1;
        stripTask(&buf);
        addTask(list, buf, done);
    }
    fclose(in);
    free(buf);
}


void markDone(List_p *list, int task_number) {
    int i = 1;
    Node_p iter = (*list)->first;
    while (iter && i != task_number) {
        iter = iter->next;
        i++;
    }
    if (i != task_number) {
        printf("Invalid task number\n");
        return;
    }
    iter->done = 1;
    char *seek = iter->task;
    while (*seek != '[')
        seek++;
    seek++;
    *seek = 'X';
}

void printListToFile(List_p list) {
    FILE *out = fopen(LIST_FILE, "w");
    if (out == NULL)
        return;
    if (list == NULL)
        return;
    Node_p iter = list->first;
    while (iter) {
        char buf[MAX_STR_LEN + 5] = {0};
        if (iter->done == 1)
            snprintf(buf, MAX_STR_LEN + 5, "%s[X]\n", iter->task);
        else snprintf(buf, MAX_STR_LEN + 5, "%s[ ]\n", iter->task);
        fputs(buf, out);
        iter = iter->next;
    }
    fclose(out);
}

int menu(List_p *list) {
    system("clear");
    printf("Welcome to your TO DO List app!\nHere is your current list:\n");
    if (list == NULL || (*list) == NULL)
        readListFromFile(list);
    printList(*list);
    printf("What would you like to do now?\n");
    printf("1. Add a task\n2. Mark a task as done\n3. Delete a task\n4. Quit\nYour choice: ");
    int choice;
    scanf("%d", &choice);
    while (choice > 4 || choice < 1) {
        printf("Invalid choice\nYour choice: ");
        scanf("%d", &choice);
    }
    return choice;
}

void userAddTask(List_p *list) {
    system("clear");
    printf("Please enter the name of the task (max. 48 characters): ");
    char *buf = malloc(MAX_STR_LEN);
    scanf("%s", buf);
    printf("%s", buf);
    addTask(list, buf, 0);
    free(buf);
    return;
}

void userFinishTask(List_p *list) {
    system("clear");
    int max;
    max = printList(*list);
    printf("Which task would you like to mark as finished? (1 - %d) ", max);
    int index = 0;
    scanf("%d", &index);
    while (index < 1 || index > max) {
        printf("Invalid task number. Please enter a task number between 1 - %d: ", max);
        scanf("%d", &index);
    }
    int i = 1;
    Node_p iter = (*list)->first;
    while (iter != NULL && i < index) {
        iter = iter->next;
        i++;
    }
    iter->done = 1;
}


void userRemoveTask(List_p *list) {
    system("clear");
    int max = printList(*list);
    printf("Which task would you like to remove? (1 - %d): ", max);
    int index;
    scanf("%d", &index);
    while (index < 1 || index > max) {
        printf("Invalid task number. Please enter a task number between 1 - %d: ", max);
        scanf("%d", &index);
    }
    if (index == 1) {
        Node_p tmp = (*list)->first;
        (*list)->first = tmp->next;
        if (tmp->next)
            tmp->next->prev = NULL;
        free(tmp->task);
        free(tmp);
        return;
    }
    if (index == max) {
        Node_p tmp = (*list)->last;
        (*list)->last = tmp->prev;
        if (tmp->prev)
            tmp->prev->next = NULL;
        free(tmp->task);
        free(tmp);
        return;
    }
    int i = 1;
    Node_p iter = (*list)->first, prev;
    while (iter != NULL && i < index) {
        i++;
        prev = iter;
        iter = iter->next;
    }
    prev->next = iter->next;
    iter->prev = prev;
    if (iter->next) 
        iter->next->prev = prev;
    free(iter);
}

void freeList(List_p *list) {
    Node_p iter = (*list)->first, tmp;
    while (iter) {
        tmp = iter;
        iter = iter->next;
        free(tmp->task);
        free(tmp);
    }
    free(*list);
}