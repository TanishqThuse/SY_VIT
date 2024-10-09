import java.util.*;

// Represents a node of the required tree

class ExpressionTree {

    static class Node {
        char data;
        Node left, right;
    
        public Node(char item) {
            data = item;
            left = right = null;
        }
    }

	static boolean isOperator(char c) {
		return c == '+' || c == '-' || c == '*' || c == '/';
	}

	static Node buildTree(String prefix) {
		Stack<Node> stack = new Stack<Node>();

		// Traverse the prefix expression in reverse order
		for (int i = prefix.length() - 1; i >= 0; i--) {
			char c = prefix.charAt(i);

			if (isOperator(c)) {
				Node left = stack.pop();
				Node right = stack.pop();
				Node node = new Node(c);
				node.left = left;
				node.right = right;
				stack.push(node);
			} else {
				Node node = new Node(c);
				stack.push(node);
			}
		}

		Node root = stack.peek();
		stack.pop();

		return root;
	}

	// Function to print the infix expression for the tree
	static void inOrder(Node node) {
		if (node != null) {
			inOrder(node.left);
			System.out.print(node.data + " ");
			inOrder(node.right);
		}
	}

	// Function to print the postfix expression for the tree
	static void postOrder(Node node) {
		if (node != null) {
			postOrder(node.left);
			postOrder(node.right);
			System.out.print(node.data + " ");
		}
	}

    static void preOrder(Node node){
        if(node!=null){
            System.err.print(node.data + " ");
            preOrder(node.left);
            preOrder(node.right);
        }
    }

	public static void main(String[] args) {
		
        Scanner sc = new Scanner(System.in);
        
        String prefix = "*+ab-cd";
        //a+b*c-d
        // System.out.println("Enter the prefix expression");

        // String prefix = sc.nextLine();  

		Node root = buildTree(prefix);

		System.out.println("Infix expression is:");
		inOrder(root);

        System.out.println("\nPrefix expression is:");
        preOrder(root);

		System.out.println("\nPostfix expression is:");
		postOrder(root);
	
        System.out.println();
    }

}
