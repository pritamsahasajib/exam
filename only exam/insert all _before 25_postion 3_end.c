#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Insert at beginning
struct Node* insertAtBeginning(struct Node* head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = head;
    return newNode;
}

// Insert after a given node
void insertAfter(struct Node* prevNode, int value) {
    if (prevNode == NULL) {
        printf("The given previous node cannot be NULL.\n");
        return;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}

// Insert before a given node 
struct Node* insertBefore(struct Node* head, int target, int value) {
    if (head == NULL) return NULL;

    if (head->data == target) {
        return insertAtBeginning(head, value);
    }

    struct Node* current = head;
    while (current->next != NULL && current->next->data != target) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf("Target node %d not found.\n", target);
        return head;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = current->next;
    current->next = newNode;

    return head;
}

// Insert at a specific position (0-based)
struct Node* insertAtPosition(struct Node* head, int position, int value) {
    if (position == 0) {
        return insertAtBeginning(head, value);
    }

    struct Node* current = head;
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Position %d out of bounds.\n", position);
        return head;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = current->next;
    current->next = newNode;

    return head;
}

// Insert at end
struct Node* insertAtEnd(struct Node* head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) return newNode;

    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// 
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// 
int main() {
    struct Node* head = NULL;

   //insert beginning
    head = insertAtBeginning(head, 30);
    head = insertAtBeginning(head, 20);
    head = insertAtBeginning(head, 10);

    printf("Original List:\n");
    printList(head);

    // Insert 25 after 20
    insertAfter(head->next, 25); 
    printf("After inserting 25 after 20:\n");
    printList(head);

    // Insert 15 before 20
    head = insertBefore(head, 20, 15);
    printf("After inserting 15 before 20:\n");
    printList(head);

    // Insert 17 at position 3
    head = insertAtPosition(head, 3, 17);
    printf("After inserting 17 at position 3:\n");
    printList(head);

    // Insert 40 at the end
    head = insertAtEnd(head, 40);
    printf("After inserting 40 at the end:\n");
    printList(head);

    return 0;
}
