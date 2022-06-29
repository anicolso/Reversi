#pragma once
#include <iostream>

using namespace std;

class Board{
  public:
    int** board;
    Board();
    ~Board();
    //Board(const Board&);
    void freeBoard(int**);
    Board copy(Board, Board);
    Board deepCopy(Board, Board);
    bool isFree(int, int);
    void mover(int, int, char);
    void flipper(int, int, int);
    void drawBoard();
    void boardVals();

  private:
};
