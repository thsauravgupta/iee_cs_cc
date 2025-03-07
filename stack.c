#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int mainStack[MAX]; 
    int minStack[MAX];  
    int maxStack[MAX];  
    int top;
} CustomStack;


// Time Complexity: O(1), Space Complexity: O(1)
void initStack(CustomStack *s) {
    s->top = -1;
}


// Time Complexity: O(1), Space Complexity: O(1) (No extra space per element)
void push(CustomStack *s, int x) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    s->top++;
    s->mainStack[s->top] = x;
    
    // Update minStack and maxStack
    if (s->top == 0) {
        s->minStack[s->top] = x;
        s->maxStack[s->top] = x;
    } else {
        s->minStack[s->top] = (x < s->minStack[s->top - 1]) ? x : s->minStack[s->top - 1];
        s->maxStack[s->top] = (x > s->maxStack[s->top - 1]) ? x : s->maxStack[s->top - 1];
    }
}


// Time Complexity: O(1), Space Complexity: O(1)
void pop(CustomStack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        return;
    }
    s->top--;
}


// Time Complexity: O(1), Space Complexity: O(1)
int top(CustomStack *s) {
    if (s->top == -1) {
        printf("Stack is empty\n");
        return INT_MIN;
    }
    return s->mainStack[s->top];
}


// Time Complexity: O(1), Space Complexity: O(1)
int getMin(CustomStack *s) {
    if (s->top == -1) {
        printf("Stack is empty\n");
        return INT_MIN;
    }
    return s->minStack[s->top];
}


// Time Complexity: O(1), Space Complexity: O(1)
int getMax(CustomStack *s) {
    if (s->top == -1) {
        printf("Stack is empty\n");
        return INT_MAX;
    }
    return s->maxStack[s->top];
}

int main() {
    CustomStack s;
    initStack(&s);
    
    push(&s, 10);
    push(&s, 5);
    push(&s, 20);
    push(&s, 2);
    push(&s, 15);
    
    printf("Top Element: %d\n", top(&s));
    printf("Minimum Element: %d\n", getMin(&s));
    printf("Maximum Element: %d\n", getMax(&s));
    
    pop(&s);
    printf("After popping:\n");
    printf("Top Element: %d\n", top(&s));
    printf("Minimum Element: %d\n", getMin(&s));
    printf("Maximum Element: %d\n", getMax(&s));
    
    return 0;
}
