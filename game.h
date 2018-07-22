#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <vector>

#include "grid.h"
#include "enemy.h"

class Player;

class Game {
  static const int NUM_TREASURE_SPAWN = 10;
  std::unique_ptr<Grid> theGrid;
  std::shared_ptr<Player> player;
  std::vector<std::shared_ptr<Enemy>>enemies;
  //std::vector<std::shared_ptr<Potion>>potions;
  bool frozen;
  // methods
 public:
  Game();
  bool startRound(const std::string &race);
  bool processTurn(const std::string &command);
  void print();
 private:
  void generateEnemies(std::vector<std::vector<Cell *>> &vcham);
  //void generatePotions();
  void generateTreasures(std::vector<std::vector<Cell *>> &vcham); // all normal treasures for now
  void generatePlayer(const std::string &race, std::vector<std::vector<Cell *>> &vvc); // generic player for now
  //void moveEnemies(std::vector<Enemy *>enemies);
  //void changeFloor();
  //void update_display();
  void movePlayer(const std::string &direction);
  void PlayerAttack(std::string direction);
  //void enemyAttack();
  //void Player_usePotion();
  //void freeze();
  //void chackvalid();
  static bool sort_function(std::shared_ptr<Enemy>e1, std::shared_ptr<Enemy>e2);
  void enemy_sort(std::vector<std::shared_ptr<Enemy>>&enemies);
  void check_neighbor();
};

#endif 
