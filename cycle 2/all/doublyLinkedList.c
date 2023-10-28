#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node with the given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the head of the doubly linked list
void insertAtHead(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

// Function to insert a node at the tail of the doubly linked list
void insertAtTail(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

// Function to insert a node at a specified position in the doubly linked list
void insertAtPosition(struct Node** head, int data, int position) {
    if (position <= 0) {
        printf("Invalid position for insertion.\n");
        return;
    }

    if (position == 1) {
        insertAtHead(head, data);
        return;
    }

    struct Node* newNode = createNode(data);
    struct Node* current = *head;
    int count = 1;

    while (current != NULL && count < position - 1) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        printf("Position out of bounds for insertion.\n");
        free(newNode);
        return;
    }

    newNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
}

// Function to delete a node at the head of the doubly linked list
void deleteAtHead(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    struct Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

// Function to delete a node at the tail of the doubly linked list
void deleteAtTail(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    struct Node* current = *head;

    while (current->next != NULL) {
        current = current->next;
    }

    if (current->prev != NULL) {
        current->prev->next = NULL;
    } else {
        *head = NULL;
    }
    free(current);
}

// Function to delete a node from a specified position in the doubly linked list
void deleteFromPosition(struct Node** head, int position) {
    if (position <= 0) {
        printf("Invalid position for deletion.\n");
        return;
    }

    if (position == 1) {
        deleteAtHead(head);
        return;
    }

    struct Node* current = *head;
    int count = 1;

    while (current != NULL && count < position) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        printf("Position out of bounds for deletion.\n");
        return;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    free(current);
}

// Function to search for a node with a specific data in the doubly linked list
struct Node* searchElement(struct Node* head, int data) {
    struct Node* current = head;

    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Function to display the elements of the doubly linked list
void displayList(struct Node* head) {
    printf("Doubly Linked List: ");
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int choice, data, position;
    struct Node* result;

    do {
        printf("Menu:\n");
        printf("1. Insert at the head\n");
        printf("2. Insert at the tail\n");
        printf("3. Insert at a position\n");
        printf("4. Delete at the head\n");
        printf("5. Delete at the tail\n");
        printf("6. Delete from a position\n");
        printf("7. Search for an element\n");
        printf("8. Display the list\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at the head: ");
                scanf("%d", &data);
                insertAtHead(&head, data);
                break;
            case 2:
                printf("Enter data to insert at the tail: ");
                scanf("%d", &data);
                insertAtTail(&head, data);
                break;
            case 3:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter the position: ");
                scanf("%d", &position);
                insertAtPosition(&head, data, position);
                break;
            case 4:
                deleteAtHead(&head);
                break;
            case 5:
                deleteAtTail(&head);
                break;
            case 6:
                printf("Enter the position to delete: ");
                scanf("%d", &position);
                deleteFromPosition(&head, position);
                break;
            case 7:
                printf("Enter the element to search: ");
                scanf("%d", &data);
                result = searchElement(head, data);
                if (result != NULL) {
                    printf("Element %d found in the list.\n", data);
                } else {
                    printf("Element %d not found in the list.\n", data);
                }
                break;
            case 8:
                displayList(head);
                break;
            case 9:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    } while (choice != 9);

    // Clean up: Free memory
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

