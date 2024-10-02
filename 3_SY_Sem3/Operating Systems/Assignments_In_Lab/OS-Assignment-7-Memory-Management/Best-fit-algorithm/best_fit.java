import java.util.*;

class BestFit {
    public static void main(String args[]) {
        int blockSize[] = {30, 5, 10};
        int processSize[] = {10, 6, 9};

        List<Integer> allocation = new ArrayList<>(Collections.nCopies(processSize.length, -1));
        boolean[] isAllocated = new boolean[blockSize.length];

        for (int i = 0; i < processSize.length; i++) {
            int bestIdx = -1;
            for (int j = 0; j < blockSize.length; j++) {
                if (!isAllocated[j] && blockSize[j] >= processSize[i]) {
                    if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                        bestIdx = j;
                    }
                }
            }

            if (bestIdx != -1) {
                allocation.set(i, bestIdx);
                blockSize[bestIdx] -= processSize[i];  // Reduce the block size
                isAllocated[bestIdx] = true; // Mark the block as allocated
            }
        }

        boolean allocationSuccessful = true;

        for (int i = 0; i < processSize.length; i++) {
            if (allocation.get(i) != -1) {
                System.out.println("Process " + i + " allocated to block " + allocation.get(i));
            } else {
                System.out.println("Process " + i + " not allocated");
                allocationSuccessful = false;
            }
        }

        if (allocationSuccessful) {
            System.out.println("All processes were allocated successfully.");
        } else {
            System.out.println("Some processes could not be allocated.");
            // Attempt reallocation for unallocated processes
            for (int i = 0; i < processSize.length; i++) {
                if (allocation.get(i) == -1) {
                    int bestIdx = -1;
                    for (int j = 0; j < blockSize.length; j++) {
                        if (blockSize[j] >= processSize[i]) {
                            if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                                bestIdx = j;
                            }
                        }
                    }
                    if (bestIdx != -1) {
                        allocation.set(i, bestIdx);
                        blockSize[bestIdx] -= processSize[i];
                        System.out.println("Process " + i + " reallocated to block " + allocation.get(i));
                    }
                }
            }
        }
    }
}
