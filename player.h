#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "creature.h"
#include <memory>


class Player: public Creature, public std::enable_shared_from_this<Player> {
  int gold;
  int maxHp;
 public:
  Player(int maxHp);
  atkStatus attack(Cell &target);
  atkStatus wasAttacked(Creature *aggressor);
  void move(Cell *target);
  virtual void beginTurn()=0;
  virtual void endTurn()=0;
  void addGold(int reward);
  //bool usePotion(Cell &cell);
  int finalScore();
  std::shared_ptr<Player>withoutBuffs();
};

#endif
