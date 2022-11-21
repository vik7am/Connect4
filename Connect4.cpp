#include<bits/stdc++.h>
using namespace std;

enum Player{PLAYER1 = 82, PLAYER2 = 66};

class Connect4Board{
    const int ROW_SIZE = 6;
    const int COLUMN_SIZE = 7;
    char board[6][7] = {'\0'};
    int columnSize[7] = {0};
    bool gameOver = false;
    
    public:
    bool isGameOver(){
        return gameOver;
    }
    bool isBoardColumnFull(int columnIndex){
        int filledBalls = columnSize[columnIndex];
        if(filledBalls >= ROW_SIZE)
            return true;
        return false;
    }
    void resetBoard(){
        for(int i=0; i<ROW_SIZE; i++)
            for(int j=0; j<COLUMN_SIZE; j++)
                board[i][j] = 0;
    }
    void dropBall(char player, int columnIndex){
        char playerName = (char)player;
        int filledBalls = columnSize[columnIndex];
        int rowIndex = ROW_SIZE - filledBalls - 1;
        board[rowIndex][columnIndex] = playerName;
        columnSize[columnIndex]++;
        for(int i=0; i<7; i++)
            if(checkBall(playerName, rowIndex, columnIndex, i))
                gameOver = true;
    }
    bool checkBall(char player, int row, int column, int direction){
        int i = row;
        int j = column;
        switch(direction){
            case 0: i=-1; j=1; break;
            case 1: i=0; j=1; break;
            case 2: i=1; j=1; break;
            case 3: i=1; j=0; break;
            case 4: i=1; j=-1; break;
            case 5: i=0; j=-1; break;
            case 6: i=-1; j=-1; break;
        }
        if(row+3*i<0 || row+3*i>=ROW_SIZE || column+3*j<0 || column+3*j>=COLUMN_SIZE)
            return false;
        if(board[row][column] != board[row+3*i][column+3*j])
            return false;
        if(board[row][column] != board[row+i][column+j])
            return false;
        if(board[row][column] != board[row+2*i][column+2*j])
            return false;
        return true;
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
    bool player1Turn = true;
    Player activePlayer = PLAYER1;
    public:
    void playGame(){
        Connect4Board game;
        int input;
        //int column;
        bool flag1;
        int turn = 0;
        int playerNo;
        game.displayBoard();
        while(turn < 42){
            if(activePlayer == PLAYER1)
                playerNo = 1;
            else
                playerNo = 2;
            //playerNo = (activePlayer == PLAYER1)? 1: 2;
            cout << "Player" << playerNo << "(" << char(activePlayer) << ") Turn: ";
            cin >> input;
            if(input <= 0 || input > 7){
                cout << "Invalid Input" << endl;
                continue;
            }
            if(game.isBoardColumnFull(input-1)){
                cout << "No space to drop ball" << endl;
                continue;
            }
            game.dropBall(activePlayer, input-1);
            game.displayBoard();
            if(game.isGameOver()){
                break;
            }
            player1Turn = !player1Turn;
            turn++;
        }
        if(turn == 42){
            cout << "Game Draw" << endl;
        }
        else if(player1Turn){
            cout << "Player 1 Won" << endl;
        }
        else{
            cout << "Player 2 Won" << endl;
        }
    }
    
    void showMainMenu(){
        int playerChoice;
        bool exitGame;
        while(exitGame == false){
            cout << "WELCOME TO CONNECT4" << endl;
            cout << "1. Start \n2. Exit \nYour Choice ";
            cin >> playerChoice;
            if(playerChoice == 1){
                playGame();
            }
            else if(playerChoice ==2){
                cout << "Thanks for Playing!" << endl;
                exitGame = true;
            }
            else{
                cout << "Invalid Input Try Again!" << endl;
            }
        }
    }
};

int main()
{
    GameManager gameManager;
        gameManager.showMainMenu();
    cout << endl;
}