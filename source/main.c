#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define MAX_STR_LEN 48
#define clear() printf("\033[H\033[J")

int main() {
    List_p main_list = NULL;
    int choice = menu(&main_list);
    while (choice != 4) {
        switch(choice) {
            case 1:
                userAddTask(&main_list);
                break;
            case 2:
                userFinishTask(&main_list);
                break;
            case 3:
                userRemoveTask(&main_list);
                break;
        }
        choice = menu(&main_list);
    }
    clear();
    printList(main_list);
    printListToFile(main_list);
    freeList(&main_list);
    return 0;
}
