#ifndef __TREASURE_H__
#define __TREASURE_H__

#include "item.h"
#include "posn.h"

class Player;

class Treasure: public Item, public std::enable_shared_from_this<Treasure>{
protected:
  int value;
  Treasure(int v, std::string name);
public:
  virtual int getValue() const;
  virtual void beSteppedOn(Entity &whoStepped) override;
  virtual bool canBeSteppedOn(const Entity &whoStepped) const override;
  virtual bool canBeAdded() const;
};

#endif
