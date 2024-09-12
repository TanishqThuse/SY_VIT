// Tic toc toe with AI (MinMax Algo).

#include <stdio.h>
#include <stdbool.h>

#define SIZE 3
#define PLAYER 'X'
#define AI 'O'
#define EMPTY ' '

void printBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
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
            if (board[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}


int evaluate(char board[SIZE][SIZE]) {
    if (checkWin(board, AI)) {
        return 10;
    } else if (checkWin(board, PLAYER)) {
        return -10;
    } else {
        return 0;
    }
}

int minimax(char board[SIZE][SIZE], int depth, bool isMaximizing) {
    int score = evaluate(board);

    if (score == 10 || score == -10) {
        return score;
    }

    if (isBoardFull(board)) {
        return 0;
    }

    if (isMaximizing) {
        int best = -1000;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    int val = minimax(board, depth + 1, !isMaximizing);
                    best = (val > best) ? val : best;
                    board[i][j] = EMPTY;
                }
            }
        }

        return best;
    } else {
        int best = 1000;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    int val = minimax(board, depth + 1, !isMaximizing);
                    best = (val < best) ? val : best;
                    board[i][j] = EMPTY;
                }
            }
        }

        return best;
    }
}


void makeAIMove(char board[SIZE][SIZE]) {
    int bestMove = -1;
    int bestScore = -1000;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveScore = minimax(board, 0, false);
                board[i][j] = EMPTY;

                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove = i * SIZE + j;
                }
            }
        }
    }

    int row = bestMove / SIZE;
    int col = bestMove % SIZE;
    board[row][col] = AI;
}


void playGame() {
    char board[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }

    while (true) {
       
        printf("Current board:\n");
        printBoard(board);

        int row, col;
        printf("Player %c's turn. Enter row and column (e.g., 1 1 for row 1, column 1): ", PLAYER);
        scanf("%d %d", &row, &col);

        if (row < 1 || row > SIZE || col < 1 || col > SIZE || board[row - 1][col - 1] != EMPTY) {
            printf("Invalid move. Please try again.\n");
            continue;
        }

        board[row - 1][col - 1] = PLAYER;

        if (checkWin(board, PLAYER)) {
            printf("Congratulations! Player %c wins!\n", PLAYER);
            printBoard(board);
            break;
        }

        if (isBoardFull(board)) {
            printf("It's a draw!\n");
            printBoard(board);
            break;
        }

        printf("AI's turn:\n");
        makeAIMove(board);

        if (checkWin(board, AI)) {
            printf("AI wins! Better luck next time.\n");
            printBoard(board);
            break;
        }

        if (isBoardFull(board)) {
            printf("It's a draw!\n");
            printBoard(board);
            break;
        }
    } 
}

int main() {
    printf("Welcome to 1-Player Tic-Tac-Toe against AI!\n");
    playGame();
    return 0;
}
