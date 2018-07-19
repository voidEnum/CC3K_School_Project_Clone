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

void Game::movePlayer(Cell &dest) {
  thegrid.moveEntity(player.cell, dest);
}

void Game::PlayerAttack(Cell &target) {
  player.attack(target);
}

void Game::enemyAttack() {
  
  
void Game::Player_usePotion(Cell &target) {
  int size = potions.size();
  int target_row = target.getRow();
  int target_col = target.getCol();
  for (int i = 0; i < size; ++size) { 
    if (target_row == potions.at(i).getRow() &&
        target_col == potions.at(i).getCol()) {
      player->usePotion(target);
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

void Game::processTurn() {
  if (!frozen) {
    moveEnemies(enemies);
  }
  update_display(); 
}
