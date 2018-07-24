#ifndef __TREASURE_H__
#define __TREASURE_H__

#include "item.h"
#include "posn.h"

class Player;

class Treasure: public Item {
protected:
  int value;
  Treasure(int v = 2);
public:
  virtual int getValue() const;
  virtual void beSteppedOn(Entity &whoStepped) override;
  virtual bool canBeSteppedOn(const Entity &whoStepped) const override; 
};

#endif
