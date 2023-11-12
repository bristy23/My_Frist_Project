#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a task node in the linked list
struct Task {
    char description[100];
    struct Task* next;
};

// Function to create a new task node
struct Task* createTask(char description[]) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    if (newTask == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newTask->description, description);
    newTask->next = NULL;
    return newTask;
}

// Function to add a task to the end of the linked list (queue)
void enqueue(struct Task** head, char description[]) {
    struct Task* newTask = createTask(description);
    if (*head == NULL) {
        *head = newTask;
    } else {
        struct Task* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTask;
    }
}

// Function to remove and return the first task from the linked list (queue)
struct Task* dequeue(struct Task** head) {
    if (*head == NULL) {
        return NULL;
    } else {
        struct Task* temp = *head;
        *head = temp->next;
        temp->next = NULL;
        return temp;
    }
}

// Function to push a task onto the stack
void push(struct Task** top, char description[]) {
    struct Task* newTask = createTask(description);
    newTask->next = *top;
    *top = newTask;
}

// Function to pop and return a task from the stack
struct Task* pop(struct Task** top) {
    if (*top == NULL) {
        return NULL;
    } else {
        struct Task* temp = *top;
        *top = temp->next;
        temp->next = NULL;
        return temp;
    }
}

// Function to delete a specific task from the linked list
void deleteTask(struct Task** head, char description[]) {
    struct Task* temp = *head;
    struct Task* prev = NULL;

    // If the task to be deleted is the first task
    if (temp != NULL && strcmp(temp->description, description) == 0) {
        *head = temp->next;
        free(temp);
        printf("Task deleted: %s\n", description);
        return;
    }

    // Search for the task to be deleted
    while (temp != NULL && strcmp(temp->description, description) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // If the task was not found
    if (temp == NULL) {
        printf("Task not found: %s\n", description);
        return;
    }

    // Unlink the task from the list and free the memory
    prev->next = temp->next;
    free(temp);

    printf("Task deleted: %s\n", description);
}

// Function to display the tasks in the linked list
void displayTasks(struct Task* head) {
    if (head == NULL) {
        printf("No tasks in the list.\n");
    } else {
        struct Task* temp = head;
        printf("Tasks:\n");
        while (temp != NULL) {
            printf("- %s\n", temp->description);
            temp = temp->next;
        }
    }
}

int main() {
    struct Task* todoList = NULL;  // Linked list for the to-do list
    struct Task* doneTasks = NULL; // Stack for completed tasks

    int choice;
    welcomeText();
    welcomeUser();

    char description[1000];
       system("cls");

    do {

        system("COLOR 9F");

        printf("\nMenu:\n\n");
        printf("1. Add Task\n\n");
        printf("2. Mark Task as Done\n\n");
        printf("3. Display Tasks\n\n");
        printf("4. Delete Task\n\n");
        printf("5. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter task description:\n ");
                scanf("%s", description);
                enqueue(&todoList, description);
                break;

            case 2:
                if (todoList == NULL) {
                    printf("No tasks to mark as done.\n");
                } else {
                    struct Task* completedTask = dequeue(&todoList);
                    push(&doneTasks, completedTask->description);
                    printf("Marked task as done: %s\n", completedTask->description);
                    free(completedTask);
                }
                break;

            case 3:
                printf("To-Do List:\n");
                displayTasks(todoList);
                printf("Done Tasks (in reverse order);\n");
                displayTasks(doneTasks);
                break;

            case 4:
                printf("Enter task description to delete:\n");
                scanf("%s", description);
                deleteTask(&todoList, description);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 5);

    // Free memory for remaining tasks in the to-do list
    while (todoList != NULL) {
        struct Task* temp = dequeue(&todoList);
        free(temp);
    }

    // Free memory for completed tasks in the stack
    while (doneTasks != NULL) {
        struct Task* temp = pop(&doneTasks);
        free(temp);
    }


    return 0;
}

void welcomeUser()
{
    system("color 5E");
    system("cls");
   printf("\n\n\n\n\n");
   printf("\t------------------------------------------------------------------------------------------------------\n\n");
   printf("\t#################################### YOUR TODO LIST APP ##############################################\n\n");
   printf("\t------------------------------------------------------------------------------------------------------\n");
   printf("\n\n\n\t\t*******************************\t\tWELCOME\t\t*******************************\n\n\n\n\n\n\n\n\n\t");
   system("pause");
}

void welcomeText()
{
    system("COLOR 03");
    printf("\n\n\n\n\n\n");
    printf("\t......................................................................................................\n\n\n");
    printf("\t\t?????????????????????????????\tIs It Blank!!!\t???????????????????????????????????\n\n");
    printf("\t.......................................................................................................\n\n");
    system("pause");
}






