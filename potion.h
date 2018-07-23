#ifndef __POTION_H__
#define __POTION_H__

#include "item.h"

class Potion : public Item { 
protected:
  Potion();
public:
  // All subclasses must implement isRevealed and reveal
  // to keep track of if one potion of that type has been
  // used.
  virtual bool isRevealed() const = 0;
  virtual void reveal() = 0;

  // All subclasses must implement wasUsed to be properly used by players.
  virtual bool wasUsed(Player &user) = 0;
};

// Declaring default potions here as well to reduce number of files
class Potion_RH : public Potion {
  int potency;
  static bool revealed;
public:
  Potion_RH(int p = 10);
  bool isRevealed() const override;
  void reveal() override;
  bool wasUsed(Player &user) override;
};
class Potion_PH : public Potion {
  int potency;
  static bool revealed;
public:
  Potion_PH(int p = 10);
  bool isRevealed() const override;
  void reveal() override;
  bool wasUsed(Player &user) override;
};
class Potion_BA : public Potion {
  int potency;
  static bool revealed;
public:
  Potion_BA(int p = 5);
  bool isRevealed() const override;
  void reveal() override;
  bool wasUsed(Player &user) override;
};
class Potion_WA : public Potion {
  int potency;
  static bool revealed;
public:
  Potion_WA(int p = 5);
  bool isRevealed() const override;
  void reveal() override;
  bool wasUsed(Player &user) override;
};
class Potion_BD : public Potion {
  int potency;
  static bool revealed;
public:
  Potion_BD(int p = 5);
  bool isRevealed() const override;
  void reveal() override;
  bool wasUsed(Player &user) override;
};
class Potion_WD : public Potion {
  int potency;
  static bool revealed;
public:
  Potion_WD(int p = 5);
  bool isRevealed() const override;
  void reveal() override;
  bool wasUsed(Player &user) override;
};
/* can't get the CRTP stuff working with regular inhertance from above.
   commenting out CRTP stuff for now and reimplemnting the standard way.
template<class DerivedPotion>
class Potion_CRTP : public Potion {
protected:
  static bool revealed;
public:
  bool isRevealed() {return revealed;}
  void reveal() {revealed = true;}
  bool wasUsed(Player &user) override {
    return static_cast<DerivedPotion*>(this)->wasUsed(user);}
};

template<class DerivedPotion>
bool Potion_CRTP<DerivedPotion>::revealed = false;
*/

#endif
