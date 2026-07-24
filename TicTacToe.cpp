/*
 * Mini Game Project: Tic Tac Toe
 * --------------------------------
 * A console-based Tic Tac Toe game in C++ demonstrating core programming
 * concepts: loops, arrays, and conditional logic.
 *
 * Features:
 *   - Two-player mode (Player X vs Player O)
 *   - Dynamic board display after every move
 *   - Win/loss/draw detection
 *   - Replay option after each game
 */

#include <iostream>
#include <limits>

using namespace std;

const int SIZE = 3;

// ---------- Display the current board ----------
void displayBoard(char board[SIZE][SIZE]) {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        cout << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

// ---------- Initialize board with position numbers 1-9 ----------
void initializeBoard(char board[SIZE][SIZE]) {
    char num = '1';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = num++;
        }
    }
}

// ---------- Check if a move at position (1-9) is valid ----------
bool isValidMove(char board[SIZE][SIZE], int pos) {
    if (pos < 1 || pos > 9) return false;

    int row = (pos - 1) / SIZE;
    int col = (pos - 1) % SIZE;

    // A cell is still empty if it holds its original number character
    return board[row][col] != 'X' && board[row][col] != 'O';
}

// ---------- Place a move on the board ----------
void makeMove(char board[SIZE][SIZE], int pos, char symbol) {
    int row = (pos - 1) / SIZE;
    int col = (pos - 1) % SIZE;
    board[row][col] = symbol;
}

// ---------- Check for a win ----------
bool checkWin(char board[SIZE][SIZE], char symbol) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        bool rowWin = true, colWin = true;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != symbol) rowWin = false;
            if (board[j][i] != symbol) colWin = false;
        }
        if (rowWin || colWin) return true;
    }

    // Check diagonals
    bool diag1 = true, diag2 = true;
    for (int i = 0; i < SIZE; i++) {
        if (board[i][i] != symbol) diag1 = false;
        if (board[i][SIZE - 1 - i] != symbol) diag2 = false;
    }

    return diag1 || diag2;
}

// ---------- Check if the board is completely filled (draw) ----------
bool isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

// ---------- Get a valid move from the current player ----------
int getPlayerMove(char board[SIZE][SIZE], char currentPlayer) {
    int pos;

    while (true) {
        cout << "Player " << currentPlayer << ", enter position (1-9): ";

        if (!(cin >> pos)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }

        if (!isValidMove(board, pos)) {
            cout << "Invalid move. That position is either taken or out of range.\n";
            continue;
        }

        return pos;
    }
}

// ---------- Play a single round of Tic Tac Toe ----------
void playGame() {
    char board[SIZE][SIZE];
    initializeBoard(board);

    char currentPlayer = 'X';
    bool gameWon = false;

    cout << "\n===================================\n";
    cout << "       TIC TAC TOE - NEW GAME       \n";
    cout << "===================================\n";
    cout << "Positions are numbered 1-9 as shown below:\n";
    displayBoard(board);

    while (true) {
        int pos = getPlayerMove(board, currentPlayer);
        makeMove(board, pos, currentPlayer);

        displayBoard(board);

        if (checkWin(board, currentPlayer)) {
            cout << "*** Player " << currentPlayer << " wins! Congratulations! ***\n";
            gameWon = true;
            break;
        }

        if (isBoardFull(board)) {
            cout << "*** It's a draw! Well played both. ***\n";
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    (void)gameWon; // outcome already communicated above
}

// ---------- Main ----------
int main() {
    char playAgain;

    do {
        playGame();

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nThanks for playing Tic Tac Toe!\n";
    return 0;
}
