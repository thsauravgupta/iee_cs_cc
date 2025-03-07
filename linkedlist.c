#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Time Complexity: O(1) | Space Complexity: O(1)
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Time Complexity: O(1) | Space Complexity: O(1)
void insertAtHead(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head != NULL) {
        (*head)->prev = newNode;
        newNode->next = *head;
    }
    *head = newNode;
}


// Time Complexity: O(n) | Space Complexity: O(1)
void insertAtTail(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {  // O(n) traversal to find the last node
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}


// Time Complexity: O(n) | Space Complexity: O(1)
void traverseForward(struct Node* head) {
    printf("Forward Traversal: ");
    struct Node* temp = head;
    while (temp != NULL) {  // O(n) traversal
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


// Time Complexity: O(n) | Space Complexity: O(1)
void traverseBackward(struct Node* head) {
    if (head == NULL) return;

    struct Node* temp = head;
    while (temp->next != NULL) {  // O(n) traversal to reach last node
        temp = temp->next;
    }

    printf("Backward Traversal: ");
    while (temp != NULL) {  // O(n) traversal back to the head
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;

    insertAtHead(&head, 10);
    insertAtHead(&head, 20);
    insertAtTail(&head, 30);
    insertAtTail(&head, 40);

    traverseForward(head);
    traverseBackward(head);

    return 0;
}
