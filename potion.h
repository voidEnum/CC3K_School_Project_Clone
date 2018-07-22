#ifndef __POTION_H__
#define __POTION_H__

#include "item.h"

class Potion : public Item {
protected:
  Potion();
};

template<class DerivedPotion>
class Potion_CRTP : public Potion {
protected:
  static bool revealed;
public:
  bool isRevealed() {return revealed;}
  void reveal() {revealed = true;}
};

template<class DerivedPotion>
bool Potion_CRTP<DerivedPotion>::revealed = false;

#endif
