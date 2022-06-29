#pragma once
#include "Reversi.h"
#include "Board.h"
#include <vector>
#include <time.h>

class pMCTS{
public:
  pMCTS();
  ~pMCTS();
  vector<pair<int,int>> moveGenerator(Board, char);
  pair<int, int> pureMCTS(Board, char);
  pair<int, int> heurMCTS(Board, char);
  int decisionHelper(Board, char);
  int gameScore(Board, char);
  pair<int, int> random(vector<pair<int, int>> moves);
};
