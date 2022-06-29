#pragma once
#include "Board.h"
#include "pMCTS.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <time.h>
#include <array>

using namespace std;

class Reversi{
  private:
    char player;
    char cpu;
  public:
    Reversi();
    ~Reversi();
    char playerToken();
    void turner2P(Board);
    void turner1P(Board);
    void turner0P(Board);
    void turner0PHeur(Board);
    bool movesLeft(Board, char);
    bool validNum(string);
    bool validMove(Board, int, int, char);
    void flipTokens(Board, int, int, char);
    bool flipChecker(Board, int, int, char);
    bool topCheck(Board, int, int, int, int);
    bool bottomCheck(Board, int, int, int, int);
    bool leftCheck(Board, int, int, int, int);
    bool rightCheck(Board, int, int, int, int);
    bool topLeftCheck(Board, int, int, int, int);
    bool topRightCheck(Board, int, int, int, int);
    bool bottomLeftCheck(Board, int, int, int, int);
    bool bottomRightCheck(Board, int, int, int, int);
    void vertFlipHelper(Board, int, int*, int, int);
    void horizFlipHelper(Board, int, int*, int, int);
    void diagFlipHelper(Board, int*, int*, int, int);
    bool isFull(Board);
    char gameWon(Board);
    void winMessage(char);
    char getPlayer();
    char getCPU();
};
