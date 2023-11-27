#include "./../utils/rand_gen.c"
#include "./../driver/display_driver.c"

char board[3][3];
char player = 'X', computer = 'O';

// 0 easy, 1 mid , 2 hard

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    write_string("     1 2 3\n", 11);
    for (int i = 0; i < 3; i++) {
        write_char(' ');
        write_char(' ');
        write_char(' ');
        write_char(' ');
        write_char(49 + i);
        for (int j = 0; j < 3; j++) {
            write_char(board[i][j]);
            if (j < 2) write_char('|');
        }
        write_char('\n');
        if (i < 2) write_string("     -----\n",11);
    }
    write_char('\n');
}

int isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

int isGameOver(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1;
    return 0;
}

int makeMove(int row, int col, char player) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ')
        return 0;
    board[row][col] = player;
    return 1;
}

void computerMove_easy() {
    int row, col;

    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (!makeMove(row, col, computer));
}

int minimax(char board[3][3], int depth, int isMaximizing) {
    char result = isGameOver(computer) ? 1 : isGameOver(player) ? -1 : isBoardFull() ? 0 : 2;
    if (result != 2) return result;

    int bestScore = isMaximizing ? -1000 : 1000;
    char currentPlayer = isMaximizing ? computer : player;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = currentPlayer;
                int score = minimax(board, depth + 1, !isMaximizing);
                board[i][j] = ' ';
                if (isMaximizing) {
                    if (score > bestScore) bestScore = score;
                }
                else {
                    if (score < bestScore) bestScore = score;
                }
            }
        }
    }

    return bestScore;
}

void computerMove_hard() {
    int bestScore = -1000;
    int bestMove[2] = { -1, -1 };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = computer;
                int score = minimax(board, 0, 0);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }

    makeMove(bestMove[0], bestMove[1], computer);
}
int computerMove_med() {
    // Check for a win or block the player from winning
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = computer;
                if (isGameOver(computer)) {
                    return 1; // Computer wins
                }
                board[i][j] = ' '; // Undo the move
            }
        }
    }

    // Try to take the center if it's available
    if (board[1][1] == ' ') {
        board[1][1] = computer;
        return 0; // No win yet
    }

    // Try to take a corner
    const int corners[4][2] = { {0, 0}, {0, 2}, {2, 0}, {2, 2} };
    for (int i = 0; i < 4; i++) {
        int row = corners[i][0];
        int col = corners[i][1];
        if (board[row][col] == ' ') {
            board[row][col] = computer;
            return 0; // No win yet
        }
    }

    // Take any available edge
    const int edges[4][2] = { {0, 1}, {1, 0}, {1, 2}, {2, 1} };
    for (int i = 0; i < 4; i++) {
        int row = edges[i][0];
        int col = edges[i][1];
        if (board[row][col] == ' ') {
            board[row][col] = computer;
            return 0; // No win yet
        }
    }

    return 0; // No moves left (shouldn't reach this point)
}


int tic_tac_toe(int game_diff) {
    set_seed(1);
    initializeBoard();

    while (true) {
        clear_screen();
        write_string("Welcome to Tic-Tac-Toe!\n\n", 25);

        if (game_diff == 0) {
            write_string("Easy Mode\n\n", 11);
        }
        else if (game_diff == 1) {
            write_string("Medium Mode\n\n", 13);
        }
        else {
            write_string("Hard Mode\n\n", 11);
        }

        printBoard();
        int row, col;

        write_string("Enter your move (row and column, e.g., 1 enter 2 enter): \n", 58);
        row = keyboard_get_input();
        col = keyboard_get_input();

        row -= 48;
        col -= 48;

        row--; // Adjust for 0-based indexing
        col--;

        if (!makeMove(row, col, player)) {
            write_string("Invalid move! Try again.\n", 25);
            continue;
        }

        if (isGameOver(player)) {
            printBoard();
            write_string("Congratulations! You win!\n", 26);
            break;
        }

        if (isBoardFull()) {
            printBoard();
            write_string("It's a draw!\n", 13);
            break;
        }

        if (game_diff == 0) computerMove_easy();
        else if (game_diff == 1) computerMove_med();
        else computerMove_hard();

        if (isGameOver(computer)) {
            printBoard();
            write_string("Computer wins! You lose.\n", 25);
            break;
        }

        if (isBoardFull()) {
            printBoard();
            write_string("It's a draw!\n", 13);
            break;
        }
    }

    return 0;
}
