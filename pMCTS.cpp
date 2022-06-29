#include "pMCTS.h"

#define PLAYOUTS 20

pMCTS::pMCTS(){
}

pMCTS::~pMCTS(){
}

vector<pair<int, int>> pMCTS::moveGenerator(Board currBoard, char t){
  Reversi reversi;
  vector<pair<int, int>> moves;
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(reversi.validMove(currBoard, i, j, t)){
          pair<int, int> availableMove(i, j);
          moves.push_back(availableMove);
      }
    }
  }
  return moves;
}

pair<int, int> pMCTS::pureMCTS(Board currBoard, char cpu){
  Reversi reversi;
  vector<pair<int, int>> possibleMoves = moveGenerator(currBoard, cpu);
  int size = possibleMoves.size();
  int ti = clock();
  int* wins = new int[size];

  char opp;
  if(cpu == 'X'){
    opp = 'O';
  }else{
    opp = 'X';
  }
  char turn = opp;


  //while(ti < 2000){
  for(int i = 0; i < size; i++){
    wins[i] = 0;

    for(int j = 0; j < PLAYOUTS; j++){
      Board newBoard = Board();
      newBoard.deepCopy(newBoard, currBoard);
      newBoard.mover(possibleMoves[i].first, possibleMoves[i].second, cpu);

      //Plays one game through to the end
      while(!(reversi.isFull(newBoard))){
        vector<pair<int, int>> oppMoves = moveGenerator(newBoard, opp);
         if(turn == opp && oppMoves.size() > 0){
           pair<int, int> choice2 = random(oppMoves);
           newBoard.mover(choice2.first, choice2.second, opp);
           reversi.flipTokens(newBoard, choice2.first, choice2.second, opp);
           turn = cpu;
         }else{
           turn = cpu;
         }

         vector<pair<int, int>> cpuMoves = moveGenerator(newBoard, cpu);
         if(turn == cpu && cpuMoves.size() > 0){

           pair<int, int> choice = random(cpuMoves);
           newBoard.mover(choice.first, choice.second, cpu);
           reversi.flipTokens(newBoard, choice.first, choice.second, cpu);
           turn = opp;
         }else{
           turn = opp;
         }
          //newBoard.drawBoard();

        //cout << cpuMoves.size() << " CPU moves left." << endl;
        //cout << oppMoves.size() << " OPP moves left." << endl;
        if(oppMoves.size() < 1 && cpuMoves.size() < 1){
          break;
        }
      }

      //Records result of playout:
      //1 = win, -1 = loss, 0 = draw
      char winner = reversi.gameWon(newBoard);

      if(winner == cpu){
        wins[i] += 2;
      }else if(winner == opp){
        wins[i] += -2;
      }else{
        wins[i] += 1;
      }
      newBoard.freeBoard(newBoard.board);
    }
  }
//}

  int largest = wins[0];
  int largestIndex = 0;

  for(int h = 1; h < size; h++){
    if(largest < wins[h]){
      largest = wins[h];
      largestIndex = h;
    }
  }
  delete [] wins;
  pair<int, int> chosen(possibleMoves[largestIndex].first, possibleMoves[largestIndex].second);
  return chosen;
}


/////////////////////////////////
//          HEURISTIC
/////////////////////////////////
pair<int, int> pMCTS::heurMCTS(Board currBoard, char cpu){
  Reversi reversi;
  vector<pair<int, int>> possibleMoves = moveGenerator(currBoard, cpu);
  int size = possibleMoves.size();
  int ti = clock();
  int* wins = new int[size];

  char opp;
  char max;
  if(cpu == 'X'){
    max = 'X';
    opp = 'O';
  }else{
    opp = 'X';
    max = 'X';
  }
  char turn = opp;
//int plays = 0;
//clock_t startTime = clock(); //Start timer
//clock_t endTime;

  //while(ti < 2000){
  for(int i = 0; i < size; i++){
    wins[i] = 0;

    for(int j = 0; j < PLAYOUTS; j++){
      Board newBoard = Board();
      newBoard.deepCopy(newBoard, currBoard);
      newBoard.mover(possibleMoves[i].first, possibleMoves[i].second, cpu);


      //Plays one game through to the end
      while(!(reversi.isFull(newBoard))){
        vector<pair<int, int>> oppMoves = moveGenerator(newBoard, opp);
         if(turn == opp && oppMoves.size() > 0){
           pair<int, int> choice2 = random(oppMoves);
           newBoard.mover(choice2.first, choice2.second, opp);
           reversi.flipTokens(newBoard, choice2.first, choice2.second, opp);
           turn = cpu;
         }else{
           turn = cpu;
         }

         vector<pair<int, int>> cpuMoves = moveGenerator(newBoard, cpu);
         if(turn == cpu && cpuMoves.size() > 0){

           pair<int, int> choice = random(cpuMoves);
           newBoard.mover(choice.first, choice.second, cpu);
           reversi.flipTokens(newBoard, choice.first, choice.second, cpu);
           turn = opp;
         }else{
           turn = opp;
         }

        if(oppMoves.size() < 1 && cpuMoves.size() < 1){
          break;
        }
      }
      //plays++;

      //Records result of playout:
      char winner = reversi.gameWon(newBoard);
      int weight = decisionHelper(newBoard, cpu);

      if(winner == cpu){
        wins[i] += weight;
      }else if(winner == opp){
        wins[i] -= weight;
      }else{
        wins[i] += 0;
      }


      newBoard.freeBoard(newBoard.board);
    }
  }
  //endTime = clock(); //end timer
  //cout << "Plays completed: " << plays << " in " << ((double)(endTime-startTime) / CLOCKS_PER_SEC) << endl;
  //}

  int largest = wins[0];
  int largestIndex = 0;

  for(int h = 1; h < size; h++){
    if(largest < wins[h]){
      largest = wins[h];
      largestIndex = h;
    }
  }
  delete [] wins;
  pair<int, int> chosen(possibleMoves[largestIndex].first, possibleMoves[largestIndex].second);
  return chosen;
}

int pMCTS::decisionHelper(Board bo, char cpu){
  int score = gameScore(bo, cpu);
  int weight;

  if(score < 0){
    score *= -1;
  }

  if(score >= 25){
    weight = 160;
  }else if(25 >= score >= 20){
    weight = 80;
  }else if(20 >= score >= 15){
    weight = 40;
  }else if(15 >= score >= 10){
    weight = 20;
  }else if(10 >= score >= 5){
    weight = 10;
  }else if(5 >= score >= 0){
    weight = 5;
  }else{
    cout << "nani the frrck" << endl;
    weight = 0;
  }
  return weight;
}

int pMCTS::gameScore(Board bo, char cpu){
  int x_pts = 0;
  int o_pts = 0;
  int diff = 0;

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(bo.board[j][i] == 0){
        x_pts++;
      }else if(bo.board[j][i] == 1){
        o_pts++;
      }
    }
  }

  if(cpu == 'X'){
      diff = x_pts - o_pts;
      return diff;
  }
  diff = o_pts - x_pts;
  return diff;
}

pair<int, int> pMCTS::random(vector<pair<int, int>> moves){
  int index = (rand() % moves.size());
  pair<int, int> choice(moves[index].first, moves[index].second);
  return choice;
}
