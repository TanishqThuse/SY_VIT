import java.util.*;

class SCAN {
    public enum Direction {
        LEFT, RIGHT
    }

    public static void main(String[] args) {
        // Define the initial head position and the disk queue
        int initialHead = 50; // Initial head position
        List<Integer> diskQueue = new ArrayList<>(List.of(176, 79, 34, 60, 92, 11, 41, 114));

        System.out.println("Initial head position: " + initialHead);
        System.out.println("Disk queue: " + diskQueue);

        int totalHeadMovement = calculateTotalHeadMovement(initialHead, new ArrayList<>(diskQueue), Direction.RIGHT);
        System.out.println("\nTotal head movement using SCAN: " + totalHeadMovement);
    }

    public static int calculateTotalHeadMovement(int initialHead, List<Integer> diskQueue, Direction direction) {
        int totalHeadMovement = 0;
        int currentHead = initialHead;

        // Create a copy of the disk queue to modify during the algorithm
        List<Integer> queueCopy = new ArrayList<>(diskQueue);

        // Sort the disk queue according to the direction
        if (direction == Direction.RIGHT) {
            Collections.sort(queueCopy);
        } else {
            Collections.sort(queueCopy, Collections.reverseOrder());
        }

        // SCAN algorithm
        while (!queueCopy.isEmpty()) {
            int nextIndex = findNextIndex(currentHead, queueCopy, direction);
            if (nextIndex == -1) {
                if (direction == Direction.RIGHT) {
                    direction = Direction.LEFT;
                } else {
                    direction = Direction.RIGHT;
                }
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

    public static int findNextIndex(int currentHead, List<Integer> queue, Direction direction) {
        int index = -1;
        int smallestDifference = Integer.MAX_VALUE;

        for (int i = 0; i < queue.size(); i++) {
            int difference = queue.get(i) - currentHead;
            if ((difference >= 0 && direction == Direction.RIGHT) || (difference <= 0 && direction == Direction.LEFT)) {
                if (Math.abs(difference) < smallestDifference) {
                    smallestDifference = Math.abs(difference);
                    index = i;
                }
            }
        }
        return index;
    }
}
