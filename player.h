#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "creature.h"
#include "potion.h"
#include <memory>
#include <string>
#include "enemy.h"

class Player: public Creature, public std::enable_shared_from_this<Player> {
  int gold;
  int maxHp;
 public:
  Player(std::string name, int hp = 100, int atk = 50, int def = 50);
  virtual atkStatus attack(std::shared_ptr<Enemy>);
  virtual atkStatus wasAttacked(std::shared_ptr<Enemy> aggressor, int modifiedDamage);
  virtual std::string actionText(std::shared_ptr<Enemy> aggressor, atkStatus as);
  virtual int getMaxHp();
  virtual void move(Posn p);
  //virtual void beginTurn();
  //virtual void endTurn();
  virtual void addGold(int reward);
  //bool useEntity(Cell &cell);
  virtual int finalScore();
  virtual std::shared_ptr<Player> withoutBuffs();
  virtual int getGold();
  virtual void beginTurn();
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
