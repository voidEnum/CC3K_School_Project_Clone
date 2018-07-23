#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "creature.h"
#include "enemy.h"
#include <memory>
#include <string>
#include "enemy.h"

class Player: public Creature, public std::enable_shared_from_this<Player> {
  int gold;
  int maxHp;
 public:
  Player(std::string name, int hp = 100, int atk = 50, int def = 50);
  virtual atkStatus attack(std::shared_ptr<Enemy> aggressor);
  atkStatus wasAttacked(std::shared_ptr<Enemy> aggressor, int modifiedDamage);
  void move(Posn p);
  //virtual void beginTurn();
  //virtual void endTurn();
  void addGold(int reward);
  //bool usePotion(Cell &cell);
  virtual int finalScore();
  std::shared_ptr<Player>withoutBuffs();
  virtual std::string actionText(std::shared_ptr<Enemy> aggressor, atkStatus as);
/*<<<<<<< HEAD
=======*/
  int getMaxHp();
//>>>>>>> 431b61aa856f9bcc0545a46272958fc858411cf2
  int getGold();
  void beginTurn();
 private:
  void die();
  static int ceil_divide(int numerator, int denom);
};

#endif
