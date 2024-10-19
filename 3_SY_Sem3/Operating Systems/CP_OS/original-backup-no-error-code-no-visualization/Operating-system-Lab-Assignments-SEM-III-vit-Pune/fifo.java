import java.util.*;

class CSCAN {
    public static void main(String[] args) {
        // Define the initial head position and the disk queue
        int initialHead = 50; // Initial head position
        List<Integer> diskQueue = new ArrayList<>(List.of(176, 79, 34, 60, 92, 11, 41, 114));

        System.out.println("Initial head position: " + initialHead);
        System.out.println("Disk queue: " + diskQueue);

        int totalHeadMovement = calculateTotalHeadMovement(initialHead, new ArrayList<>(diskQueue));
        System.out.println("\nTotal head movement using CSCAN: " + totalHeadMovement);
    }

    public static int calculateTotalHeadMovement(int initialHead, List<Integer> diskQueue) {
        int totalHeadMovement = 0;
        int currentHead = initialHead;

        // Create a copy of the disk queue to modify during the algorithm
        List<Integer> queueCopy = new ArrayList<>(diskQueue);

        // Sort the disk queue in ascending order
        Collections.sort(queueCopy);

        // CSCAN algorithm
        while (!queueCopy.isEmpty()) {
            int nextIndex = findNextIndex(currentHead, queueCopy);
            if (nextIndex == -1) {
                // Move to the beginning of the disk
                totalHeadMovement += Math.abs(currentHead - 0);
                System.out.println("Move from " + currentHead + " to 0, Head Movement: " + Math.abs(currentHead - 0));
                currentHead = 0;
                continue;
            }

            int nextTrack = queueCopy.get(nextIndex);
            int headMovement = Math.abs(currentHead - nextTrack);
            totalHeadMovement += headMovement;

            System.out.println("Move from " + currentHead + " to " + nextTrack + ", Head Movement: " + headMovement);

            currentHead = nextTrack;
            queueCopy.remove(nextIndex);
        }
        return totalHeadMovement;
    }

    public static int findNextIndex(int currentHead, List<Integer> queue) {
        int index = -1;
        int smallestDifference = Integer.MAX_VALUE;

        for (int i = 0; i < queue.size(); i++) {
            int difference = queue.get(i) - currentHead;
            if (difference >= 0 && difference < smallestDifference) {
                smallestDifference = difference;
                index = i;
            }
        }
        return index;
    }
}
