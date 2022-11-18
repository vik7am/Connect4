#include<bits/stdc++.h>
using namespace std;

class Connect4Board{
    const static int ROW_SIZE = 6;
    const static int COLUMN_SIZE = 7;
    char board[ROW_SIZE][COLUMN_SIZE] = {'\0'};
    int columnSize[COLUMN_SIZE] = {0};
    public:
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
        game.displayBoard();
        for(int i=0; i<6; i++){
            if(player1Turn){
                cout << "Player 1(R) Turn: ";
                cin >> column;
                flag1 = game.dropBall('R', column-1);
            }
            else{
                cout << "Player 2(B) Turn: ";
                cin >> column;
                flag1 = game.dropBall('B', column-1);
            }
            if(flag1 == false){
                cout << "No space to drop ball" << endl;
                continue;
            }
            game.displayBoard();
            player1Turn = !player1Turn;
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