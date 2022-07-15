#include "Reversi.h"

Reversi::Reversi(){
  player = playerToken();
  if(player == 'X'){
    cpu = 'O';
  }else{
    cpu = 'X';
  }
}

Reversi::~Reversi(){

}

char Reversi::playerToken(){
  const char first[2] = {'X', 'O'};
  int r = rand() % 2;
  return first[r];
}

bool Reversi::isFull(Board bo){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(bo.board[j][i] == -1){
        return false;
      }
    }
  }
  return true;
}

void Reversi::turner2P(Board bo){
  char turn = 'X';
  string x_coord;
  string y_coord;

while(!isFull(bo) && (movesLeft(bo, cpu) || movesLeft(bo, player))){
    while (turn == player && movesLeft(bo, player)){
      cout << turn << "'s turn!" << endl;
      cout << "Enter x-value: ";
      cin >> x_coord;
      if (validNum(x_coord)){
        cout << "Enter y-value: ";
        cin >> y_coord;
        if(validNum(y_coord)){
          int myX = stoi(x_coord);
          int myY = stoi(y_coord);
          if(validMove(bo, myX, myY, turn)){
              bo.mover(myX, myY, turn);
              flipTokens(bo, myX, myY, turn);
              turn = cpu;
              bo.drawBoard();
              break;
          }
        }
      }
      cout << "INCORRECT MOVE ENTERED. Try again! ";
    }
    turn = cpu;

    while (turn == cpu && movesLeft(bo, cpu)){
      cout << turn << "'s turn!" << endl;
      cout << "Enter x-value: ";
      cin >> x_coord;
      if (validNum(x_coord)){
        cout << "Enter y-value: ";
        cin >> y_coord;
        if(validNum(y_coord)){
          int myX = stoi(x_coord);
          int myY = stoi(y_coord);
          if(validMove(bo, myX, myY, turn)){
              bo.mover(myX, myY, turn);
              flipTokens(bo, myX, myY, turn);
              turn = player;
              bo.drawBoard();
              break;
          }
        }
      }
      cout << "INCORRECT MOVE ENTERED. Try again! ";
    }
    turn = player;
  }
}

void Reversi::turner1P(Board bo){
  char turn = 'X';
  string x_coord;
  string y_coord;

while(!isFull(bo) && (movesLeft(bo, cpu) || movesLeft(bo, player))){
    while (turn == player && movesLeft(bo, player)){
      cout << turn << "'s turn!" << endl;
      cout << "Enter x-value: ";
      cin >> x_coord;
      if (validNum(x_coord)){
        cout << "Enter y-value: ";
        cin >> y_coord;
        if(validNum(y_coord)){
          int myX = stoi(x_coord);
          int myY = stoi(y_coord);

          if(validMove(bo, myX, myY, turn)){
              bo.mover(myX, myY, turn);
              flipTokens(bo, myX, myY, turn);
              turn = cpu;
              bo.drawBoard();
              break;
          }
        }
      }
      cout << "INCORRECT MOVE ENTERED. Try again! ";
    }

    if(!isFull(bo) && (movesLeft(bo, cpu))){
      pMCTS pmcts = pMCTS();
      pair<int, int> chosen = pmcts.pureMCTS(bo, cpu);
      bo.mover(chosen.first, chosen.second, turn);
      flipTokens(bo, chosen.first, chosen.second, turn);
      turn = player;
      cout << "AI'S turn!" << endl;
      bo.drawBoard();
      cout << "AI PLAYED X: " << chosen.first << ", Y: " << chosen.second << endl;
    }else{
      turn = player;
    }
  }
}

void Reversi::turner0P(Board bo){
  char turn = 'X';
  string x_coord;
  string y_coord;

  while(!isFull(bo) && (movesLeft(bo, cpu) || movesLeft(bo, player))){
    if(!isFull(bo) && movesLeft(bo, player) && turn == player){
      pMCTS pmcts2 = pMCTS();
      cout << "AI1'S turn!" << endl;
      pair<int, int> chosen2 = pmcts2.pureMCTS(bo, player);
      bo.mover(chosen2.first, chosen2.second, turn);
      flipTokens(bo, chosen2.first, chosen2.second, turn);
      turn = cpu;
      bo.drawBoard();
      cout << "AI1 Played  X: " << chosen2.first << ", Y: " << chosen2.second << endl;
    }else{
      turn = cpu;
    }

    if(!isFull(bo) && movesLeft(bo, cpu) && turn == cpu){
      pMCTS pmcts = pMCTS();
      cout << "AI2'S turn!" << endl;
      pair<int, int> chosen = pmcts.pureMCTS(bo, cpu);
      bo.mover(chosen.first, chosen.second, turn);
      flipTokens(bo, chosen.first, chosen.second, turn);
      turn = player;
      bo.drawBoard();
      cout << "AI2 Played  X: " << chosen.first << ", Y: " << chosen.second << endl;
    }else{
      turn = player;
    }
  }
}

void Reversi::turner0PHeur(Board bo){
  char turn = 'X';
  string x_coord;
  string y_coord;

  while(!isFull(bo) && (movesLeft(bo, cpu) || movesLeft(bo, player))){
    if(!isFull(bo) && movesLeft(bo, player) && turn == player){
      pMCTS pmctsHeur = pMCTS();
      cout << "\npMCTS AI'S turn!" << endl;
      pair<int, int> chosen2 = pmctsHeur.pureMCTS(bo, player);
      bo.mover(chosen2.first, chosen2.second, turn);
      flipTokens(bo, chosen2.first, chosen2.second, turn);
      turn = cpu;
      bo.drawBoard();
      cout << "pMCTS AI Played  X: " << chosen2.first << ", Y: " << chosen2.second << endl;
    }else{
      turn = cpu;
    }

    if(!isFull(bo) && movesLeft(bo, cpu) && turn == cpu){
      pMCTS pmcts = pMCTS();
      cout << "\nAI Heur's turn!" << endl;
      pair<int, int> chosen = pmcts.heurMCTS(bo, cpu);
      bo.mover(chosen.first, chosen.second, turn);
      flipTokens(bo, chosen.first, chosen.second, turn);
      turn = player;
      bo.drawBoard();
      cout << "AI Heur Played  X: " << chosen.first << ", Y: " << chosen.second << endl;
    }else{
      turn = player;
    }
  }
}

bool Reversi::validNum(string coord){
  if(coord.length() > 1){
    return false;
  }else if(!(isdigit(coord[0]))){
    return false;
  }else if(isdigit(coord[0])){
    int myCoord = stoi(coord);
    if(0 <= myCoord <= 7){
      return true;
    }else{
      return false;
    }
  }else{
    return false;
  }
}

bool Reversi::validMove(Board bo, int x, int y, char t){
  Board checkBoard = Board();
  checkBoard.copy(checkBoard, bo);

  if(bo.board[y][x] == -1){
    checkBoard.mover(x, y, t);
    if(flipChecker(checkBoard, x, y, t)){
      checkBoard.freeBoard(checkBoard.board);
      return true;
    }else{
      checkBoard.freeBoard(checkBoard.board);
      return false;
    }
  }else{
    checkBoard.freeBoard(checkBoard.board);
    return false;
  }
}

  bool Reversi::movesLeft(Board currBoard, char plyr){
    vector<pair<int, int>> moves;
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        if(validMove(currBoard, i, j, plyr)){
            pair<int, int> availableMove(i, j);
            moves.push_back(availableMove);
            if(moves.size() > 0){
              return true;
            }
        }
      }
    }
    return false;
  }

  /*

  //top left check
  if((j-1) < 0 || (i-1) < 0){
    //Out of bounds -- do nothing
  }else if(bo.board[j-1][i-1] != -1){
    return true;
  }

  //top middle check
  if((j-1) < 0){
    //Out of bounds -- do nothing
  }else if(bo.board[j-1][i] != -1){
    return true;
  }

  //top right check
  if((j-1) < 0 || (i+1) > 7){
    //Out of bounds -- do nothing
  }else if(bo.board[j-1][i+1] != -1){
    return true;
  }

  //left check
  if((i-1) < 0){
    //Out of bounds -- do nothing
  }else if(bo.board[j][i-1] != -1){
    return true;
  }

  //right check
  if((j) < 0 || (i+1) > 7){
    //Out of bounds -- do nothing
  }else if(bo.board[j][i+1] != -1){
    return true;
  }

  //bottom left check
  if((j+1) > 7 || (i-1) < 0){
    //Out of bounds -- do nothing
  }else if(bo.board[j+1][i-1] != -1){
    return true;
  }

  //bottom check
  if((j+1) > 7){
    //Out of bounds -- do nothing
  }else if(bo.board[j+1][i] != -1){
    return true;
  }

  //bottom right check
  if((j+1) > 7 || (i+1) > 7){
    //Out of bounds -- do nothing
  }else if(bo.board[j+1][i+1] != -1){
    return true;
  }

  return false;
  */

  // [j--][i--],[j--][i],[j--][i++]
   //[j][i--]              [j][i++]
   //[j++][i--],[j++][i],[j++][i++]

bool Reversi::flipChecker(Board bo, int myX, int myY, char t){
  int turn;
  int opp;

  if(t == 'X'){
    turn = 0;
    opp = 1;
  } else{
    turn = 1;
    opp = 0;
  }

  return topCheck(bo, myX, myY, turn, opp)
  || bottomCheck(bo, myX, myY, turn, opp)
  || leftCheck(bo, myX, myY, turn, opp)
  || rightCheck(bo, myX, myY, turn, opp)
  || topLeftCheck(bo, myX, myY, turn, opp)
  || topRightCheck(bo, myX, myY, turn, opp)
  || bottomLeftCheck(bo, myX, myY, turn, opp)
  || bottomRightCheck(bo, myX, myY, turn, opp);
}

void Reversi::flipTokens(Board bo, int myX, int myY, char t){
  int turn;
  int opp;

  if(t == 'X'){
    turn = 0;
    opp = 1;
  } else{
    turn = 1;
    opp = 0;
  }

  topCheck(bo, myX, myY, turn, opp);
  bottomCheck(bo, myX, myY, turn, opp);
  leftCheck(bo, myX, myY, turn, opp);
  rightCheck(bo, myX, myY, turn, opp);
  topLeftCheck(bo, myX, myY, turn, opp);
  topRightCheck(bo, myX, myY, turn, opp);
  bottomLeftCheck(bo, myX, myY, turn, opp);
  bottomRightCheck(bo, myX, myY, turn, opp);
}

bool Reversi::topCheck(Board bo, int x, int y, int turn, int opp){
  int toFlip[6]; //maximum size is 6 b/c needs to be token on either end to flip
  int input = 0;

  for(int j = (y-1); j >= 0; j--){
    if(j < 0 || j > 7){
      return false;
    }

    if(bo.board[j][x] == -1){
      break;
    }else if(bo.board[j][x] == opp){
      toFlip[input] = j;
      input++;
    }else if(bo.board[j][x] == turn){
      if(input > 0){
        vertFlipHelper(bo, x, toFlip, turn, input);
        return true;
      }
      return false;
    }else{
      break;
    }
  }
  return false;
}

bool Reversi::bottomCheck(Board bo, int x, int y, int turn, int opp){
  int toFlip[6]; //maximum size is 6 b/c needs to be token on either end to flip
  int input = 0;

  for(int j = (y+1); j <= 7; j++){
    if(j < 0 || j > 7){
      return false;
    }

    if(bo.board[j][x] == -1){
      return false;
    }else if(bo.board[j][x] == opp){
      toFlip[input] = j;
      input++;
    }else if(bo.board[j][x] == turn){
      if(input > 0){
        vertFlipHelper(bo, x, toFlip, turn, input);
        return true;
      }
      return false;
    }
  }
  return false;
}

bool Reversi::leftCheck(Board bo, int x, int y, int turn, int opp){
  int toFlip[6]; //maximum size is 6 b/c needs to be token on either end to flip
  int input = 0;

  for(int i = (x-1); i >= 0; i--){
    if(i < 0 || i > 7){
      return false;
    }

    if(bo.board[y][i] == -1){
      break;
    }else if(bo.board[y][i] == opp){
      toFlip[input] = i;
      input++;
    }else if(bo.board[y][i] == turn){
      if(input > 0){
        horizFlipHelper(bo, y, toFlip, turn, input);
        return true;
      }
      return false;
    }
  }
  return false;
}

bool Reversi::rightCheck(Board bo, int x, int y, int turn, int opp){
  int toFlip[6]; //maximum size is 6 b/c needs to be token on either end to flip
  int input = 0;

  for(int i = (x+1); i <= 7; i++){
    if(i < 0 || i > 7){
      return false;
    }
    if(bo.board[y][i] == -1){
      break;
    }else if(bo.board[y][i] == opp){
      toFlip[input] = i;
      input++;
    }else if(bo.board[y][i] == turn){
      if(input > 0){
        horizFlipHelper(bo, y, toFlip, turn, input);
        return true;
      }
      return false;
    }
  }
  return false;
}

bool Reversi::topLeftCheck(Board bo, int x, int y, int turn, int opp){
  int toFlipX[6]; //maximum size is 6 b/c needs to be token on either end to flip
  int toFlipY[6];
  int input = 0;

  if((x-1) < 0 || (y+1) > 7){
    return false;
  }

  int i = x - 1;
  int j = y + 1;

  for(int k = 0; k <= 7; k++){
      if(i < 0 || i > 7 || j < 0 || j > 7){
        return false;
      }

      if(0 <= x <= 7 && 0 <= y <= 7){
        if(bo.board[j][i] == -1){
          break;
        }else if(bo.board[j][i] == opp){
          toFlipY[input] = j;
          toFlipX[input] = i;
          i--;
          j++;
          input++;
        }else if(bo.board[j][i] == turn){
          if(input > 0){
            diagFlipHelper(bo, toFlipX, toFlipY, turn, input);
            return true;
          }
          break;
        }
      }
  }
  return false;
}

bool Reversi::topRightCheck(Board bo, int x, int y, int turn, int opp){
  int toFlipX[6]; //maximum size is 6 b/c needs to be token on either end to flip
  int toFlipY[6];
  int input = 0;

  if((x+1) > 7 || (y+1) > 7){
    return false;
  }

  int i = x + 1;
  int j = y + 1;

  for(int k = 0; k <= 7; k++){
      //Check that still within bounds
      if(i < 0 || i > 7 || j < 0 || j > 7){
        return false;
      }

      if(0 <= x <= 7 && 0 <= y <= 7){
        if(bo.board[j][i] == -1){
          break;
        }else if(bo.board[j][i] == opp){
          toFlipY[input] = j;
          toFlipX[input] = i;
          i++;
          j++;
          input++;
        }else if(bo.board[j][i] == turn){
          if(input > 0){
            diagFlipHelper(bo, toFlipX, toFlipY, turn, input);
            return true;
          }
          break;
        }else{
          break;
        }
      }else{
        break;
      }
  }
  return false;
}

bool Reversi::bottomLeftCheck(Board bo, int x, int y,  int turn, int opp){
  int toFlipX[6]; //maximum size is 6 b/c needs to be token on either end to flip
  int toFlipY[6];
  int input = 0;

  if((x-1) < 0 || (y-1) < 0){
    return false;
  }

  int i = x - 1;
  int j = y - 1;

  for(int k = 0; k <= 7; k++){
      //Check that still within bounds
      if(i < 0 || i > 7 || j < 0 || j > 7){
        return false;
      }

      if(0 <= x <= 7 && 0 <= y <= 7){
        if(bo.board[j][i] == -1){
          break;
        }else if(bo.board[j][i] == opp){
          toFlipY[input] = j;
          toFlipX[input] = i;
          i--;
          j--;
          input++;
        }else if(bo.board[j][i] == turn){
          if(input > 0){
            diagFlipHelper(bo, toFlipX, toFlipY, turn, input);
            return true;
          }
          break;
        }else{
          break;
        }
      }else{
        break;
      }
  }
  return false;
}

bool Reversi::bottomRightCheck(Board bo, int x, int y, int turn, int opp){
  int toFlipX[6]; //maximum size is 6 b/c needs to be token on either end to flip
  int toFlipY[6];
  int input = 0;

  if((x+1) > 7 || (y-1) < 0){
    return false;
  }

  int i = x + 1;
  int j = y - 1;

  for(int k = 0; k <= 7; k++){
      //Check that still within bounds
      if(i < 0 || i > 7 || j < 0 || j > 7){
        return false;
      }

      if(0 <= i <= 7 && 0 <= j <= 7){
        if(bo.board[j][i] == -1){
          break;
        }else if(bo.board[j][i] == opp){
          toFlipY[input] = j;
          toFlipX[input] = i;
          i++;
          j--;
          input++;
        }else if(bo.board[j][i] == turn){
          if(input > 0){
            diagFlipHelper(bo, toFlipX, toFlipY, turn, input);
            return true;
          }
          break;
        }else{
          break;
        }
      }else{
        break;
      }
  }
  return false;
}

void Reversi::diagFlipHelper(Board bo, int* toFlipX, int* toFlipY, int turn, int size){
  for(int i = 0; i < size; i++){
    if(bo.board[toFlipY[i]][toFlipX[i]] == turn || toFlipX[i] == 0 || toFlipY[i] == 0){
      break;
    } else{
      bo.flipper(toFlipX[i], toFlipY[i], turn);
    }
  }
}


void Reversi::vertFlipHelper(Board bo, int x, int* toFlip, int turn, int size){
    for(int i = 0; i < size; i++){
      if(bo.board[toFlip[i]][x] == turn || toFlip[i] == 0){
        break;
      } else{
        bo.flipper(x, toFlip[i], turn);
      }
    }
}

void Reversi::horizFlipHelper(Board bo, int y, int* toFlip, int turn, int size){
    for(int i = 0; i < size; i++){
      if(bo.board[y][toFlip[i]] == turn || toFlip[i] == 0){
        break;
      } else{
        bo.flipper(toFlip[i], y, turn);
      }
    }
}

char Reversi::gameWon(Board bo){
  int x_pts = 0;
  int o_pts = 0;

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(bo.board[j][i] == 0){
        x_pts++;
      }else if(bo.board[j][i] == 1){
        o_pts++;
      }
    }
  }

  if(x_pts > o_pts){
    return 'X';
  }else if(o_pts > x_pts){
    return 'O';
  }else{
    return 'D';
  }
}

void Reversi::winMessage(char winner){
  if(winner == player){
    cout << "CONGRATULATIONS, PLAYER 1!\n" << player << " IS THE WINNER! " << endl;
  } else if(winner == cpu){
    cout << "Your opponent WINS! \nBetter luck next time, Player 1" << endl;
  } else{
    cout << "DRAW!\nBoth players scored the same!" << endl;
  }
}

char Reversi::getPlayer(){
  return player;
}

char Reversi::getCPU(){
  return cpu;
}

int main(){
/*
  Board board = Board();
  Reversi reversi = Reversi();
  pMCTS pmcts = pMCTS();
*/

  Board board = Board();
  Reversi reversi = Reversi();
  string gameMode;
  srand(time(NULL));


  cout << "    ________________________________" << endl;
  cout << "" << endl;
  cout << "   |  Alyssa's MCTS Reversi Project  |" << endl;
  cout << "    ________________________________\n" << endl;
  cout << "Welcome to Reversi, created for CMPT310!\n" << endl;

  cout << "How would you like to play today?" << endl;
  cout << "--Enter '1' for 2-player" << endl;
  cout << "--Enter '2' for 1-player against an AI" << endl;
  cout << "--Enter '3' for an AI-vs-AI simulation (no heuristics)" << endl;
  cout << "--Enter '4' for an AI-vs-heuristic AI simulation" << endl;
  cout << "Your selection: ";
  cin >> gameMode;

  if(reversi.validNum(gameMode)){
    int choice = stoi(gameMode);
    if(choice == 1){
      cout << "\nPlayer 1's token is '" << reversi.getPlayer() << "'." << endl;
      cout << "Player 2's token is '" << reversi.getCPU() << "'." << endl;
      cout << "Let the game begin! \n" << endl;

      board.drawBoard();
      reversi.turner2P(board);

      char w = reversi.gameWon(board);
      reversi.winMessage(w);
    }else if(choice == 2){
      cout << "\nYour token is '" << reversi.getPlayer() << "'." << endl;
      cout << "AI's token is '" << reversi.getCPU() << "'." << endl;
      cout << "Let the game begin! \n" << endl;

      board.drawBoard();
      reversi.turner1P(board);

      char w = reversi.gameWon(board);
      reversi.winMessage(w);
    }else if(choice == 3){
      cout << "\nAI1's token is '" << reversi.getPlayer() << "'." << endl;
      cout << "AI2's token is '" << reversi.getCPU() << "'." << endl;
      cout << "Let the game begin! \n" << endl;

      board.drawBoard();
      reversi.turner0P(board);

      char w = reversi.gameWon(board);
      if(w == reversi.getPlayer()){
        cout << "AI1 WINS!" << endl;
      }else if(w == reversi.getCPU()){
        cout << "AI2 WINS!" << endl;
      }else{
        cout << "DRAW!" << endl;
      }
      /*
      int ai1Wins = 0;
      int ai2Wins = 0;
      int draw = 0;

      while(ai1Wins < 2){
        Board board2 = Board();
        board2.drawBoard();
        reversi.turner0P(board2);

        char w = reversi.gameWon(board2);
        if(w == reversi.getPlayer()){
          cout << "AI1 WINS!" << endl;
          ai1Wins++;
        }else if(w == reversi.getCPU()){
          cout << "AI2 WINS!" << endl;
          ai2Wins++;
        }else{
          cout << "DRAW!" << endl;
          draw++;
        }
        cout << "Ai1 wins: " << ai1Wins << "  |  Ai2 wins: " << ai2Wins << "  |  Draws: " << draw << endl;

        board2.freeBoard(board2.board);
        board2.~Board();
      }
      cout << "Ai1 wins: " << ai1Wins << "  |  Ai2 wins: " << ai2Wins << "  |  Draws: " << draw << endl;
      */
    }else if(choice == 4){
      cout << "\nPure MCTS AI token is '" << reversi.getPlayer() << "'." << endl;
      cout << "Heuristic AI's token is '" << reversi.getCPU() << "'." << endl;
      cout << "Let the game begin! \n" << endl;

      board.drawBoard();
      reversi.turner0PHeur(board);

      char w = reversi.gameWon(board);
      if(w == reversi.getPlayer()){
        cout << "PURE MCTS WINS!" << endl;
      }else if(w == reversi.getCPU()){
        cout << "HEUR MCTS WINS!" << endl;
      }else{
        cout << "DRAW!" << endl;
      }
/*
      board.drawBoard();
      reversi.turner0PHeur(board);

      char w = reversi.gameWon(board);
      if(w == reversi.getPlayer()){
        cout << "AI WITHOUT HEURISTICS WINS!" << endl;
      }else if(w == reversi.getCPU()){
        cout << "AI WITH HEURISTICS WINS!" << endl;
      }else{
        cout << "DRAW!" << endl;
      }
*/
    }else{
      cout << "Invalid Entry. Exiting Game..." << endl;
    }
  }
}

/*
  cout << "What will your move be? " << endl;
  cout << "Enter x-value (0-7): ";
  while(!(cin >> x_coord)){
    cin.clear();
    cout << "Please enter a valid x-value (0-7): ";
  }

  cout << "Enter y-value (0-7): ";
  while(!(cin >> y_coord)){
    cin.clear();
    cout << "Please enter a valid y-value (0-7): ";
  }*/
