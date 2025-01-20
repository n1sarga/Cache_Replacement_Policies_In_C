#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CACHE_SIZE 3 // Cache Size

// Cache Block
typedef struct {
    int data;
    int age; // Used for LRU
} CacheBlock;

CacheBlock cache[CACHE_SIZE];

// Initialize cache
void initializeCache() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i].data = -1; // -1 indicates an empty block
        cache[i].age = 0;
    }
}

// Display cache contents
void displayCache() {
    printf("Cache contents: ");
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].data != -1) {
            printf("%d ", cache[i].data);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

// Least Recently Used (LRU) policy
void accessLRU(int data) {
    int leastUsed = 0, leastAge = cache[0].age;

    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].data == data) {
            printf("Hit: %d\n", data);
            cache[i].age = 0; // Reset age
            return;
        }
        if (cache[i].age > leastAge) {
            leastUsed = i;
            leastAge = cache[i].age;
        }
    }

    // Miss: Replace least recently used
    printf("Miss: Replacing %d with %d\n", cache[leastUsed].data, data);
    cache[leastUsed].data = data;
    cache[leastUsed].age = 0;

    // Increment age for other blocks
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (i != leastUsed) {
            cache[i].age++;
        }
    }
}

// First-In-First-Out (FIFO) policy
int fifoPointer = 0;
void accessFIFO(int data) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].data == data) {
            printf("Hit: %d\n", data);
            return;
        }
    }

    // Miss: Replace the oldest entry
    printf("Miss: Replacing %d with %d\n", cache[fifoPointer].data, data);
    cache[fifoPointer].data = data;
    fifoPointer = (fifoPointer + 1) % CACHE_SIZE;
}

// Random replacement policy (replaces only after the cache is full)
void accessRandom(int data) {
    // Check if the data is already in the cache
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].data == data) {
            printf("Hit: %d\n", data);
            return;
        }
    }

    // Check if there is an empty slot in the cache
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].data == -1) { // Empty slot
            printf("Miss: Adding %d to cache\n", data);
            cache[i].data = data;
            return;
        }
    }

    // Cache is full, replace a random block
    int randomIndex = rand() % CACHE_SIZE;
    printf("Miss: Replacing %d with %d\n", cache[randomIndex].data, data);
    cache[randomIndex].data = data;
}

// Main function for testing
int main() {
    initializeCache();
    int policyChoice;
    printf("Choose Cache Replacement Policy:\n1. LRU\n2. FIFO\n3. Random\n");
    scanf("%d", &policyChoice);

    int data;
    while (true) {
        printf("Enter data to access (-1 to exit): ");
        scanf("%d", &data);
        if (data == -1) break;

        switch (policyChoice) {
            case 1:
                accessLRU(data);
                break;
            case 2:
                accessFIFO(data);
                break;
            case 3:
                accessRandom(data);
                break;
            default:
                printf("Invalid policy choice.\n");
                return 1;
        }
        displayCache();
    }

    return 0;
}
