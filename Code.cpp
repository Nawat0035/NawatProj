#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int ROWS = 8;
const int COLS = 8;
const int TYPES = 5;

vector<vector<char>> board(ROWS, vector<char>(COLS));
int score = 0;

char randomCandy() {
    return 'A' + rand() % TYPES;
}

void generateBoard() {
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            board[i][j] = randomCandy();
}

void printBoard() {

    cout << "\n========== Puzzue Candy Crush ==========\n";
    cout << "r = row horizontal c = column vertical\n";
    cout << "Score : " << score << endl;

    cout << "   ";
    for(int j=0;j<COLS;j++) cout << j << " ";
    cout << endl;

    for(int i=0;i<ROWS;i++){
        cout << i << "  ";
        for(int j=0;j<COLS;j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    cout << "==========================================\n";
}

void explodeRow(int r){
    for(int j=0;j<COLS;j++){
        if(board[r][j] != ' '){
            board[r][j]=' ';
            score +=10;
        }
    }
}

void explodeCross(int r,int c){

    for(int j=0;j<COLS;j++){
        if(board[r][j]!=' '){
            board[r][j]=' ';
            score+=10;
        }
    }

    for(int i=0;i<ROWS;i++){
        if(board[i][c]!=' '){
            board[i][c]=' ';
            score+=10;
        }
    }
}

bool findMatches(){

    bool found=false;

    // horizontal
    for(int i=0;i<ROWS;i++){

        int count=1;

        for(int j=1;j<COLS;j++){

            if(board[i][j]==board[i][j-1])
                count++;
            else{

                if(count>=3){

                    found=true;

                    if(count==4)
                        explodeRow(i);

                    else if(count>=5)
                        explodeCross(i,j-1);

                    else{

                        for(int k=0;k<count;k++){
                            if(board[i][j-1-k]!=' '){
                                board[i][j-1-k]=' ';
                                score+=10;
                            }
                        }

                    }

                }

                count=1;
            }

        }

        if(count>=3){

            found=true;

            if(count==4)
                explodeRow(i);

            else if(count>=5)
                explodeCross(i,COLS-1);

            else{

                for(int k=0;k<count;k++){
                    if(board[i][COLS-1-k]!=' '){
                        board[i][COLS-1-k]=' ';
                        score+=10;
                    }
                }

            }

        }

    }

    // vertical

    for(int j=0;j<COLS;j++){

        int count=1;

        for(int i=1;i<ROWS;i++){

            if(board[i][j]==board[i-1][j])
                count++;
            else{

                if(count>=3){

                    found=true;

                    if(count==4)
                        explodeRow(i-1);

                    else if(count>=5)
                        explodeCross(i-1,j);

                    else{

                        for(int k=0;k<count;k++){
                            if(board[i-1-k][j]!=' '){
                                board[i-1-k][j]=' ';
                                score+=10;
                            }
                        }

                    }

                }

                count=1;
            }

        }

        if(count>=3){

            found=true;

            if(count==4)
                explodeRow(ROWS-1);

            else if(count>=5)
                explodeCross(ROWS-1,j);

            else{

                for(int k=0;k<count;k++){
                    if(board[ROWS-1-k][j]!=' '){
                        board[ROWS-1-k][j]=' ';
                        score+=10;
                    }
                }

            }

        }

    }

    return found;
}

void dropCandies(){

    for(int j=0;j<COLS;j++){

        for(int i=ROWS-1;i>=0;i--){

            if(board[i][j]==' '){

                int k=i-1;

                while(k>=0 && board[k][j]==' ')
                    k--;

                if(k>=0){

                    board[i][j]=board[k][j];
                    board[k][j]=' ';

                }

            }

        }

    }

}

void fillNew(){

    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            if(board[i][j]==' ')
                board[i][j]=randomCandy();

}

void resolveBoard(){

    while(true){

        if(!findMatches())
            break;

        dropCandies();
        fillNew();

    }

}

bool swapCandy(int r1,int c1,int r2,int c2){

    if(abs(r1-r2)+abs(c1-c2)!=1)
        return false;

    swap(board[r1][c1],board[r2][c2]);

    if(findMatches()){
        dropCandies();
        fillNew();
        resolveBoard();
        return true;
    }

    swap(board[r1][c1],board[r2][c2]);
    return false;

}

int main(){

    srand(time(0));

    generateBoard();
    resolveBoard();

    score = 0; 

    while(true){

        printBoard();

        int r1,c1,r2,c2;

        cout << "Swap (r1 c1 r2 c2) : ";
        cin >> r1 >> c1 >> r2 >> c2;

        if(!swapCandy(r1,c1,r2,c2))
            cout << "Invalid move!\n";

    }

}