#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "creature.h"
#include "potion.h"
#include <memory>
#include <string>

class Player: public Creature, public std::enable_shared_from_this<Player> {
  int gold;
  int maxHp;
 public:
  Player(std::string name, int hp = 100, int atk = 50, int def = 50);
  atkStatus attack(Cell &target);
  atkStatus wasAttacked(Creature *aggressor);
  void move(Posn p);
  //virtual void beginTurn();
  //virtual void endTurn();
  virtual void addGold(int reward);
  //bool useEntity(Cell &cell);
  int finalScore();
  virtual std::shared_ptr<Player> withoutBuffs();
  std::string actionText(Creature *aggressor);
  int getGold();
  void beginTurn();
  //useEntity overloads for visitor pattern
  //virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion> p);
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_RH> p);
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_PH> p);
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_BA> p);
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_WA> p);
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_BD> p);
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_WD> p);
 private:
  void die();
  static int ceil_divide(int numerator, int denom);
};

#endif
