// Take input.txt and buffer
import java.io.FileReader;
import java.io.IOException;

public class ReadFileExample {
    public static void main(String[] args) {
        String filePath = "C:\\Users\\91876\\Desktop\\input.txt.txt";
        try {
            FileReader fileReader = new FileReader(filePath);
            int character;
            while ((character = fileReader.read()) != -1) {
                System.out.print((char) character);
            }
            fileReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


// buffer containig Input.txt


