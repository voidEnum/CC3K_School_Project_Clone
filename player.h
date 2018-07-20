#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "creature.h"
#include <memory>


class Player: public Creature, public std::enable_shared_from_this<Player> {
  int gold;
 public:
  Player();
  atkStatus attack(Cell &target);
  atkStatus wasAttacked(Creature *aggressor);
  void move(Posn p);
  //virtual void beginTurn();
  //virtual void endTurn();
  void addGold(int reward);
  //bool usePotion(Cell &cell);
  int finalScore();
  std::shared_ptr<Player>withoutBuffs();
  std::string actionText(Creature *aggressor);
 private:
  void die();
  static int ceil_divide(int numerator, int denom);
};

#endif
