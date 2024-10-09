// Tree traversal in Java

import java.util.Scanner;

public class BinaryTree {


    static class Node {
        int item;
        Node left, right;
    
        public Node(int key) {
        item = key;
        left = right = null;
        }
    }

    // Root of Binary Tree
    Node root;
  
    BinaryTree() {
    root = null;
    }
  
    void postorder(Node node) {
    if (node == null)
      return;
  
    // Traverse left
    postorder(node.left);
    // Traverse right
    postorder(node.right);
    // Traverse root
    System.out.print(node.item + " -> ");
    }
  
    void inorder(Node node) {
    if (node == null)
      return;
  
    // Traverse left
    inorder(node.left);
    // Traverse root
    System.out.print(node.item + " -> ");
    // Traverse right
    inorder(node.right);
    }
  
    void preorder(Node node) {
    if (node == null)
      return;
  
    // Traverse root
    System.out.print(node.item + " -> ");
    // Traverse left
    preorder(node.left);
    // Traverse right
    preorder(node.right);
    }

    public static void insert(Node root, int key) {
        if (root == null) {
            root = new Node(key);
            return;
        }
        if (key < root.item) {
            if (root.left == null) {
                root.left = new Node(key);
            } else {
                insert(root.left, key);
            }
        } else {
            if (root.right == null) {
                root.right = new Node(key);
            } else {
                insert(root.right, key);
            }
        }
    }
  
    public static void main(String[] args) {
    BinaryTree tree = new BinaryTree();
    Scanner sc = new Scanner(System.in);

    //insert the nodes
    // int[] arr = { 12, 1, 5, 9, 6 };


    System.out.println("Enter number of nodes in tree");
    int n = sc.nextInt();
    
    int[] arr = new int[n];
    System.out.println("Enter the nodes of the tree");

    for(int i=0; i<n; i++){
        arr[i] = sc.nextInt();
    }



    for (int i = 0; i < arr.length; i++) {
        if (i == 0) {
            tree.root = new Node(arr[i]);
        } else {
            insert(tree.root, arr[i]);
        }
    }

    System.out.println("Inorder traversal");
    tree.inorder(tree.root);
  
    System.out.println("\nPreorder traversal ");
    tree.preorder(tree.root);
  
    System.out.println("\nPostorder traversal");
    tree.postorder(tree.root);

    System.out.println();
    }
  }