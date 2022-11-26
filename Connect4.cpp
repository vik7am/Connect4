#include<iostream>
using namespace std;

enum Player{PLAYER1 = 82, PLAYER2 = 66};
enum Direction{NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST, NORTH};

class Connect4Board{
    const int ROW_SIZE = 6;
    const int COLUMN_SIZE = 7;
    char board[6][7];
    int availableSpace[7];
    int rowIndex;
    int columnIndex;

    public:
    void resetBoard(){
        for(int i=0; i<ROW_SIZE; i++)
            for(int j=0; j<COLUMN_SIZE; j++)
                board[i][j] = 0;
        for(int i=0; i<COLUMN_SIZE; i++)
            availableSpace[i] = ROW_SIZE;
    }

    bool isBoardColumnFull(){
        if(availableSpace[columnIndex] > 0)
            return false;
        return true;
    }

    bool dropBall(char playerName, int column){
        columnIndex = column -1;
        if(isBoardColumnFull())
            return false;
        rowIndex = availableSpace[columnIndex] - 1;
        board[rowIndex][columnIndex] = playerName;
        availableSpace[columnIndex]--;
        return true;
    }

    bool playerWon(char playerName){
        int i,j;
        int counter;
        if(chackDirection(1, 0))
            return true;
        if(chackDirection(0, 1))
            return true;
        if(chackDirection(1, 1))
            return true;
        if(chackDirection(1, -1))
            return true;
        return false;
    }

    bool chackDirection(int i, int j){
        int counter = 0;
        for(int k=1; k<=3; k++){
            if(!validPos(rowIndex + i*k, columnIndex + j*k))
                break;
            if(board[rowIndex + i*k][columnIndex + j*k] == board[rowIndex][columnIndex])
                counter++;
            else
                break;
        }
        for(int k=1; k<=3; k++){
            if(!validPos(rowIndex - i*k, columnIndex - j*k))
                break;
            if(board[rowIndex - i*k][columnIndex - j*k] == board[rowIndex][columnIndex])
                counter++;
            else
                break;
        }
        if(counter >= 3)
            return true;
        return false;
    }

    bool validPos(int row, int col, int boundaryX = 6, int boundaryY = 7){
        if(row<0 && row>=boundaryX && col<0 && col>=boundaryY)
            return false;
        return true;
    }

    void displayBoard(){
        cout << endl;
        cout << "  1   2   3   4   5   6   7  " << endl;
        cout << "|---|---|---|---|---|---|---|" << endl;
        for(int i=0; i<6; i++){
            printf("| ");
            for(int j=0; j<7; j++){
                cout << board[i][j] << " | ";
            }
            cout << "\n|---|---|---|---|---|---|---|" << endl;
        }
        cout << endl;
    }
};
class GameManager{
    Player activePlayer;
    Connect4Board game;
    int input;
    int playerNo;
    int turn;
    public:
    void playGame(){
        activePlayer = PLAYER1;
        turn = 0;
        game.resetBoard();
        game.displayBoard();
        while(turn < 42){
            if(turn == 10)
                turn = turn;
            playerNo = (activePlayer == PLAYER1)? 1: 2;
            cout << "Player " << playerNo << " (" << char(activePlayer) << ") Turn: ";
            cin >> input;
            if(input <= 0 || input > 7){
                cout << "Invalid Column number" << endl;
                continue;
            }
            if(game.dropBall(activePlayer, input) == false){
                cout << "No space to drop ball" << endl;
                continue;
            }
            game.displayBoard();
            if(game.playerWon(activePlayer))
                break;
            activePlayer = (activePlayer == PLAYER1)? PLAYER2: PLAYER1;
            turn++;
        }
        if(turn == 42)
            cout << "\nGame Draw\n" << endl;
        else if(activePlayer == PLAYER1)
            cout << "\nPlayer 1 Won\n" << endl;
        else
            cout << "\nPlayer 2 Won\n" << endl;
        cout << "Press 1 to continue ";
        cin >> input;
    }
};

void welcomeMessage(){
    cout << "\nWELCOME TO CONNECT4\n";
    cout << "\nRULES :-\n";
    cout << "1. Two-player (red & blue) game.\n";
    cout << "2. Board size is  6 rows x 7 columns.\n";
    cout << "3. A player wins if he/she is able to connect 4 dots horizontally, vertically or diagonally.\n";
    cout << "4. Draw when the matrix is fully filled.\n";
    cout << "\nHow to play :-\n";
    cout << "1. Game always starts with the player - 1 i.e. Red(R).\n";
    cout << "2. In each step, each player can choose the column number in which they want to drop the ball.\n";
    cout << "3. Rows will be filled from bottom to top in any column.\n" << endl;

}

int main()
{
    GameManager gameManager;
    int playerChoice;
    bool exitGame;
    while(exitGame == false){
        welcomeMessage();
        cout << "MAIN MENU \n1. Start \n2. Exit \nYour Choice: ";
        cin >> playerChoice;
        if(playerChoice == 1){
            gameManager.playGame();
        }
        else if(playerChoice ==2){
            cout << "Thanks for Playing!" << endl;
            exitGame = true;
        }
        else{
            cout << "Invalid Input Try Again!" << endl;
        }
    }
    cout << endl;
}