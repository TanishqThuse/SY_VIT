import java.util.Arrays;

public class DeadlockDetection {
    int processes; // Number of processes
    int resources; // Number of resources
    int[][] allocation; // Resources currently allocated to processes
    boolean[] finish; // Indicates whether a process has finished or not
    int[] available; // Available resources

    public DeadlockDetection(int processes, int resources, int[][] allocation, int[] available) {
        this.processes = processes;
        this.resources = resources;
        this.allocation = allocation;
        this.available = available;
        this.finish = new boolean[processes];
    }

    public boolean isDeadlock() {
        int[] work = Arrays.copyOf(available, resources);
        boolean[] canFinish = new boolean[processes];

        // Initialize canFinish array to indicate whether a process can finish or not
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                canFinish[i] = isLessThanOrEqual(allocation[i], work);
            }
        }

        boolean found;
        do {
            found = false;
            for (int i = 0; i < processes; i++) {
                if (!finish[i] && canFinish[i]) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    canFinish[i] = false;
                    found = true;
                }
            }
        } while (found);

        // Check if any process is unable to finish
        for (boolean can : canFinish) {
            if (can) {
                return true; // System is in a deadlock state
            }
        }

        return false; // System is not in a deadlock state
    }

    private boolean isLessThanOrEqual(int[] arr1, int[] arr2) {
        for (int i = 0; i < arr1.length; i++) {
            if (arr1[i] > arr2[i]) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        int processes = 5;
        int resources = 3;
        int[][] allocation = {
            {0, 1, 0},
            {2, 0, 0},
            {3, 0, 2},
            {2, 1, 1},
            {0, 0, 2}
        };
        int[] available = {3, 3, 2};

        DeadlockDetection deadlockDetector = new DeadlockDetection(processes, resources, allocation, available);
        if (deadlockDetector.isDeadlock()) {
            System.out.println("System is in a deadlock state.");
        } else {
            System.out.println("System is not in a deadlock state.");
        }
    }
}
