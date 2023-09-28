#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "coordinate.h"

//function prototypes
void placeNQueens(std::vector<std::vector<Coordinate>> &board, int col);
bool findSafety(std::vector<Coordinate> &pastQueens, Coordinate currentQueen, int n);
std::vector<std::vector<Coordinate>> fillValues(std::vector<std::vector<Coordinate>> &board, int n);
void printBoard(std::vector<std::vector<Coordinate>> &board, int n);

int main() {
    //create an empty integer variable and fill it with the user's input
    int n;
    std::cout << "Input n up to 99 (I don't recommend more than 12): " << std::endl;
    std::cin >> n;
    std::cout << "Given n was: " << n << std::endl;

    bool keepGoing = true;
    while(keepGoing){
        if(n <= 99){
            keepGoing = false;
        } else {
            std::cout << "Input a valid n (1 to 99): " << std::endl;
            std::cin >> n;
            std::cout << "Given n was: " << n << std::endl;
        }//end else if

    }//end while

    //create a vector of vectors which is dynamic
    std::cout << "The (-4,-4) represents an empty spot on the board" << std::endl;
    std::vector<std::vector<Coordinate>> board;
    board = fillValues(board, n);
    //printBoard(board, n);
    
    //begin filling the stack and 2d array by placing queens by row and col
    //start with the first column, column zero
    placeNQueens(board, n);

    //print the final board
    printBoard(board, n);

    return 0;

}//end main


//return how many queens could be placed on the board and their position
 void placeNQueens(std::vector<std::vector<Coordinate>> &board, int n){

    //initialize a stack to hold all the queens that could be placed
    std::stack<Coordinate> nQueens;
    
    //create an extra vector to hold all the x and y values of every past queen
    std::vector<Coordinate> pastQueens;
    
    //defined the currentQueen
    //at the start of any program, the first queen is assumed to always be placed at (0,0)
    Coordinate currentQueen = Coordinate(0,0);

     Coordinate filler = Coordinate();

    //defined a counter to determine how filled the stack gets
    int filled = 0;

    //create a while loop since it's unknown how many iterations it will take
    bool keepGoing = true;

    int counter = 0;

    while(keepGoing){
        printBoard(board, n);
        counter++;
        std::cout << counter << std::endl;
        if((n == 2) || (n == 3)){
            std::cout << "No Solution" << std::endl;
            keepGoing = false;
        } else {
            if(findSafety(pastQueens, currentQueen, n) == true){
                filled++;
                if(filled >= n){
                    keepGoing = false;
                    //printBoard(board, n);
                } else{
                    //record the current queen that proved to be in a safe location
                    nQueens.push(currentQueen);
                    pastQueens.push_back(currentQueen);

                    //place the current point on the board
                    board[currentQueen.getY()][currentQueen.getX()] = currentQueen;

                    //set up the following queens
                    currentQueen.setX(0);
                    currentQueen.setY((currentQueen.getY() + 1)); 

                    //increase filled by one since the stack was increased
                    //filled++;

                    //print the board each time there is a queen placed
                    

                }//end else if
            } else if((findSafety(pastQueens, currentQueen, n) == false) && currentQueen.getX() != (n - 1)){
                /*
                this case will occur when the queen is not in a safe place
                but there is still room to shift right because the current queen's x value isn't n
                (n-1) is n because indexing begins at zero not one
                */

                //reset current position to filler
                board[currentQueen.getY()][currentQueen.getX()] = filler;

                //shift the current queen to the right by one
                currentQueen.setX((currentQueen.getX() + 1));

                //fill?

                board[currentQueen.getY()][currentQueen.getX()] = currentQueen;
                //printBoard(board, n);

            } else if((findSafety(pastQueens, currentQueen, n) == false) && currentQueen.getX() == (n - 1)){
                /* 
                This case will occur when the queen is not in a safe place and can't shift to the right anymore
                This is when we pop from the stack and give the current queen the top most past queen's coordinates
                Then we change manually shift the current queen to the right one
                Filled is also decreased
                */

            board[currentQueen.getY()][currentQueen.getX()] = filler;

                bool corner = true;
                while(corner){
                    if(currentQueen.getX() != (n - 1)){
                        corner = false;
                    } else {
                        //pop queen
                        currentQueen = nQueens.top();
                        nQueens.pop();

                        //pop from the pastQueen vector
                        pastQueens.pop_back();

                        //reset board location to empty
                        board[currentQueen.getY()][currentQueen.getX()] = filler;
                    
                        //decrease the filled amount by one
                        filled--;

                    }//end else

                }//end while


                //shift current Queen to the right
                currentQueen.setX((currentQueen.getX() + 1));

                //print board
                board[currentQueen.getY()][currentQueen.getX()] = currentQueen;
                //printBoard(board, n);


            }//end else if
        }//end else
    }//end while loop

}//end solveNQueens


//return if there is a safe place available area to place a queen
bool findSafety(std::vector<Coordinate> &pastQueens, Coordinate currentQueen, int n) {

    //check if there is a queen at a given location 
    for(int i = 0; i < pastQueens.size(); i++){
        //take the first queen placed in the stack and give it's x and y to a temporary variable
        //if the currentQueen that is trying to be placed has the same x value as a past queen
        //then they're in the same row and the curren queent danger
        Coordinate queenPos = pastQueens[i];
        if(queenPos.getX() == currentQueen.getX()){
            return false;
        } else if(queenPos.getY() == currentQueen.getY()){
            //if the y value of a previous queen and the current queen are the same
            //then they're in same column and the current queen is in danger
            return false;
        }
    }//end for

    //check both diagonals of the past queens to determine if the current queen is in any danger
    //equation for right diagnal (x + offset), (y + offset)
    //euqation for left diagnal (x - offset), (y + offset)
    for(int i = 0; i < pastQueens.size(); i++){
        Coordinate queenPos = pastQueens[i];
        for(int offset = 0; offset < n; offset++){
            //set the rightDiagnal to the right diagnal coordinate of the current past queen
            Coordinate rightDiagnal = Coordinate((queenPos.getX() + offset), (queenPos.getY() + offset));
            //set the leftDiagnal to to the left diagnal coordinate of the current past queen
            Coordinate leftDiagnal = Coordinate((queenPos.getX() - offset), (queenPos.getY() + offset));

            //see if the currentQueen is in either right or left diagnals
            if((rightDiagnal.getX() == currentQueen.getX()) && (rightDiagnal.getY() == currentQueen.getY())){
                return false;
            }//end if 
            if((leftDiagnal.getX() == currentQueen.getX()) && (leftDiagnal.getY() == currentQueen.getY())){
                return false;
            }//end if 

        }//end nested for loop

    }//end for loop

    //if none of the for loops find a collision
    //then the function returns true
    return true;

}//end findSafety


//filler value -1,-1
//fill the board, since vectors aren't automatically filled in
//i = x, j = y
std::vector<std::vector<Coordinate>> fillValues(std::vector<std::vector<Coordinate>> &board, int n){
    //since vector starts out empty we need a temporary vector to fill
    for(int i = 0; i < n; i++){
        std::vector<Coordinate> currentRow;
        for(int j = 0; j < n; j++){
            Coordinate filler = Coordinate();
            currentRow.push_back(filler);
        }//end nested for loop
        board.push_back(currentRow);
    }//end for loop
    return board;
}//end fillValues

void printBoard(std::vector<std::vector<Coordinate>> &board, int n){
    for(int i = (n - 1); i >= 0; i--){
        for(int j = 0; j < n; j++){
            std::cout << "|(" << board[i][j].getX() << "," << board[i][j].getY() << ")| ";       
        }//end nested for loop
        std::cout << "\n";
    }//end for loop
    std::cout << "\n";

}//end fillValues
