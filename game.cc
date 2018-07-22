#include "game.h"

#include "cell.h"
#include "player.h"
#include "treasure.h"
#include "treasure_normal.h"
#include "invalid_behave.h"
#include "posn.h"

#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

Game::Game(): theGrid(new Grid()), player{nullptr}, /*enemies{nullptr}, potions{nullptr},*/ frozen{false} {
  theGrid->init("maps/basicFloor.txt", 1);
}

void Game::generateEnemies(vector<vector<Cell *>> &vcham) {
  for (int i = 0; i < 20; ++i) {
    int numChambers = vcham.size();
    int selectedChamberIdx = rand() % (numChambers);
    vector<Cell *> &vc = vcham[selectedChamberIdx];
    int numCells = vc.size();
    int selectedCellIdx = rand() % (numCells);

    Cell &selected = *(vc[selectedCellIdx]);

    shared_ptr<Enemy> enemy(new Enemy());
    theGrid->placeEntity(enemy, {selected.getRow(), selected.getCol()});
    enemies.emplace_back(enemy);
    vc.erase(vc.begin() + selectedCellIdx); // remove cell from candidate spawn locations
  }
}
  /*int size = theGrid.size();
  int randomrange = 0;
  int randomnumber = 0;
  Vector<Cell>candidates;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (theGrid[i][j].cell.tile == Terrain::Chamfloor) {
        ++randomrange;
        candidates.emplace_back(theGrid[i][j]);
      }
    }
  }
  for (int k = 0; k < 20; ++k) {
    randomnumber = rand() % randomrange;
    Enemy &e = Enemy{&candidates[randomnumber]};
    placeEntity(e, candidates[randomnumber]);
    enemies.emplace_back(e);
  }
}*/  
    
/*void Game::generatePotions() {
  int size = theGrid.size();
  int randomrange = 0;
  int randomnumber = 0;
  Vector<Cell>candidates;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (theGrid[i][j].cell.tile == Terrain::Chamfloor) {
        ++randomrange;
        candidates.emplace_back(theGrid[i][j]);
      }
    }
  }
  for (int k = 0; k < 10; ++k) {
    randomnumber = rand() % randomrange;
    Potion &p = Potion{&candidates[randomnumber]};
    placeEntity(p, candidates[randomnumber]);
    potions.emplace_back(p);
  }
}  
*/ 
 
void Game::generateTreasures(vector<vector<Cell *>> &vcham) {
  for (int i = 0; i < NUM_TREASURE_SPAWN; i++) {
    int numChambers = vcham.size();
    int selectedChamberIdx = rand() % numChambers;

    vector<Cell *> &vc = vcham[selectedChamberIdx];
    int numCells = vc.size();
    int selectedCellIdx = rand() % numCells;

    Cell &selected = *(vc[selectedCellIdx]);
    vc.erase(vc.begin() + selectedCellIdx); // remove cell from candidate spawn locations
    shared_ptr<Treasure> toPlace(new Treasure_Normal()); 
    theGrid->placeEntity(toPlace, {selected.getRow(), selected.getCol()});
  }
}


void Game::generatePlayer(const string &race, vector<vector<Cell *>> &vvc) {
  (void)race;

  int numChambers = vvc.size();
  int selectedChamberIdx = rand() % numChambers;

  vector<Cell *> &vc = vvc[selectedChamberIdx];
  int numCells = vc.size();
  int selectedCellIdx = rand() % numCells;

  Cell &selected = *(vc[selectedCellIdx]);
  vc.erase(vc.begin() + selectedCellIdx); // remove cell from candidate spawn locations

  shared_ptr<Player> test(new Player());

  player = test;
  theGrid->placeEntity(player, {selected.getRow(), selected.getCol()}); 
}       



bool Game::startRound(const string &race) {
  // Copy the chamber layout
  vector<vector<Cell *>> candidateCells = theGrid->getChambers();
  
  //generateEnemies();
  //generatePotions();
  generatePlayer(race, candidateCells);
  generateTreasures(candidateCells);
  generateEnemies(candidateCells);
  return true;
}

/*
void Game::moveEnemies(vector<shared_ptr<Enemy>>enemies) {
  int size = enemies.size();
  int randomrange = 0;
  int randomnumber = 0;
  vector<Cell>candidates;
  for (int i = 0; i < size; ++i) {
    row = enemies.cell.getRow();
    col = enemies.cell.getCol();
    for (int r = ((row == 0) ? 0 : -1); r <= ((row == size - 1) ? 0 : 1); ++r) {
        //checks for all neighbors
      for (int c = ((col == 0) ? 0 : -1); c <= ((col == size - 1) ? 0 : 1); ++c) {
        if (!(r == 0 && c == 0)) {
          candidates.emplace_back(theGrid[row + r][col + c]);
          ++randomrange;
        }
      }
    }
    randomnumber = rand() % randomrange;
    theGrid.moveEntity(enemies.at(i).cell, candidates.at(randomnumber));
    randomnumber = 0;
    randomrange = 0;
  }
}

void Game::changeFloor() {
  theGrid.init();
}
  
void Game::update_display() {
  theGrid.td.update();
}*/


Posn dir_to_posn(Cell &cur_cell, string direction) {
  int row = cur_cell.getRow();
  int col = cur_cell.getCol();
  if (direction == "ea") return {row, col + 1};
  else if (direction == "no") return {row - 1, col};
  else if (direction == "we") return {row, col - 1};
  else if (direction == "so") return {row + 1, col};
  else if (direction == "nw") return {row - 1, col - 1};
  else if (direction == "ne") return {row - 1, col + 1};
  else if (direction == "sw") return {row + 1, col - 1};
  else if (direction == "se") return {row + 1, col + 1};
  else return {-1, -1};
}

void Game::movePlayer(const string &direction) {
  Posn player_Posn = player->getPosn();
  Posn heading_dir = dir_to_posn(theGrid->getCell(player_Posn), direction);
  char heading_tile = theGrid->getCell(heading_dir).getSymbol();
  if (heading_tile == '#' || heading_tile == '.' ||
      heading_tile == '\\' || heading_tile == '+') { 
    cout << heading_tile << endl;
    theGrid->moveEntity(player_Posn, heading_dir);
  }
  else {
    throw Invalid_behave("");
  }
}

/*void Game::PlayerAttack(string direction) {
  player.attack(dir_to_cell(player.cell, direction));
}*/

/*void Game::enemyAttack() {}
  
  
void Game::Player_usePotion(string direction) {
  int size = potions.size();
  int target_row = target.getRow();
  int target_col = target.getCol();
  for (int i = 0; i < size; ++size) { 
    if (target_row == potions.at(i).getRow() &&
        target_col == potions.at(i).getCol()) {
      player->usePotion(dir_to_cell(player.cell, direction));
      shared_ptr<Potion>removed_potion = potions.back();
      potions.pop_back();
      removeEntity(removed_potion.cell);
      return;
    }
  }
}

void Game::freeze() {
  frozen = !frozen;
}*/

bool valid_dir(string dir) {
  if (dir == "ea" || dir == "no" || dir == "so" || dir == "we" ||
      dir == "sw" || dir == "se" || dir == "nw" || dir == "ne") {
    return true;
  }
  else {
    throw Invalid_behave("");
    return false;
  }
}

bool Game::processTurn(const string &command) {
  istringstream iss(command);
  string s;
  iss >> s;
  /*if (s == "a") {
    iss >> s;
    if (valid_dir(s)) {
      PlayerAttack(s);
    }
  }*/
  /*else if (s == "use") {
    //iss >> s;
    //if (valid_dir(s)) {
    //  Player_usePotion(s);
    //}
  }
  else if (s == "restart") {
    //changeFloor();
  }
  else if (s == "f") {
    //freeze();
  }*/ 
  if (valid_dir(s)) {
    movePlayer(s);
  } 
  /*else if (!frozen) {
   // moveEnemies(enemies);
  }*/
  return true;
}

void Game::print() {
  cout << *theGrid;
  cout << "Race: " << "Player " << "Gold: " << to_string(player->finalScore()) << endl;
  cout << "HP: " << to_string(player->getHp()) << endl;
  cout << "Atk: " << to_string(player->getAtk()) << endl;
  cout << "Def: " << to_string(player->getDef()) << endl;
  cout << "Action: " << endl; 
}

bool Game::sort_function(shared_ptr<Enemy>e1, shared_ptr<Enemy>e2) {
  if ((e1->getPosn()).r < (e2->getPosn()).r) {
    return true;
  }
  else if ((e1->getPosn()).r == (e2->getPosn()).r &&
           (e1->getPosn()).c < (e2->getPosn()).c) {
    return true;
  }
  else {
    return false;
  }
}

void Game::enemy_sort(vector<shared_ptr<Enemy>>&enemies) {
  sort(enemies.begin(), enemies.end(), &sort_function);
} 

/*void check_neighbor() {
  for (int i = -1; i < 1; ++i) {
    for (int j = -1; j < 1; ++j) {*/
