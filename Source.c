/*
7. Napisati program koji pomocu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguciti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Tocnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct directory Directory;
typedef Directory* position_Directory;
struct directory {
    char name[50];
    position_Directory next;
    position_Directory subdirectory;
};

typedef struct stack_element Stack_element;
typedef Stack_element* position_stack;
struct stack_element {
    position_Directory directory;
    position_stack next;
};



position_Directory create_directory(char name[]);
int push(position_stack head_stack, position_Directory current_directory);
position_Directory find_directory(position_Directory current_directory, char name[]);
position_Directory pop(position_stack head_stack);
int print_subdirectories(position_Directory current_directory);

int main() {


    Directory head_directory = {
        .name = {0},
        .next = NULL,
        .subdirectory = NULL,
    };

    position_Directory root_directory = create_directory("C:");
    head_directory.next = root_directory;

    position_Directory current_directory = root_directory;

    Stack_element head_stack = {
        .directory = NULL,
        .next = NULL,
    };

    push(&head_stack, current_directory);

    while (1) {
        printf("\nMenu:\n");
        printf("1 - md (Create Directory)\n");
        printf("2 - cd dir (Change Directory)\n");
        printf("3 - cd.. (Go Up)\n");
        printf("4 - dir (List Contents)\n");
        printf("5 - exit\n");

        int choice = 0;

        printf("Unesite broj opcije:");
        scanf("%d", &choice);

        if (choice == 1) {

            char name[50];

            printf("Unesite ime novog direktorija:");
            scanf("%s", name);

            position_Directory new_subdirectory = create_directory(name);

            new_subdirectory->next = current_directory->subdirectory;
            current_directory->subdirectory = new_subdirectory;
            printf("\nDirectory %s created\n", new_subdirectory->name);
        }
        else if (choice == 2) {

            char name[50];

            printf("Unesite ime željenog direktorija:");
            scanf("%s", name);

            current_directory = find_directory(current_directory, name);
            push(&head_stack, current_directory);
            printf("\nCurrently in %s\n", current_directory->name);

        }
        else if (choice == 3) {

            current_directory = pop(&head_stack);
            printf("\nCurrently in %s\n", current_directory->name);

        }
        else if (choice == 4) {

            print_subdirectories(current_directory);

        }
        else if (choice == 5) {
            printf("\nExiting program\n");
            break;

        }

    }

    return 0;
}

position_Directory create_directory(char name[]) {

    position_Directory new_directory = NULL;
    new_directory = malloc(sizeof(Directory));

    if (new_directory == NULL) {
        printf("\nERROR alocating memory");
        return NULL;
    }

    strcpy(new_directory->name, name);
    new_directory->next = NULL;
    new_directory->subdirectory = NULL;

    return new_directory;
}

position_Directory find_directory(position_Directory current_directory, char name[]) {

    position_Directory subdirectory = current_directory->subdirectory;

    while (subdirectory != NULL) {

        if (strcmp(subdirectory->name, name) == 0) {
            break;
        }
        subdirectory = subdirectory->next;
    }

    if (subdirectory == NULL) {
        printf("\ncould not find directory");
    }

    return subdirectory;
}


int push(position_stack head_stack, position_Directory current_directory) {

    position_stack new_element = NULL;
    new_element = malloc(sizeof(Stack_element));

    if (new_element == NULL) {
        printf("\nERROR alocating memory");
        return 1;
    }

    new_element->directory = current_directory;

    new_element->next = head_stack->next;
    head_stack->next = new_element;

    return 0;
}

position_Directory pop(position_stack head_stack) {

    if (head_stack->next == NULL) {
        printf("\nERROR:stack is empty");
        return NULL;
    }

    if (head_stack->next->next == NULL) {
        return head_stack->next->directory;
    }

    position_stack to_delete = head_stack->next;
    head_stack->next = to_delete->next;

    free(to_delete);

    return head_stack->next->directory;
}

int print_subdirectories(position_Directory current_directory) {

    position_Directory subdirectory = current_directory->subdirectory;

    if (subdirectory == NULL) {
        printf("\nERROR: no directories found in current directory");
        return 1;
    }
    printf("Directories in %s:\n", current_directory->name);
    while (subdirectory != NULL) {
        printf("%s\n", subdirectory->name);
        subdirectory = subdirectory->next;
    }

    return 0;
}