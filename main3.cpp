#include <iostream>
#include <vector>
#include <cctype> // For isdigit
using namespace std;

// Function to display the game board
void displayBoard(const vector<char>& board) {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n";
    cout << "\n";
}

// Function to check for a winner
bool checkWinner(const vector<char>& board, char player) {
    // Winning combinations
    vector<vector<int>> winningCombos = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    // Check each winning combination
    for (const auto& combo : winningCombos) {
        if (board[combo[0]] == player && board[combo[1]] == player && board[combo[2]] == player) {
            return true;
        }
    }
    return false;
}

// Function to check for a draw
bool isDraw(const vector<char>& board) {
    for (char cell : board) {
        if (isdigit(cell)) { // If any cell still contains a number, it's not a draw
            return false;
        }
    }
    return true;
}

// Main game function
void playGame() {
    vector<char> board(9); // Board with 9 cells
    for (int i = 0; i < 9; ++i) {
        board[i] = '1' + i; // Initialize cells with numbers
    }

    char currentPlayer = 'X';
    bool gameOver = false;

    // Main game loop
    while (!gameOver) {
        displayBoard(board);

        // Ask current player for their move
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        int move;
        cin >> move;

        // Validate move
        if (move < 1 || move > 9 || board[move - 1] == 'X' || board[move - 1] == 'O') {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        // Make the move
        board[move - 1] = currentPlayer;

        // Check for a winner
        if (checkWinner(board, currentPlayer)) {
            displayBoard(board);
            cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
        }
        // Check for a draw
        else if (isDraw(board)) {
            displayBoard(board);
            cout << "It's a draw!\n";
            gameOver = true;
        } else {
            // Switch player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

int main() {
    cout << "Welcome to Tic Tac Toe!\n";
    char playAgain;

    do {
        playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}
