#ifndef __POTION_H__
#define __POTION_H__

#include "item.h"
#include <memory>

class Potion : public Item { 
protected:
  int potency;  // represents the power of the potion.
  Potion(int n, std::string name = "Potion");
public:
  // All subclasses must implement isRevealed and reveal
  // to keep track of if one potion of that type has been
  // used.
  virtual bool isRevealed() const = 0;
  virtual void reveal() = 0;

  virtual bool isUsable() const override;
  virtual int getPotency() const;
  std::string getName() const;

  // beUsedBy is part of a visitor pattern. beUsedBy will visit Players
  // by calling user.useEntity(*this). All subclasses must implement.
  virtual void beUsedBy(Player &user) = 0;
  // All subclass potions must implement beUsedBy to properly
  // interact with player classes
};

#endif
