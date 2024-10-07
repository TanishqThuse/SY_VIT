import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReadFileWithBuffer {
    public static void main(String[] args) {
        String filePath = "C:\\Users\\91876\\Desktop\\input.txt.txt";
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(filePath));
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                System.out.println(line);
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
