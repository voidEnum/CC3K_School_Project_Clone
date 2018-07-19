#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "entity.h"

class Cell;

class Creature : public Entity {
protected:
  int hp, atk, def;
  bool isAlive;
public:
  Creature(Cell *c = nullptr, char sym = 'C', int h = 100, 
           int a = 50, int d = 50, bool isalive = true);
  virtual void move(Cell *target);
  virtual void beginTurn();
  virtual void endTurn();
  virtual int getAtk() const;
  virtual int getDef() const;
  int damage(int atk, int def);
  bool checkAlive() const;
  private:
    static int ceil_divide(int numerator, int denom);
    void die();
};

#endif
