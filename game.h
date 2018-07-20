#ifndef _GAME_H_
#define _GAME_H_

class Game {
  shared_ptr<Grid>theGrid;
  Player &player;
  vector<shared_ptr<Enemy>>enemies;
  vector<shared_ptr<Potion>>potions;
  bool frozen;
  // methods
 public:
  Game();
  bool startRound(string race);
  void processTurn(string command);
 private:
  void generateEnemeies();
  void generatePotions();
  void generateTreasures();
  void generatePlayer(string race);
  void moveEnemies(vector<Enemy *>enemies);
  void changeFloor();
  void update_display();
  void movePlayer(string direction);
  void PlayerAttack(string direction);
  void enemyAttack();
  void Player_usePotion();
  void freeze();
  void chackvalid();
} 
