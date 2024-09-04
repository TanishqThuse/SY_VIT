import java.util.*;

public class infixApp2 {
    static int prec(char c) {
                if (c == '^')
                    return 3;
                else if (c == '/' || c == '*')
                    return 2;
                else if (c == '+' || c == '-')
                    return 1;
                else
                    return -1;
            }
        
            static char associativity(char c) {
                if (c == '^')
                    return 'R';
                return 'L';
            }
        
            static void infixToPostfix(String s) {
                StringBuilder result = new StringBuilder();
                Stack<Character> stack = new Stack<>();
        
                for (int i = 0; i < s.length(); i++) {
                    char c = s.charAt(i);
        
                    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
                        result.append(c);
                    } else if (c == '(') {
                        stack.push(c);
                    } else if (c == ')') {
                        while (!stack.isEmpty() && stack.peek() != '(') {
                            result.append(stack.pop());
                        }
                        stack.pop();
                    } else {
                        while (!stack.isEmpty() && (prec(s.charAt(i)) < prec(stack.peek()) ||
                                                     prec(s.charAt(i)) == prec(stack.peek()) &&
                                                         associativity(s.charAt(i)) == 'L')) {
                            result.append(stack.pop());
                        }
                        stack.push(c);
                    }
                }
        
                while (!stack.isEmpty()) {
                    result.append(stack.pop());
                }
        
                System.out.println(result);
            }
        
            public static void main(String[] args) {
                // String exp = "a+b*(c^d-e)^(f+g*h)-i";
                Scanner sc = new Scanner(System.in);
                System.out.println("Enter the infix expression: ");
                String exp = sc.nextLine();
        
                System.out.println("Postfix expression: ");
                infixToPostfix(exp);
            }
}
