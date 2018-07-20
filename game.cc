#include "game.h"

Game::Game(): theGrid{nullptr}, player{nullptr}, enemies{nullptr}, potions{nullptr}, frozen{false} {
  theGrid.init();
}

void Game::generateEnemies() {
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
  for (int k = 0; k < 20; ++k) {
    randomnumber = rand() % randomrange;
    Enemy &e = Enemy{&candidates[randomnumber]};
    placeEntity(e, candidates[randomnumber]);
    enemies.emplace_back(e);
  }
}  
    
void Game::generatePotions() {
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
  
void Game::generateTreasures() {
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
    Treasure &t = Treasure{&candidates[randomnumber]};
    placeEntity(t, candidates[randomnumber]);
  }
}


void Game::generatePlayer() {
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
  randomnumber = rand() % randomrange;
  Player &user = Player{&candidates[randomnumber]};
  placeEntity(user, candidates[randomnumber]);
  player = user;
}       
  
void Game::startRound() {
  generateEnemies();
  generatePotions();
  generateTreasures();
  generatePlayer();
}

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
}

Cell &dir_to_cell(Cell &cur_cell, string direction) {
  int row = cur_cell.getRow();
  int col = cur_cell.getCol();
  switch (direction) {
    case "ea" : return theGrid[row][col + 1];
    case "no" : return theGrid[row - 1][col];
    case "we" : return theGrid[row][col - 1];
    case "so" : return theGrid[row + 1][col];
    case "nw" : return theGrid[row - 1][col - 1];
    case "ne" : return theGrid[row - 1][col + 1];
    case "sw" : return theGrid[row + 1][col - 1];
    case "se" : return theGrid[row + 1][col + 1];
  }
}

void Game::movePlayer(string direction) {
  thegrid.moveEntity(player.cell, dir_to_cell(player.cell, direction));
}

void Game::PlayerAttack(string direction) {
  player.attack(dir_to_cell(player.cell, direction));
}

void Game::enemyAttack() {
  
  
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
}

bool valid_dir(string dir) {
  if (dir == "ea" || dir == "no" || dir == "so" || dir == "we" ||
      dir == "sw" || dir == "se" || dir == "nw" || dir == "ne") {
    return true;
  }
  else {
    return false;
  }
}

void Game::processTurn(string command) {
  istringstream iss(command);
  string s;
  iss >> s;
  if (s == "a") {
    iss >> s;
    if (valid_dir(s)) {
      PlayerAttack(s);
    }
  }
  else if (s == "use") {
    iss >> s;
    if (valid_dir(s)) {
      Player_usePotion(s);
    }
  }
  else if (s == "restart") {
    changeFloor();
  }
  else if (s == "f") {
    freeze();
  }
  else if (valid_dir(s)) {
    movePlayer(s);
  } 
  else if (!frozen) {
    moveEnemies(enemies);
  }
  update_display(); 
}
