import java.util.Scanner;

public class FirstFitMemoryAllocation {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Number of memory partitions
        int numPartitions;
        System.out.print("Enter the number of memory partitions: ");
        numPartitions = scanner.nextInt();

        int[] partitions = new int[numPartitions]; // Array to store memory partition sizes
        boolean[] allocated = new boolean[numPartitions]; // Array to track allocated partitions

        // Input memory partition sizes
        for (int i = 0; i < numPartitions; i++) {
            System.out.print("Enter size for partition " + i + ": ");
            partitions[i] = scanner.nextInt();
            allocated[i] = false; // Initially, no partition is allocated
        }

        // Number of processes
        int numProcesses;
        System.out.print("Enter the number of processes: ");
        numProcesses = scanner.nextInt();

        int[] processes = new int[numProcesses]; // Array to store process sizes
        boolean[] processAllocated = new boolean[numProcesses]; // Array to track allocated processes

        // Input process sizes
        for (int i = 0; i < numProcesses; i++) {
            System.out.print("Enter size for process " + i + ": ");
            processes[i] = scanner.nextInt();
            processAllocated[i] = false; // Initially, no process is allocated
        }

        // Perform first fit allocation
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numPartitions; j++) {
                if (!allocated[j] && partitions[j] >= processes[i]) {
                    allocated[j] = true;
                    processAllocated[i] = true;
                    System.out.println("Process " + i + " of size " + processes[i] + " is allocated to partition " + j);
                    break; // Move to the next process
                }
            }
            if (!processAllocated[i]) {
                System.out.println("Process " + i + " of size " + processes[i] + " cannot be allocated.");
            }
        }

        scanner.close();
    }
}
