#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char board[3][3];
char currentPlayer = 'X';
char playerX[50], playerO[50];
int moveHistory[9][2];
int moveCount = 0;
int scoreX = 0, scoreO = 0, draws = 0;

void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
    moveCount = 0;
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" ");
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("-----------\n");
    }
    printf("\n");
}

void printScoreboard() {
    printf("Scoreboard:\n");
    printf("  %s (X): %d\n", playerX, scoreX);
    printf("  %s (O): %d\n", playerO, scoreO);
    printf("  Draws: %d\n\n", draws);
}

void printMoveHistory() {
    printf("Move History:\n");
    for (int i = 0; i < moveCount; i++) {
        printf("  %c: (%d, %d)\n",
               (i % 2 == 0) ? 'X' : 'O',
               moveHistory[i][0], moveHistory[i][1]);
    }
    printf("\n");
}

int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return 1;
        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
            return 1;
    }

    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return 1;

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return 1;

    return 0;
}

int checkDraw() {
    return moveCount >= 9;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void undoMove() {
    if (moveCount == 0) {
        printf("No moves to undo.\n");
        return;
    }

    moveCount--;
    int row = moveHistory[moveCount][0];
    int col = moveHistory[moveCount][1];
    board[row][col] = ' ';
    switchPlayer();
    printf("Last move undone.\n");
}

void playGame() {
    int row, col;
    char input[10];

    initializeBoard();
    currentPlayer = 'X';

    while (1) {
        printBoard();
        printScoreboard();
        printMoveHistory();

        printf("Player %c (%s), Enter move as 'row col', or 'u' to undo last move:\n",
               currentPlayer, (currentPlayer == 'X') ? playerX : playerO);
        scanf("%s", input);

        if (strcmp(input, "u") == 0) {
            undoMove();
            continue;
        }

        row = atoi(input);
        scanf("%d", &col);

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        board[row][col] = currentPlayer;
        moveHistory[moveCount][0] = row;
        moveHistory[moveCount][1] = col;
        moveCount++;

        if (checkWin()) {
            printBoard();
            printf("?? Player %c (%s) wins! ??\n", currentPlayer,
                   (currentPlayer == 'X') ? playerX : playerO);
            if (currentPlayer == 'X') scoreX++;
            else scoreO++;
            break;
        }

        if (checkDraw()) {
            printBoard();
            printf("?? It's a draw between %s and %s!\n", playerX, playerO);
            draws++;
            break;
        }

        switchPlayer();
    }
}

int main() {
    char playAgain;

    printf("=== TIC-TAC-TOE GAME ===\n");

    printf("Enter name for Player X: ");
    fgets(playerX, sizeof(playerX), stdin);
    playerX[strcspn(playerX, "\n")] = 0;

    printf("Enter name for Player O: ");
    fgets(playerO, sizeof(playerO), stdin);
    playerO[strcspn(playerO, "\n")] = 0;

    do {
        playGame();
        printf("\nPlay again? (y/n): ");
        scanf(" %c", &playAgain);
    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\nThanks for playing, %s and %s!\n", playerX, playerO);
    printf("Final Scores:\n");
    printScoreboard();

    return 0;
}

