#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a hotel room
typedef struct {
    int roomNumber;
    char guestName[50];
} Room;

// Define a node for the linked list
typedef struct Node {
    Room data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int roomNumber, const char* guestName) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data.roomNumber = roomNumber;
    strcpy(newNode->data.guestName, guestName);
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertNode(Node** head, int roomNumber, const char* guestName) {
    Node* newNode = createNode(roomNumber, guestName);

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to display all booked rooms
void displayBookedRooms(Node* head) {
    if (head == NULL) {
        printf("No rooms booked.\n");
        return;
    }

    printf("Booked Rooms:\n");
    while (head != NULL) {
        printf("Room Number: %d, Guest Name: %s\n", head->data.roomNumber, head->data.guestName);
        head = head->next;
    }
}

// Function to book a room
void bookRoom(Node** availableRooms, Node** bookedRooms, int roomNumber, const char* guestName) {
    // Remove the booked room from available rooms
    Node* current = *availableRooms;
    Node* prev = NULL;

    while (current != NULL && current->data.roomNumber != roomNumber) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Room not found or already booked.\n");
        return;
    }

    if (prev == NULL) {
        *availableRooms = current->next;
    } else {
        prev->next = current->next;
    }

    // Add the booked room to booked rooms
    insertNode(bookedRooms, roomNumber, guestName);
    printf("Room booked successfully.\n");
}

// Function to check out from a room
void checkOut(Node** availableRooms, Node** bookedRooms, int roomNumber) {
    // Remove the booked room from booked rooms
    Node* current = *bookedRooms;
    Node* prev = NULL;

    while (current != NULL && current->data.roomNumber != roomNumber) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Room not found or not booked.\n");
        return;
    }

    if (prev == NULL) {
        *bookedRooms = current->next;
    } else {
        prev->next = current->next;
    }

    // Add the checked-out room to available rooms
    insertNode(availableRooms, roomNumber, "Available");
    printf("Room checked out successfully.\n");
}

// Main function
int main() {
    Node* availableRooms = NULL; // Linked list for available rooms
    Node* bookedRooms = NULL;    // Linked list for booked rooms

    // Initialize available rooms
    for (int i = 1; i <= 10; ++i) {
        insertNode(&availableRooms, i, "Available");
    }

    int choice;
    do {
        printf("WELCOME TO OUR HOTEL\n");
        printf("1. Available Rooms\n");
        printf("2. Booked Rooms\n");
        printf("3. Book a Room\n");
        printf("4. Check Out\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Available Rooms:\n");
                displayBookedRooms(availableRooms);
                break;
            case 2:
                displayBookedRooms(bookedRooms);
                break;
            case 3:
                printf("Enter Room Number to book: ");
                int roomNumber;
                scanf("%d", &roomNumber);
                printf("Enter Guest Name: ");
                char guestName[50];
                scanf("%s", guestName);
                bookRoom(&availableRooms, &bookedRooms, roomNumber, guestName);
                break;
            case 4:
                printf("Enter Room Number to check out: ");
                int checkOutRoomNumber;
                scanf("%d", &checkOutRoomNumber);
                checkOut(&availableRooms, &bookedRooms, checkOutRoomNumber);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    // Free allocated memory for linked lists
    Node* temp;
    while (availableRooms != NULL) {
        temp = availableRooms;
        availableRooms = availableRooms->next;
        free(temp);
    }

    while (bookedRooms != NULL) {
        temp = bookedRooms;
        bookedRooms = bookedRooms->next;
        free(temp);
    }

    return 0;
}
