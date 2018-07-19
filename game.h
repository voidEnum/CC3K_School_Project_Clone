#ifndef _GAME_H_
#define _GAME_H_

class Game {
  shared_ptr<Grid>theGrid;
  Player &player;
  vector<shared_ptr<Enemy>>enemies;
  vector<shared_ptr<Potion>>potions;
  bool frozen;
 public:
  Game();
  void generateEnemeies();
  void generatePotions();
  void generateTreasures();
  void generatePlayer();
  void startRound();
  void moveEnemies(vector<Enemy *>enemies);
  void changeFloor();
  void update_display();
  void movePlayer();
  void PlayerAttack();
  void enemyAttack();
  void Player_usePotion();
  void freeze();
  void chackvalid();
} 
