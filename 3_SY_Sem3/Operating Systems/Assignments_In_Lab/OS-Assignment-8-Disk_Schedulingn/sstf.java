// Java program for implementation of 
// SSTF disk scheduling

public class sstf {

	static class node {
	
        // represent difference between 
        // head position and track number
        int distance = 0; 
        
        // true if track has been accessed
        boolean accessed = false; 
    }
	
	// Calculates difference of each 
	// track number with the head position
	public static void calculateDifference(int queue[], 
										int head, node diff[])
										
	{
		for (int i = 0; i < diff.length; i++)
			diff[i].distance = Math.abs(queue[i] - head);
	}

	// find unaccessed track 
	// which is at minimum distance from head
	public static int findMin(node diff[])
	{
		int index = -1, minimum = Integer.MAX_VALUE;

		for (int i = 0; i < diff.length; i++) {
			if (!diff[i].accessed && minimum > diff[i].distance) {
				
				minimum = diff[i].distance;
				index = i;
			}
		}
		return index;
	}

	public static void shortestSeekTimeFirst(int request[], 
													int head)
													
	{
		if (request.length == 0)
			return;
			
		// create array of objects of class node 
		node diff[] = new node[request.length]; 
		
		// initialize array
		for (int i = 0; i < diff.length; i++) 
		
			diff[i] = new node();
		
		// count total number of seek operation 
		int seek_count = 0; 
		
		// stores sequence in which disk access is done
		int[] seek_sequence = new int[request.length + 1]; 
		
		for (int i = 0; i < request.length; i++) {
			
			seek_sequence[i] = head;
			calculateDifference(request, head, diff);
			
			int index = findMin(diff);
			
			diff[index].accessed = true;
			
			// increase the total count
			seek_count += diff[index].distance; 
			
			// accessed track is now new head
			head = request[index]; 
		}
		
		// for last accessed track
		seek_sequence[seek_sequence.length - 1] = head; 
		
		System.out.println("Total number of seek operations = "
													+ seek_count);
													
		System.out.println("Seek Sequence is");
		
		// print the sequence
		for (int i = 0; i < seek_sequence.length; i++) 
			System.out.println(seek_sequence[i]);
	}

	public static void main(String[] args)
	{
		// request array
		int arr[] = { 176, 79, 34, 60, 92, 11, 41, 114 }; 
		shortestSeekTimeFirst(arr, 50);
	}
}

