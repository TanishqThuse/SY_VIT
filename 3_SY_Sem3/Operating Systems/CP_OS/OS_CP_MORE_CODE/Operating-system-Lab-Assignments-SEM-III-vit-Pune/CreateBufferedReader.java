import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class CreateBufferedReader {
    public static void main(String[] args) {
        String filePath = "C:\\Users\\91876\\Desktop\\input.txt.txt";
        try {
            FileReader fileReader = new FileReader(filePath);
            BufferedReader bufferedReader = new BufferedReader(fileReader);

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
