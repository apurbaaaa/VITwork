#include <stdio.h>
#include <stdbool.h>

#define MAX_PAGES 15
#define MAX_FRAMES 4


bool isPresent(int frames[], int page, int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page)
            return true;
    }
    return false;
}


int findFIFOIndex(int front) {
    return front;
}


int findOptimalIndex(int pages[], int frames[], int frameCount, int pageIndex) {
    int index = -1, farthest = pageIndex;
    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = pageIndex; j < MAX_PAGES; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == MAX_PAGES)
            return i;
    }
    return (index == -1) ? 0 : index;
}

int findLRUIndex(int lastUsed[], int frameCount) {
    int min = lastUsed[0], index = 0;
    for (int i = 1; i < frameCount; i++) {
        if (lastUsed[i] < min) {
            min = lastUsed[i];
            index = i;
        }
    }
    return index;
}


void FIFO(int pages[]) {
    int frames[MAX_FRAMES] = {-1, -1, -1, -1};
    int front = 0, hits = 0, misses = 0;

    for (int i = 0; i < MAX_PAGES; i++) {
        if (isPresent(frames, pages[i], MAX_FRAMES)) {
            hits++;
        } else {
            frames[findFIFOIndex(front)] = pages[i];
            front = (front + 1) % MAX_FRAMES;
            misses++;
        }
    }
    printf("FIFO - Hits: %d, Misses: %d, Hit Ratio: %.2f, Miss Ratio: %.2f\n", hits, misses, (float)hits / MAX_PAGES, (float)misses / MAX_PAGES);
}


void Optimal(int pages[]) {
    int frames[MAX_FRAMES] = {-1, -1, -1, -1};
    int hits = 0, misses = 0;

    for (int i = 0; i < MAX_PAGES; i++) {
        if (isPresent(frames, pages[i], MAX_FRAMES)) {
            hits++;
        } else {
            int index = findOptimalIndex(pages, frames, MAX_FRAMES, i + 1);
            frames[index] = pages[i];
            misses++;
        }
    }
    printf("Optimal - Hits: %d, Misses: %d, Hit Ratio: %.2f, Miss Ratio: %.2f\n", hits, misses, (float)hits / MAX_PAGES, (float)misses / MAX_PAGES);
}


void LRU(int pages[]) {
    int frames[MAX_FRAMES] = {-1, -1, -1, -1};
    int lastUsed[MAX_FRAMES] = {0, 0, 0, 0};
    int hits = 0, misses = 0;

    for (int i = 0; i < MAX_PAGES; i++) {
        if (isPresent(frames, pages[i], MAX_FRAMES)) {
            hits++;
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == pages[i])
                    lastUsed[j] = i;
            }
        } else {
            int index = findLRUIndex(lastUsed, MAX_FRAMES);
            frames[index] = pages[i];
            lastUsed[index] = i;
            misses++;
        }
    }
    printf("LRU - Hits: %d, Misses: %d, Hit Ratio: %.2f, Miss Ratio: %.2f\n", hits, misses, (float)hits / MAX_PAGES, (float)misses / MAX_PAGES);
}

int main() {
    int pages[MAX_PAGES] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5, 1, 2, 3};

    printf("Page sequence: ");
    for (int i = 0; i < MAX_PAGES; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    FIFO(pages);
    Optimal(pages);
    LRU(pages);

    return 0;
}
