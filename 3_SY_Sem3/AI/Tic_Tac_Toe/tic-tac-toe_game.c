#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*Logic : 
1) Print board initially in printBoard() function
2) Take turn of player in takeTurn() function
3) Check if game is over in checkGameOver() function
4) If game is over, print the result and end the game
5) If game is not over, switch to the other player and continue playing
6) Repeat steps 2-5 until the game is over
7) Print the result of the game (win/tie) after the game is over
8) End the game (exit with code 0) after printing the result (line 5
9) Run the game (line 1
10) Print the board (line
11) Start the game with player X (line 1
*/

char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

void printBoard() {
    printf("%c | %c | %c\n", board[0], board[1], board[2]);
    printf("%c | %c | %c\n", board[3], board[4], board[5]);
    printf("%c | %c | %c\n", board[6], board[7], board[8]);
}

void takeTurn(char player) {
    int position;
    printf("%c's turn.\n", player);
    printf("Choose a position from 1-9: ");
    scanf("%d", &position);
    position -= 1;

    while (position < 0 || position > 8 || board[position] != '-') {
        printf("Invalid input or position already taken. Choose a different position: ");
        scanf("%d", &position);
        position -= 1;
    }

    board[position] = player;
    printBoard();
}

char* checkGameOver() {
    // Check for a win
    if ((board[0] == board[1] && board[1] == board[2] && board[0] != '-') ||
        (board[3] == board[4] && board[4] == board[5] && board[3] != '-') ||
        (board[6] == board[7] && board[7] == board[8] && board[6] != '-') ||
        (board[0] == board[3] && board[3] == board[6] && board[0] != '-') ||
        (board[1] == board[4] && board[4] == board[7] && board[1] != '-') ||
        (board[2] == board[5] && board[5] == board[8] && board[2] != '-') ||
        (board[0] == board[4] && board[4] == board[8] && board[0] != '-') ||
        (board[2] == board[4] && board[4] == board[6] && board[2] != '-')) {
        return "win";
    }
    // Check for a tie
    else if (strchr(board, '-') == NULL) {
        return "tie";
    }
    // Game is not over
    else {
        return "play";
    }
}

int main() {
    printBoard();
    char currentPlayer = 'X';
    bool gameOver = false;
    
    while (!gameOver) {
        takeTurn(currentPlayer);
        char* gameResult = checkGameOver();
        
        if (strcmp(gameResult, "win") == 0) {
            printf("%c wins!\n", currentPlayer);
            gameOver = true;
        } else if (strcmp(gameResult, "tie") == 0) {
            printf("It's a tie!\n");
            gameOver = true;
        } else {
            // Switch to the other player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    return 0;
}
