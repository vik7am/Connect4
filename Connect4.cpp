#include<iostream>
using namespace std;

enum Player{PLAYER1 = 82, PLAYER2 = 66};
enum Direction{NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST, NORTH};

class Connect4Board{
    const int ROW_SIZE = 6;
    const int COLUMN_SIZE = 7;
    char board[6][7];
    int availableSpace[7];
    int mainRowIndex;
    int mainColumnIndex;
    public:
    void resetBoard(){
        for(int i=0; i<ROW_SIZE; i++)
            for(int j=0; j<COLUMN_SIZE; j++)
                board[i][j] = 0;
        for(int i=0; i<COLUMN_SIZE; i++)
            availableSpace[i] = ROW_SIZE;
    }
    bool isBoardColumnFull(){
        if(availableSpace[mainColumnIndex] > 0)
            return false;
        return true;
    }
    bool dropBall(char playerName, int column){
        mainColumnIndex = column -1;
        if(isBoardColumnFull())
            return false;
        mainRowIndex = availableSpace[mainColumnIndex] - 1;
        board[mainRowIndex][mainColumnIndex] = playerName;
        availableSpace[mainColumnIndex]--;
        return true;
    }
    bool checkConnect4(char playerName){
        int i,j;
        // check in all directions for a pair of 4
        for(int k=0; k<7; k++)
            if(checkBall(mainRowIndex, mainColumnIndex, k))
                return true;
        // check all adjecent positions for a pair of 4
        for(int direction=0; direction<7; direction++){
            switch(direction){
            case NORTH_EAST: i=-1; j=1; break;
            case EAST:       i=0; j=1; break;
            case SOUTH_EAST: i=1; j=1; break;
            case SOUTH_WEST: i=1; j=-1; break;
            case WEST:       i=0; j=-1; break;
            case NORTH_WEST: i=-1; j=-1; break;
            default : continue;
            }
            // if adjecent position is not equal to maim position then contine the loop for next
            if(board[mainRowIndex][mainColumnIndex] != board[mainRowIndex+i][mainColumnIndex+j])
                continue;
            // check in all directions for a pair of 4
            for(int k=0; k<7; k++)
                if(checkBall(mainRowIndex+i, mainColumnIndex+j, k))
                    return true;
        }
        return false;
    }
    bool checkBall(int rowIndex, int columnIndex, int direction){
        int i,j;
        switch(direction){
            case NORTH_EAST: i=-1; j=1; break;
            case EAST:       i=0; j=1; break;
            case SOUTH_EAST: i=1; j=1; break;
            case SOUTH:      i=1; j=0; break;
            case SOUTH_WEST: i=1; j=-1; break;
            case WEST:       i=0; j=-1; break;
            case NORTH_WEST: i=-1; j=-1; break;
        }
        // Returns false if 4th location in the given direction is out of bounds
        if(rowIndex+3*i<0 || rowIndex+3*i>=ROW_SIZE || columnIndex+3*j<0 || columnIndex+3*j>=COLUMN_SIZE)
            return false;
        // compares vales of 1st and 4th location in the board 
        if(board[rowIndex][columnIndex] != board[rowIndex+3*i][columnIndex+3*j])
            return false;
        if(board[rowIndex][columnIndex] != board[rowIndex+i][columnIndex+j])
            return false;
        if(board[rowIndex][columnIndex] != board[rowIndex+2*i][columnIndex+2*j])
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
    bool gameOver;
    int input;
    int playerNo;
    int turn;
    public:
    void playGame(){
        activePlayer = PLAYER1;
        turn = 0;
        gameOver = false;
        game.resetBoard();
        game.displayBoard();
        while(turn < 42){
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
            for(int i=0; i<7; i++)
                if(game.checkConnect4(activePlayer))
                    gameOver = true;
            game.displayBoard();
            if(gameOver)
                break;
            activePlayer = (activePlayer == PLAYER1)? PLAYER2: PLAYER1;
            turn++;
        }
        if(turn == 42){
            cout << "\nGame Draw\n" << endl;
        }
        else if(activePlayer == PLAYER1){
            cout << "\nPlayer 1 Won\n" << endl;
        }
        else{
            cout << "\nPlayer 2 Won\n" << endl;
        }
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