
// tic toc toe without AI


#include <stdio.h>
#include <stdbool.h>

#define SIZE 3

void printBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) {
   printf("|");}
        }
        printf("\n");
         if (i < SIZE - 1) {
            printf("---+---+---\n");
        }
        }
    }


bool checkWin(char board[SIZE][SIZE], char player) {
   
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }

    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

bool isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

void playGame() {
    char board[SIZE][SIZE];
    char currentPlayer = 'X';
    int row, col;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }

    while (true) {
        printf("Current board:\n");
        printBoard(board);

        printf("Player %c's turn. Enter row and column (e.g., 1 1 for row 1, column 1): ", currentPlayer);
        scanf("%d %d", &row, &col);

        if (row < 1 || row > SIZE || col < 1 || col > SIZE) {
            printf("Invalid move. Please try again.\n");
            continue;
        }

        if (board[row - 1][col - 1] != ' ') {
            printf("Cell already occupied. Please try again.\n");
            continue;
        }

        board[row - 1][col - 1] = currentPlayer;

        if (checkWin(board, currentPlayer)) {
            printf("Congratulations! Player %c wins!\n", currentPlayer);
            printBoard(board);
            break;
        }

        if (isBoardFull(board)) {
            printf("It's a draw!\n");
            printBoard(board);
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    printf("Welcome to 2-Player Tic-Tac-Toe!\n");
    playGame();
    return 0;
}
