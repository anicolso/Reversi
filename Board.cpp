#include "Board.h"

#define BOARD_X 8
#define BOARD_Y 8

// 0 = X, 1 = O, -1 = empty
Board::Board(){
  board = new int*[BOARD_Y];
  for(int i = 0; i < 8; i++){
    board[i] = new int[BOARD_X];
    for(int j = 0; j < 8; j++){
      if((i == 3 && j == 3) || (i ==4 && j == 4)){
        board[i][j] = 1;
      }else if((i == 3 && j == 4) || (i ==4 && j == 3)){
        board[i][j] = 0;
      }else{
        board[i][j] = -1;
      }
    }
  }
}

Board::~Board(){
  
}

void Board::freeBoard(int** board){
  for(int i = 0; i < BOARD_Y; i++){
    delete[] board[i];
  }
  delete[] board;
}

void Board::drawBoard(){
  cout << "\n   0  1  2  3  4  5  6  7" << endl;
  for(int i = 0; i < BOARD_X; i++){
    cout << i << " ";
    for(int j = 0; j < BOARD_Y; j++){
      if(board[i][j] == 0){
        cout << " X ";
      } else if(board[i][j] == 1){
        cout << " O ";
      } else{
        cout << "   ";
      }
    }
    cout << "" << endl;
  }
  cout << "" << endl;
}

//FOR TROUBLESHOOTING
void Board::boardVals(){
  for(int i = 0; i < BOARD_X; i++){
    for(int j = 0; j < BOARD_Y; j++){
      cout << board[i][j];
    }
    cout << "" << endl;
  }
}

bool Board::isFree(int x, int y){
  if(board[y][x] == 0 || board[y][x] == 1){
    return false;
  } else if(board[y][x] == -1){
    return true;
  }else{
    return false;
  }
}

void Board::mover(int x, int y, char t){
  int turn;
  if(t == 'X'){
    turn = 0;
  }else{
    turn = 1;
  }
  board[y][x] = turn;
}

void Board::flipper(int x, int y, int turn){
  board[y][x] = turn;
}


Board Board::copy(Board newBoard, Board currBoard){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      newBoard.board[i][j] = currBoard.board[i][j];
    }
  }
  return newBoard;
}

Board Board::deepCopy(Board newBoard, Board currBoard){
  newBoard.board = new int* [8];
  for(int i = 0; i < 8; i++){
    newBoard.board[i] = new int[8];
    for(int j = 0; j < 8; j++){
      newBoard.board[i][j] = currBoard.board[i][j];
    }
  }
  return newBoard;
}
