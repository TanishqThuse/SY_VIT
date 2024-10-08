import java.util.*;

class fifo{
    public static void main(String args[]){
        int pages[] = {1, 3, 0, 3, 5, 6, 3};
        int capacity = 3; //aka frames in our case
        int n = pages.length;
        
        // Set containing current pages
        HashSet<Integer> s = new HashSet<>(capacity);
    
        // Queue to store the pages in FIFO manner
        Queue<Integer> indexes = new LinkedList<>() ;

        int page_faults = 0;
        
        for (int i=0; i<n; i++){
            // Check if the set can hold more pages or not
            if (s.size() < capacity){
                // Insert it into set if not present
                // already which represents page fault
                if (!s.contains(pages[i])){
                    s.add(pages[i]);
    
                    // increment page fault
                    page_faults++;
    
                    // Push the current page into the queue
                    indexes.add(pages[i]);
                }
            }
    
            // If the set is full then need to perform FIFO
            // i.e. remove the first page of the queue from
            // set and queue both and insert the current page
            else
            {
                // Check if current page is not already
                // present in the set
                if (!s.contains(pages[i]))
                {
                    //Pop the first page from the queue
                    int val = indexes.peek();
    
                    indexes.poll();
    
                    // Remove the indexes page
                    s.remove(val);
    
                    // insert the current page
                    s.add(pages[i]);
    
                    // push the current page into
                    // the queue
                    indexes.add(pages[i]);
    
                    // Increment page faults
                    page_faults++;
                }
            }
        }
        System.out.println(page_faults);
        
    }
}
