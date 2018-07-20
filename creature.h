#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "entity.h"
#include "posn.h"

class Cell;

class Creature : public Entity {
protected:
  int maxHp, hp, atk, def;
public:
  Creature(Posn p = {-1, -1}, char sym = 'C', int mhp = 100, int h = 100, 
           int a = 50, int d = 50);
  virtual void beginTurn();
  virtual void endTurn();
  virtual int getAtk() const;
  virtual int getDef() const;
  virtual int getHp() const;
  virtual int damage(int atk, int def);
 private:
  int ceil_divide(int numerator, int denom);
};

#endif
