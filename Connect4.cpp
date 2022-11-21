#include<bits/stdc++.h>
using namespace std;

class Connect4Board{
    const static int ROW_SIZE = 6;
    const static int COLUMN_SIZE = 7;
    char board[ROW_SIZE][COLUMN_SIZE] = {'\0'};
    int columnSize[COLUMN_SIZE] = {0};
    
    public:
    bool gameOver = false;
    void resetBoard(){
        for(int i=0; i<ROW_SIZE; i++)
            for(int j=0; j<COLUMN_SIZE; j++)
                board[i][j] = 0;
    }
    bool dropBall(char player, int column){
        int filledBalls = columnSize[column];
        if(filledBalls >= ROW_SIZE)
            return false;
        int row = ROW_SIZE - filledBalls - 1;
        board[row][column] = player;
        columnSize[column]++;
        for(int i=0; i<7; i++)
            if(checkBall(player, row, column, i))
                gameOver = true;
        return true;
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
    public:
    void playGame(){
        Connect4Board game;
        char input;
        int column;
        bool flag1;
        int turn = 0;
        game.displayBoard();
        while(turn < 42){
            if(player1Turn){
                cout << "Player 1(R) Turn: ";
                cin >> column;
                if(column>0 && column <= 7)
                    flag1 = game.dropBall('R', column-1);
                else{
                    cout << "Invalid column number" << endl;
                    continue;
                }
            }
            else{
                cout << "Player 2(B) Turn: ";
                cin >> column;
                if(column>0 && column <= 7)
                    flag1 = game.dropBall('B', column-1);
                else{
                    cout << "Invalid column number" << endl;
                    continue;
                }
            }
            if(flag1 == false){
                cout << "No space to drop ball" << endl;
                continue;
            }
            game.displayBoard();
            if(game.gameOver){
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