#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "entity.h"

class Cell;

class Creature : public Entity {
protected:
  int hp, atk, def;
public:
  Creature(char sym = 'C', std::string name = "Creature", int h = 100, 
           int a = 50, int d = 50);
  virtual void beginTurn();
  virtual void endTurn();
  virtual int getAtk() const;
  virtual int getDef() const;
  virtual int getHp() const;
  virtual std::string getName() const;
  virtual int damage(int atk, int def);

  virtual void modifyHp(int delta);
 private:
  int ceil_divide(int numerator, int denom);
  void die();
};

#endif
