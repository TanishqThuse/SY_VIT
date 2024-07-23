import java.util.Scanner;

public class TicTacToe {
    static char[][] board = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    public static void printBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                System.out.print(board[i][j]);
                if (j < 2) System.out.print(" | ");
            }
            System.out.println();
            if (i < 2) System.out.println("---------");
        }
    }

    public static boolean checkWinner(char player) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
        return false;
    }

    public static boolean isBoardFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') return false;
            }
        }
        return true;
    }

    public static int[] minimax(char[][] board, int depth, boolean isMaximizing) {
        if (checkWinner('O')) return new int[]{1, -1, -1};
        if (checkWinner('X')) return new int[]{-1, -1, -1};
        if (isBoardFull()) return new int[]{0, -1, -1};

        int bestScore = isMaximizing ? Integer.MIN_VALUE : Integer.MAX_VALUE;
        int[] bestMove = new int[]{-1, -1, -1};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = isMaximizing ? 'O' : 'X';
                    int[] currentScore = minimax(board, depth + 1, !isMaximizing);
                    board[i][j] = ' ';
                    currentScore[0] += isMaximizing ? -depth : depth;

                    if (isMaximizing && currentScore[0] > bestScore) {
                        bestScore = currentScore[0];
                        bestMove = new int[]{bestScore, i, j};
                    } else if (!isMaximizing && currentScore[0] < bestScore) {
                        bestScore = currentScore[0];
                        bestMove = new int[]{bestScore, i, j};
                    }
                }
            }
        }
        return bestMove;
    }

    public static void aiMove() {
        int[] result = minimax(board, 0, true);
        if (result[1] != -1 && result[2] != -1) {
            board[result[1]][result[2]] = 'O';
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Welcome to Tic-Tac-Toe!");

        while (true) {
            printBoard();
            if (checkWinner('X')) {
                // System.out.println("Player X wins!");
                System.out.println("Human wins!");
                break;
            }
            if (checkWinner('O')) {
                // System.out.println("Player O wins!");
                System.out.println("AI wins!");
                break;
            }
            if (isBoardFull()) {
                System.out.println("It's a tie!");
                break;
            }

            System.out.println("Enter your move (row and column): ");
            int row = scanner.nextInt();
            int col = scanner.nextInt();

            if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
                System.out.println("Invalid move. Try again.");
                continue;
            }

            board[row][col] = 'X';
            if (!checkWinner('X') && !isBoardFull()) {
                aiMove();
            }
        }

        printBoard();
        scanner.close();
    }
}