#include <stdio.h>
#include <stdlib.h>

#define MAX_INTERVALS 100

typedef struct {
    int start, end;
} Interval;

typedef struct {
    Interval intervals[MAX_INTERVALS];
    int size;
} IntervalMerger;


// Time Complexity: O(1), Space Complexity: O(1)
void initMerger(IntervalMerger *merger) {
    merger->size = 0;
}


// Time Complexity: O(1) per comparison
int compare(const void *a, const void *b) {
    return ((Interval *)a)->start - ((Interval *)b)->start;
}


// Time Complexity: O(n log n) due to sorting, O(n) for merging => Overall O(n log n)
// Space Complexity: O(1) (modifying existing array)
void addInterval(IntervalMerger *merger, int start, int end) {
    if (merger->size >= MAX_INTERVALS) {
        printf("Interval storage full!\n");
        return;
    }
    

    merger->intervals[merger->size].start = start;
    merger->intervals[merger->size].end = end;
    merger->size++;
    
    qsort(merger->intervals, merger->size, sizeof(Interval), compare);

    int index = 0;
    for (int i = 1; i < merger->size; i++) {
        if (merger->intervals[index].end >= merger->intervals[i].start) {
            if (merger->intervals[index].end < merger->intervals[i].end)
                merger->intervals[index].end = merger->intervals[i].end;
        } else {
            index++;
            merger->intervals[index] = merger->intervals[i];
        }
    }
    
    merger->size = index + 1;
}


// Time Complexity: O(n) (iterating over the intervals)
// Space Complexity: O(1) (only printing)
void getIntervals(IntervalMerger *merger) {
    printf("[");
    for (int i = 0; i < merger->size; i++) {
        printf("[%d, %d]", merger->intervals[i].start, merger->intervals[i].end);
        if (i < merger->size - 1)
            printf(", ");
    }
    printf("]\n");
}

int main() {
    IntervalMerger merger;
    initMerger(&merger);
    
    addInterval(&merger, 1, 5);
    addInterval(&merger, 6, 8);
    addInterval(&merger, 4, 7);
    
    getIntervals(&merger);
    
    return 0;
}
