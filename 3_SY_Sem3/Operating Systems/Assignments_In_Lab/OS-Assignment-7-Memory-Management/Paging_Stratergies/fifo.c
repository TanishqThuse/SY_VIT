#include <stdio.h>
#include <stdbool.h>

void display(int frames[], int frameSize) {
    for (int i = 0; i < frameSize; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

// FIFO Page Replacement
void fifo(int pages[], int n, int frameSize) {
    int frames[frameSize], pageFaults = 0, next = 0;

    // Initialize frames to empty
    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        // Check if page is already in a frame
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            // Replace page using FIFO
            frames[next] = page;
            next = (next + 1) % frameSize;
            pageFaults++;
        }

        display(frames, frameSize);
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}


/**Enter number of blocks in the memory: 3
Enter size of block 1: 100
Enter size of block 2: 500
Enter size of block 3: 200
Enter the number of processes: 3
Enter the size of Process 1: 120
Enter the size of Process 2: 50
Enter the size of Process 3: 300
 */