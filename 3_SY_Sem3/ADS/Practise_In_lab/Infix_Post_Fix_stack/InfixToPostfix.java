// // Approach 1
import java.util.*;

class InfixPostFix{
    
    public static String infixToPostfix(String infix){
        Stack<Character> stack = new Stack<>();
        
        String postFix = "";
        int n = infix.length();
        int flag = 0;
        char LastOperator = ' ' ;
        for(int i=0; i<n; i++){
            char ch = infix.charAt(i);
            if(ch=='(' || ch==')'){
                continue;
            }
            if(ch-'a'>= 0 && ch-'a'<=25){
                postFix += ch;
            }
            else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'){
                if(i==n-2){
                    LastOperator = infix.charAt(n-2);
                }
                if(flag == 0){
                    stack.push(ch);
                    flag = 1;
                }
                else{
                    flag = 0;
                    postFix += stack.pop();
                }
            }
        }
        while(!stack.isEmpty()){
            postFix += stack.pop();
        }
        return postFix+LastOperator;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter the infix expression: ");
        String infix = sc.nextLine();
        
        System.out.println("Postfix expression: " + infixToPostfix(infix));
        sc.close();
    }
}

// // //Approach 2 : 
// import java.util.*;
// public class InfixToPostfix {

//     static int prec(char c) {
//         if (c == '^')
//             return 3;
//         else if (c == '/' || c == '*')
//             return 2;
//         else if (c == '+' || c == '-')
//             return 1;
//         else
//             return -1;
//     }

//     static char associativity(char c) {
//         if (c == '^')
//             return 'R';
//         return 'L';
//     }

//     static void infixToPostfix(String s) {
//         StringBuilder result = new StringBuilder();
//         Stack<Character> stack = new Stack<>();

//         for (int i = 0; i < s.length(); i++) {
//             char c = s.charAt(i);

//             if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
//                 result.append(c);
//             } else if (c == '(') {
//                 stack.push(c);
//             } else if (c == ')') {
//                 while (!stack.isEmpty() && stack.peek() != '(') {
//                     result.append(stack.pop());
//                 }
//                 stack.pop();
//             } else {
//                 while (!stack.isEmpty() && (prec(s.charAt(i)) < prec(stack.peek()) ||
//                                              prec(s.charAt(i)) == prec(stack.peek()) &&
//                                                  associativity(s.charAt(i)) == 'L')) {
//                     result.append(stack.pop());
//                 }
//                 stack.push(c);
//             }
//         }

//         while (!stack.isEmpty()) {
//             result.append(stack.pop());
//         }

//         System.out.println(result);
//     }

//     public static void main(String[] args) {
//         // String exp = "a+b*(c^d-e)^(f+g*h)-i";
//         Scanner sc = new Scanner(System.in);
//         System.out.println("Enter the infix expression: ");
//         String exp = sc.nextLine();

//         System.out.println("Postfix expression: ");
//         infixToPostfix(exp);
//     }
// }