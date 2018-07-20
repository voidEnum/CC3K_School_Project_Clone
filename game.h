#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <vector>

#include "grid.h"

class Player;

class Game {
  std::unique_ptr<Grid> theGrid;
  std::shared_ptr<Player> player;
  //std::vector<std::shared_ptr<Enemy>>enemies;
  //std::vector<std::shared_ptr<Potion>>potions;
  bool frozen;
  // methods
 public:
  Game();
  bool startRound(std::string race);
  bool processTurn(std::string command);
 private:
  //void generateEnemeies();
  //void generatePotions();
  //void generateTreasures();
  //void generatePlayer(std::string race);
  //void moveEnemies(std::vector<Enemy *>enemies);
  //void changeFloor();
  //void update_display();
  //void movePlayer(std::string direction);
  //void PlayerAttack(std::string direction);
  //void enemyAttack();
  //void Player_usePotion();
  //void freeze();
  //void chackvalid();
};

#endif 
