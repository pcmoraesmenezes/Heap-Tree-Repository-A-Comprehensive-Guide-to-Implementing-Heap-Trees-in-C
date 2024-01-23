#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct HeapTree {
    int size;
    int heap[MAX_SIZE];
} HeapTree;

void insertHeap(int value, HeapTree *p) {
    if (p->size == MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }
    p->heap[p->size] = value;
    int index = p->size;
    p->size++;
    int parent = (index - 1) / 2;
    while (index > 0 && p->heap[index] > p->heap[parent]) {
        int temp = p->heap[index];
        p->heap[index] = p->heap[parent];
        p->heap[parent] = temp;
        index = parent;
        parent = (index - 1) / 2;
    }
}

void printHeapTree(HeapTree *p, int index, int level) {
    if (index >= p->size)
        return;

    printHeapTree(p, 2 * index + 2, level + 1);

    for (int i = 0; i < level; i++)
        printf("\t");

    printf("%d\n", p->heap[index]);

    printHeapTree(p, 2 * index + 1, level + 1);
}

void printHeap(HeapTree *p) {
    if (p->size == 0) {
        printf("Heap is empty!\n");
        return;
    }

    printHeapTree(p, 0, 0);
}

int search(HeapTree *p, int value) {
    if (p->size == 0) {
        printf("No elements in the heap!\n");
        return 0;
    }
    for (int i = 0; i < p->size; i++) {
        if (p->heap[i] == value) {
            printf("Found!\n");
            return i;
        }
    }
    printf("Value not found!\n");
    return 2;
}

int removeHeap(HeapTree *p, int value) {
    if (p->size == 0) {
        printf("No elements in the heap!\n");
        return 0;
    }
    int aux = search(p, value);
    if (aux == 2) {
        return 2;
    }
    p->heap[aux] = p->heap[p->size - 1];
    p->size--;
    int parent = (aux - 1) / 2;
    int child = 2 * aux + 1;
    while (child < p->size) {
        if (child + 1 < p->size && p->heap[child + 1] > p->heap[child]) {
            child++;
        }
        if (p->heap[child] > p->heap[aux]) {
            int temp = p->heap[child];
            p->heap[child] = p->heap[aux];
            p->heap[aux] = temp;
            aux = child;
            child = 2 * aux + 1;
        } else {
            break;
        }
    }
}

int main() {
    HeapTree *p = (HeapTree *)malloc(sizeof(HeapTree));
    p->size = 0;
    int navigator = 0;
    int add = 0;
    while (1) {
        printf("Welcome to your Heap Tree!\n To view the Heap, enter '1'\n To insert a value, enter '2'\n To remove an element, enter '3'\n To perform a search, enter '4'\n To exit, enter '5'\n");
        scanf("%d", &navigator);
        while (navigator != 1 && navigator != 2 && navigator != 3 && navigator != 4 && navigator != 5) {
            printf("You did not enter a valid option! Try again\n");
            scanf("%d", &navigator);
        }
        if (navigator == 1) {
            if (p->size == 0) {
                printf("Heap is empty!\n");
            } else {
                printf("You chose to view the Heap!\n ");
                printHeap(p);
            }
        }
        if (navigator == 2) {
            printf("You chose to insert! Please enter the number below:\n");
            scanf("%d", &add);
            insertHeap(add, p);
        }
        if (navigator == 3) {
            if (p->size == 0) {
                printf("Heap is empty!\n");
            } else {
                printf("You chose to remove an element from the heap!\n ");
                printf("Enter a value!\n");
                scanf("%d", &add);
                removeHeap(p, add);
            }
        }
        if (navigator == 4) {
            printf("You chose to perform a search, enter the desired value to be searched!\n");
            scanf("%d", &add);
            search(p, add);
        }
        if (navigator == 5) {
            printf("You chose to exit the Navigator

!\n");
            break;
        }
    }
    return 0;
}
