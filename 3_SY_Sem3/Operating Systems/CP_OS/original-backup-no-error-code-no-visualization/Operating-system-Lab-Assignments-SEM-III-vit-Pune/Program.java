// Online Java Compiler
// Use this editor to write, compile and run your Java code online

import java.util.HashMap;
import java.util.Map;

class Program {
    private final String name;
    private final int size;

    public Program(String name, int size) {
        this.name = name;
        this.size = size;
    }

    public String getName() {
        return name;
    }

    public int getSize() {
        return size;
    }
}
 class MemoryManager {
    private static final int MEMORY_SIZE = 100; // Total memory size
    private static final int BLOCK_SIZE = 10;   // Size of each memory block

    private final Map<Integer, Program> memoryMap = new HashMap<>();
    private int nextMemoryLocation = 0;

    public boolean loadProgram(Program program) {
        int requiredBlocks = (program.getSize() + BLOCK_SIZE - 1) / BLOCK_SIZE; // Calculate how many memory blocks are needed

        if (nextMemoryLocation + requiredBlocks <= MEMORY_SIZE / BLOCK_SIZE) {
            // There is enough space to load the program
            for (int i = nextMemoryLocation; i < nextMemoryLocation + requiredBlocks; i++) {
                memoryMap.put(i, program);
            }
            nextMemoryLocation += requiredBlocks;
            return true;
        } else {
            // Not enough space
            return false;
        }
    }

    public void printMemoryStatus() {
        System.out.println("Memory Usage:");
        for (int i = 0; i < MEMORY_SIZE / BLOCK_SIZE; i++) {
            Program program = memoryMap.getOrDefault(i, null);
            if (program != null) {
                System.out.println("Block " + i + ": " + program.getName());
            } else {
                System.out.println("Block " + i + ": Empty");
            }
        }
    }

    public static void main(String[] args) {
        MemoryManager memoryManager = new MemoryManager();

        Program program1 = new Program("Program A", 25);
        Program program2 = new Program("Program B", 15);

        boolean loaded1 = memoryManager.loadProgram(program1);
        boolean loaded2 = memoryManager.loadProgram(program2);

        if (loaded1) {
            System.out.println(program1.getName() + " loaded successfully.");
        } else {
            System.out.println(program1.getName() + " could not be loaded due to insufficient memory.");
        }

        if (loaded2) {
            System.out.println(program2.getName() + " loaded successfully.");
        } else {
            System.out.println(program2.getName() + " could not be loaded due to insufficient memory.");
        }

        memoryManager.printMemoryStatus();
    }
}
