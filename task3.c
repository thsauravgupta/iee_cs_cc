#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX_SIZE 100

typedef struct {
    int key;
    int value;
    time_t expiry;
} CacheEntry;

CacheEntry heap[MAX_SIZE];  
int heapSize = 0;


CacheEntry* hashTable[MAX_SIZE];


void swap(CacheEntry* a, CacheEntry* b) {
    CacheEntry temp = *a;
    *a = *b;
    *b = temp;
}


void heapifyDown(int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && heap[left].expiry < heap[smallest].expiry)
        smallest = left;
    if (right < heapSize && heap[right].expiry < heap[smallest].expiry)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapifyDown(smallest);
    }
}

// Heap insertion -> O(log n) time
void insertHeap(CacheEntry entry) {
    heap[heapSize] = entry;
    int i = heapSize;
    heapSize++;

    while (i > 0 && heap[(i - 1) / 2].expiry > heap[i].expiry) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Heap deletion -> O(log n) time
void removeMinHeap() {
    if (heapSize == 0) return;
    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapifyDown(0);
}

// Inserts a key-value pair with expiry -> O(log n) time (heap insertion)
void set(int key, int value, int expirySeconds) {
    time_t currentTime = time(NULL);
    CacheEntry entry = {key, value, currentTime + expirySeconds};

    insertHeap(entry);  
    hashTable[key] = &heap[heapSize - 1];  
}

// Retrieves a value if not expired -> O(log n) time (removes expired keys)
int get(int key) {
    time_t currentTime = time(NULL);

    // Remove expired keys -> O(log n)
    while (heapSize > 0 && heap[0].expiry <= currentTime) {
        hashTable[heap[0].key] = NULL;
        removeMinHeap();
    }

    if (hashTable[key] && hashTable[key]->expiry > currentTime) {
        return hashTable[key]->value;
    }

    return -1;  
}

int main() {
    set(1, 100, 5);
    set(2, 200, 10);
    
    printf("Value of key 1: %d\n", get(1));  
    Sleep(6000);
    printf("Value of key 1 after expiry: %d\n", get(1)); 

    return 0;
}
