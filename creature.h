#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "entity.h"

class Cell;

class Creature : public Entity {
protected:
  int maxHp, hp, atk, def;
public:
  Creature(char sym = 'C', int mhp = 100, int h = 100, 
           int a = 50, int d = 50);
  virtual void beginTurn();
  virtual void endTurn();
  virtual int getAtk() const;
  virtual int getDef() const;
};

#endif
