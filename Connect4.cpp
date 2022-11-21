#include<bits/stdc++.h>
using namespace std;

enum Player{PLAYER1 = 82, PLAYER2 = 66};

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
    bool checkBall(char player, int direction){
        int i = rowIndex;
        int j = columnIndex;
        switch(direction){
            case 0: i=-1; j=1; break;
            case 1: i=0; j=1; break;
            case 2: i=1; j=1; break;
            case 3: i=1; j=0; break;
            case 4: i=1; j=-1; break;
            case 5: i=0; j=-1; break;
            case 6: i=-1; j=-1; break;
        }
        if(rowIndex+3*i<0 || rowIndex+3*i>=ROW_SIZE || columnIndex+3*j<0 || columnIndex+3*j>=COLUMN_SIZE)
            return false;
        if(board[rowIndex][columnIndex] != board[rowIndex+3*i][columnIndex+3*j])
            return false;
        if(board[rowIndex][columnIndex] != board[rowIndex+i][columnIndex+j])
            return false;
        if(board[rowIndex][columnIndex] != board[rowIndex+2*i][columnIndex+2*j])
            return false;
        return true;
    }
    void displayBoard(){
        cout << "  1   2   3   4   5   6   7  " << endl;
        cout << "|---|---|---|---|---|---|---|" << endl;
        for(int i=0; i<6; i++){
            printf("| ");
            for(int j=0; j<7; j++){
                cout << board[i][j] << " | ";
            }
            cout << "\n|---|---|---|---|---|---|---|" << endl;
        }
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
        game.resetBoard();
        game.displayBoard();
        while(turn < 42){
            playerNo = (activePlayer == PLAYER1)? 1: 2;
            cout << "Player" << playerNo << "(" << char(activePlayer) << ") Turn: ";
            cin >> input;
            if(input <= 0 || input > 7){
                cout << "Invalid Input" << endl;
                continue;
            }
            if(game.dropBall(activePlayer, input) == false){
                cout << "No space to drop ball" << endl;
                continue;
            }
            for(int i=0; i<7; i++)
                if(game.checkBall(activePlayer, i))
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

int main()
{
    GameManager gameManager;
    int playerChoice;
     bool exitGame;
    while(exitGame == false){
        cout << "WELCOME TO CONNECT4" << endl;
        cout << "1. Start \n2. Exit \nYour Choice ";
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