#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

// Function to insert a node at the head of the circular linked list
void insertAtHead(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    if (head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        struct Node* current = head;
        while (current->next != head) {
            current = current->next;
        }
        newNode->next = head;
        current->next = newNode;
        head = newNode;
    }
}

// Function to insert a node at the tail of the circular linked list
void insertAtTail(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = head;
    if (head == NULL) {
        head = newNode;
        head->next = head;
        return;
    }
    struct Node* current = head;
    while (current->next != head) {
        current = current->next;
    }
    current->next = newNode;
}

// Function to insert a node at a specific position in the circular linked list
void insertAtPosition(int value, int position) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    if (position <= 1) {
        newNode->next = head;
        struct Node* current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = newNode;
        head = newNode;
        return;
    }
    struct Node* current = head;
    for (int i = 1; i < position - 1 && current->next != head; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

// Function to delete a node at the head of the circular linked list
void deleteAtHead() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node* current = head;
    if (current->next == head) {
        free(head);
        head = NULL;
    } else {
        while (current->next != head) {
            current = current->next;
        }
        struct Node* temp = head;
        head = head->next;
        current->next = head;
        free(temp);
    }
}

// Function to delete a node at the tail of the circular linked list
void deleteAtTail() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node* current = head;
    struct Node* prev = NULL;
    while (current->next != head) {
        prev = current;
        current = current->next;
    }
    if (prev == NULL) {
        free(head);
        head = NULL;
    } else {
        prev->next = head;
        free(current);
    }
}

// Function to delete a node from a specific position in the circular linked list
void deleteAtPosition(int position) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (position <= 1) {
        struct Node* current = head;
        while (current->next != head) {
            current = current->next;
        }
        struct Node* temp = head;
        head = head->next;
        current->next = head;
        free(temp);
        return;
    }
    struct Node* current = head;
    struct Node* prev = NULL;
    for (int i = 1; i < position && current->next != head; i++) {
        prev = current;
        current = current->next;
    }
    if (current == head) {
        return;
    }
    prev->next = current->next;
    free(current);
}

// Function to search for an element in the circular linked list
int searchElement(int value) {
    if (head == NULL) {
        return -1;
    }
    struct Node* current = head;
    int position = 1;
    do {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    } while (current != head);
    return -1;
}

// Function to display the circular linked list
void displayList() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node* current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

int main() {
    insertAtHead(1);
    insertAtHead(2);
    insertAtTail(3);
    insertAtPosition(4, 2);

    printf("Circular Linked List: ");
    displayList();

    deleteAtHead();
    deleteAtTail();
    deleteAtPosition(2);

    printf("Circular Linked List after deletions: ");
    displayList();

    int elementToSearch = 3;
    int position = searchElement(elementToSearch);
    if (position != -1) {
        printf("%d found at position %d\n", elementToSearch, position);
    } else {
        printf("%d not found in the list\n", elementToSearch);
    }

    return 0;
}
