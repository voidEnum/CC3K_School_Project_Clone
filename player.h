#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <memory>
class Player: public Creature{
  int gold;
 public:
  Player(Entity &entity);
  atkStatus attack(Cell &cell);
  atkStatus wasAttacked(Creature &crtr);
  void move(Cell &cell);
  virtual void beginTurn()=0;
  virtual void endTurn()=0;
  bool usePotion(Cell &cell);
  int finalScore();
  shared_ptr<Player>withoutBuffs();
 private:
  void die();
  static int ceil_divide(int numerator, int denom)
}

#endif
