#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

char matrix[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char current_marker;
int current_player;

void drawBoard() {
  
    #ifdef _WIN32         //this is the library to clear the screen
        system("cls");
    #else
        system("clear");    //and after every move they will print the fresh screen with the positions of o and x
    #endif

    cout << "  TIC TAC TOE \n";
    cout << "-----------------------------\n";
    for(int i = 0; i < 3; i++) {
        cout << setw(5) << "|";
        for(int j = 0; j < 3; j++) {
            cout << "  " << matrix[i][j] << "  |";
        }
        cout << "\n-----------------------------\n";
    }
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    // Checking if the slot is already taken by 'X' or 'O'
    if (matrix[row][col] != 'X' && matrix[row][col] != 'O') {
        matrix[row][col] = current_marker;
        return true;
    } else {
        return false;
    }
}

int winner() {
    // Rows and Columns are defined here
    for (int i = 0; i < 3; i++) {
        if (matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2]) return current_player;
        if (matrix[0][i] == matrix[1][i] && matrix[1][i] == matrix[2][i]) return current_player;
    }
    // here are the diagonals difined
    if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) return current_player;
    if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0]) return current_player;

    return 0;
}

void swapPlayer() {
    if (current_marker == 'X') current_marker = 'O';
    else current_marker = 'X';

    if (current_player == 1) current_player = 2;
    else current_player = 1;
}

void game() {
    cout << "Player 1, choose your marker (X or O): ";
    cin >> current_marker;
    current_player = 1;

    drawBoard();

    int player_won = 0;

    for (int i = 0; i < 9; i++) {
        int slot;
        cout << "Player " << current_player << " (" << current_marker << "), enter slot (1-9): ";
        cin >> slot;

        if (slot < 1 || slot > 9) {
            cout << "Invalid slot! Try again.\n";
            i--; 
            continue;
        }

        if (!placeMarker(slot)) {
            cout << "Slot occupied! Try again.\n";
            i--; 
            continue;
        }

        drawBoard();
        player_won = winner();

        if (player_won != 0) {
            cout << "Congratulations! Player " << player_won << " wins!";
            break;
        }

        swapPlayer();
    }

    if (player_won == 0) {
        cout << "It's a tie game!";
    }
}

int main() {
    game();
    return 0;
}